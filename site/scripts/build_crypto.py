#!/usr/bin/env python3
"""Typecheck crypto examples, generate C, build and check the browser module."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tarfile
import zipfile
from nist_vectors import prepare_nist
from native_suites import prepare_drivers

SITE = Path(__file__).resolve().parents[1]
GMP_VERSION = "6.3.0"
GMP_SHA256 = "a3c2b80201b89e68616f4ad30bc66aee4927c3ce50e33929ca819d5c43538898"


def run(command, **kwargs):
    return subprocess.run([str(part) for part in command], check=True, **kwargs)


def find(root, name):
    matches = [path for path in root.rglob(name) if not any(
        part.startswith(".") or part in ("node_modules", "pvs2c", "dist")
        for part in path.relative_to(root).parts)]
    if len(matches) != 1:
        raise SystemExit(f"Expected one {name} under {root}, found {matches}")
    return matches[0]


def generation_fingerprint(crypto, pvs, runtime, suites=()):
    inputs = [*sorted(crypto.rglob("*.pvs")), find(crypto, "replay-generate.lisp"),
              find(crypto, "crypto-random-attachments.lisp"), find(crypto, "crypto-statistics-attachments.lisp"), SITE / "scripts/pvs2c-compat.lisp"]
    inputs += [find(crypto, name) for name in ("check.py", "check_aes.py", "check_assessments.py")]
    selection = [{key: suite.get(key) for key in ("theory", "driver", "generator", "nist")} for suite in suites]
    revision = subprocess.run(["git", "-C", pvs.parent, "rev-parse", "HEAD"], capture_output=True).stdout
    return hashlib.sha256(str(pvs).encode() + revision + json.dumps(selection, sort_keys=True).encode() + (runtime / "include/pvslib.h").read_bytes() +
                          b"".join(path.read_bytes() for path in inputs if "pvs2c" not in path.parts)).hexdigest()


def gmp_library(cache):
    archive = cache / f"gmp-{GMP_VERSION}.tar.xz"
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != GMP_SHA256:
        temporary = archive.with_suffix(".download")
        run(["curl", "-fsSL", "--retry", "3", f"https://gmplib.org/download/gmp/{archive.name}", "-o", temporary])
        temporary.replace(archive)
    if hashlib.sha256(archive.read_bytes()).hexdigest() != GMP_SHA256:
        raise SystemExit(f"GMP checksum mismatch: {archive}")
    version = subprocess.check_output(["emcc", "--version"], text=True).splitlines()[0]
    key = hashlib.sha256((version + GMP_SHA256).encode()).hexdigest()[:16]
    prefix = cache / f"gmp-wasm-{key}"
    if not (prefix / "lib/libgmp.a").exists():
        source = cache / f"gmp-{GMP_VERSION}"
        with tarfile.open(archive) as tar:
            tar.extractall(cache, filter="data")
        build = cache / f"gmp-build-{key}"
        build.mkdir(exist_ok=True)
        with (build / "build.log").open("w") as log:
            for command in (["emconfigure", source / "configure", "--host=wasm32-unknown-emscripten",
                             "--disable-assembly", "--disable-shared", "--enable-static", f"--prefix={prefix}"],
                            ["emmake", "make", f"-j{min(os.cpu_count() or 2, 8)}"],
                            ["emmake", "make", "install"]):
                run(command, cwd=build, env={**os.environ, "CC_FOR_BUILD": os.environ.get("CC_FOR_BUILD", "cc")},
                    stdout=log, stderr=subprocess.STDOUT)
    return prefix, archive, version


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pvs", default=os.environ.get("PVS_BIN", "pvs"))
    parser.add_argument("--crypto-root", type=Path)
    parser.add_argument("--cache", type=Path, default=SITE / ".wasm-cache")
    parser.add_argument("--output", type=Path, default=SITE / ".wasm")
    parser.add_argument("--suite", action="append", help="Build only this theory (local development)")
    parser.add_argument("--reuse-generated", action="store_true", help="Reuse generation only when its source/tool fingerprint matches")
    args = parser.parse_args()
    pvs = shutil.which(os.path.expanduser(args.pvs))
    if not pvs:
        parser.error("Set PVS_BIN, put pvs on PATH, or pass --pvs")
    pvs = Path(pvs).resolve()
    repository = Path(subprocess.check_output(["git", "rev-parse", "--show-toplevel"], cwd=SITE, text=True).strip())
    crypto = args.crypto_root.resolve() if args.crypto_root else find(repository, "crypto_words.pvs").parent.parent
    runtime = Path(os.environ.get("PVS2C_RUNTIME", pvs.parent / "lib/pvs2c")).resolve()
    suites = json.loads((SITE / "crypto-runners.json").read_text())
    if args.suite:
        suites = [suite for suite in suites if suite["theory"] in args.suite]
        if {suite["theory"] for suite in suites} != set(args.suite):
            parser.error("Unknown suite")
    output, cache = args.output.resolve(), args.cache.resolve()
    output.mkdir(parents=True, exist_ok=True)
    # A failed rebuild must never leave a publishable old manifest.
    (output / "manifest.json").unlink(missing_ok=True)
    cache.mkdir(parents=True, exist_ok=True)
    gmp, gmp_source, emcc_version = gmp_library(cache)
    stage = cache / "application"
    fingerprint = generation_fingerprint(crypto, pvs, runtime, suites)
    marker = stage / ".generation-key"
    reuse = args.reuse_generated and marker.exists() and marker.read_text() == fingerprint
    if not reuse:
        shutil.rmtree(stage, ignore_errors=True)
    stage.mkdir(exist_ok=True)
    inputs = {}
    for source in crypto.rglob("*.pvs"):
        if "pvs2c" in source.relative_to(crypto).parts:
            continue
        destination = stage / source.relative_to(crypto)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, destination)
        inputs[source.relative_to(repository).as_posix()] = hashlib.sha256(source.read_bytes()).hexdigest()
    drivers = prepare_drivers(suites, crypto, stage, output, find, inputs, repository)
    nist_sets = prepare_nist(suites, cache, output, crypto, find)
    env = {**os.environ, "PVS_LIBRARY_PATH": str(stage), "PVS_LOG_DIR": str(stage)}
    helper = find(crypto, "replay-generate.lisp")
    mains = []
    aes_ready = False
    def generate(theory, generator=None):
        nonlocal aes_ready
        original = find(crypto, theory + ".pvs")
        source = stage / original.relative_to(crypto)
        previous = stage / f"{theory}.log"
        if (reuse and previous.exists() and (source.parent / f"pvs2c/include/{theory}_c.h").exists() and
                (source.parent / f"pvs2c/src/{theory}_c.c").exists() and f"CRYPTO-OK {theory}" in previous.read_text(errors="replace")):
            return original, source
        if generator == "aes" and not aes_ready:
            # Match validation/check_aes.py: prime the bytevector ABI before AES.
            primer = find(stage, "bytevector_tests.pvs")
            with (stage / "bytevectors.log").open("w") as log:
                run([pvs, "-raw", "-L", SITE / "scripts/pvs2c-compat.lisp", "-E", '(progn (tc "bytevector_tests") '
                     '(pvs2c-theory "bytevector_tests" t) (uiop:quit 0))'],
                    cwd=primer.parent, env=env, stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT)
            aes_ready = True
        generate = (f'(tc "{theory}") (pvs2c-theory "{theory}" t) (format t "CRYPTO-OK {theory}~%")'
                    if generator == "aes" else f'(crypto-replay-generate "{theory}" nil)')
        action = (f'(handler-case (progn {generate} (uiop:quit 0)) '
                  '(error (e) (format t "FAILED ~a~%" e) (uiop:quit 1)))')
        print(f"Generating {theory}", flush=True)
        with (stage / f"{theory}.log").open("w+", encoding="utf-8", errors="replace") as log:
            result = subprocess.run([pvs, "-raw", "-L", SITE / "scripts/pvs2c-compat.lisp",
                                    "-L", find(crypto, "crypto-random-attachments.lisp"),
                                    "-L", find(crypto, "crypto-statistics-attachments.lisp"), "-L", helper, "-E", action], cwd=source.parent,
                                    env=env, stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT,
                                    timeout=600)
            log.seek(0)
            transcript = log.read()
            if result.returncode or f"CRYPTO-OK {theory}" not in transcript:
                raise SystemExit(transcript[-10000:])
        return original, source

    for index, suite in enumerate(suites):
        theory = suite["theory"]
        if suite.get("driver"):
            if not list(stage.rglob(theory + "_c.h")):
                generate(theory, suite.get("generator"))
            for name in reversed(drivers[suite["driver"]]["theories"]):
                if not list(stage.rglob(name + "_c.h")):
                    generate(name, suite.get("generator"))
            original = find(crypto, theory + ".pvs")
            source = stage / original.relative_to(crypto)
        else:
            original, source = generate(theory, suite.get("generator"))
        suite.update(index=index, source=original.relative_to(repository).as_posix())
        if not suite.get("driver"):
            expected = re.findall(r"^\s*(\w+)\s*:\s*_TEST_\b", original.read_text(), re.M | re.I)
            if not expected:
                raise SystemExit(f"No _TEST_ declarations in {original}")
            suite["expected"] = [f"{theory}.{name} ==> true" for name in expected]
            mains.append((index, source.parent / f"pvs2c/src/{theory}.c"))
    marker.write_text(fingerprint)

    includes = [gmp / "include", runtime / "include", *sorted(stage.rglob("pvs2c/include"))]
    flags = ["emcc", "-O2", "-Wno-incompatible-pointer-types", "-Wno-deprecated-declarations",
             "-include", find(crypto, "crypto_bits_compat.h")]
    for path in includes:
        flags += ["-I", path]
    nist_flags = ["-DNIST_" + name.upper().replace("-", "_") for name in sorted(nist_sets)]
    flags += nist_flags
    objects = cache / "objects"
    shutil.rmtree(objects, ignore_errors=True)
    objects.mkdir()
    statistics = any(s.get("statistics") for s in suites)
    compression = any(s.get("driver") == "entropy" for s in suites)
    if statistics:
        flags += ["-include", find(crypto, "crypto_statistics_math.h")]
    if compression:
        flags += ["--use-port=bzip2"]
    sources = sorted(stage.rglob("*_c.c")) + sorted((runtime / "src").glob("*.c")) + [SITE / "scripts/wasm_runtime.c"]
    if compression:
        sources.append(find(crypto, "crypto_compression.c"))
    compiled = []
    for index, source in enumerate(sources):
        obj = objects / f"{index}.o"
        run([*flags, "-c", source, "-o", obj])
        compiled.append(obj)
    if statistics:
        obj = objects / "gamma.o"
        run(["em++", "-std=c++17", "-O2", "--use-port=boost_headers", "-c", find(crypto, "crypto_gamma.cc"), "-o", obj])
        compiled.append(obj)
    common = objects / "common.a"
    run(["emar", "rcs", common, *compiled])
    compiled = []
    for index, source in mains:
        obj = objects / f"main-{index}.o"
        run([*flags, f"-Dmain=example_{index}", "-c", source, "-o", obj])
        compiled.append(obj)
    dispatch = cache / "dispatch.c"
    dispatch.write_text("\n".join(f"int example_{i}(void);" for i, _ in mains) +
                        "\nint run_example(unsigned index) { switch(index) {\n" +
                        "\n".join(f"case {i}: return example_{i}();" for i, _ in mains) +
                        "\ndefault: return 2; } }\n")
    link_settings = ["--no-entry", "-sMODULARIZE=1", "-sEXPORT_ES6=1", "-sENVIRONMENT=web,worker,node",
                     "-sEXPORTED_FUNCTIONS=['_run_example','_nist_eval']", "-sEXPORTED_RUNTIME_METHODS=['ccall','FS']",
                     "-sALLOW_MEMORY_GROWTH=1", "-sMAXIMUM_MEMORY=536870912", "-sSTACK_SIZE=8388608", "-sASSERTIONS=1", "-Wl,--wrap=exp2__exp2"]
    weak = cache / "random-defaults.c"
    weak.write_text('#include <stdint.h>\n__attribute__((weak)) uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i){return 256;}\n'
                    '__attribute__((weak)) uint16_t crypto_prng_lookup(uint64_t s,uint32_t i){return 256;}\n')
    def link(destination, sources, extras=()):
        run([*flags, *sources, weak, common, gmp / "lib/libgmp.a", *extras, *link_settings, "-o", output / destination])
        stem = destination.removesuffix(".mjs")
        wasm_path, js_path = output / (stem + ".wasm"), output / destination
        digest = hashlib.sha256(wasm_path.read_bytes() + js_path.read_bytes()).hexdigest()[:16]
        module, wasm = f"{stem}-{digest}.mjs", f"{stem}-{digest}.wasm"
        (output / module).write_text(js_path.read_text().replace(stem + ".wasm", wasm))
        wasm_path.rename(output / wasm)
        js_path.unlink()
        return module
    module = link("crypto.mjs", [dispatch, SITE / "scripts/nist_bridge.c", *compiled])
    for suite in suites:
        if not suite.get("driver"):
            continue
        key = suite["driver"]
        wrapper = stage / "drivers" / key / "browser.c"
        wrapper.write_text('#include <stdio.h>\nint main(void);\n'
                           'int run_example(unsigned ignored){ if(!freopen("/runner-input","rb",stdin)) return 2;'
                           'int code=main(); fflush(stdout); fflush(stderr); return code;}\n')
        obj = objects / (key + "-main.o")
        run([*flags, "-c", drivers[key]["source"], "-o", obj])
        adapter = objects / (key + "-adapter.o")
        adapter_flags = [flag for flag in flags if not str(flag).startswith("-DNIST_")]
        adapter_flags += ["-DNIST_" + name.upper().replace("-", "_") for name in suite.get("nist", [])]
        run([*adapter_flags, "-c", SITE / "scripts/nist_extra.c", "-o", adapter])
        suite["module"] = link(key + ".mjs", [wrapper, obj, adapter], ["-sFORCE_FILESYSTEM=1", "-sINVOKE_RUN=0"])
        for name in suite.get("nist", []):
            nist_sets[name]["module"] = suite["module"]
        print(f"Linked {key}", flush=True)
    (output / "nist/manifest.json").write_text(json.dumps({"sets": nist_sets}, indent=2) + "\n")
    # Hash names prevent a new JS loader from picking up a cached older Wasm binary.
    manifest = {"module": module, "suites": suites, "emscripten": emcc_version, "inputs": inputs, "nist": nist_sets,
                "revision": subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=repository, text=True).strip()}
    generator = subprocess.run(["git", "-C", pvs.parent, "rev-parse", "HEAD"], text=True, capture_output=True)
    manifest["pvsRevision"] = generator.stdout.strip() if generator.returncode == 0 else os.environ.get("PVS_REF")
    pending = output / "manifest.pending.json"
    pending.write_text(json.dumps(manifest, indent=2) + "\n")
    run(["node", SITE / "scripts/check_crypto.mjs", pending])
    # Include all C, headers and the exact GMP source for inspection and rebuilding.
    with zipfile.ZipFile(output / "sources.zip", "w", zipfile.ZIP_DEFLATED) as archive:
        for source in stage.rglob("*"):
            if source.is_file() and source.suffix in (".c", ".h", ".pvs"):
                archive.write(source, "application/" + source.relative_to(stage).as_posix())
        for folder in ("src", "include"):
            for source in (runtime / folder).glob("*"):
                if source.suffix in (".c", ".h"):
                    archive.write(source, "runtime/" + folder + "/" + source.name)
        archive.write(gmp_source, gmp_source.name)
        archive.write(find(crypto, "crypto_bits_compat.h"), "crypto_bits_compat.h")
        archive.write(dispatch, "dispatch.c")
        archive.write(SITE / "scripts/rebuild_crypto.sh", "rebuild.sh")
        archive.write(SITE / "scripts/rebuild_crypto.py", "rebuild.py")
        archive.write(SITE / "scripts/pvs2c-compat.lisp", "generator-compat.lisp")
        archive.write(SITE / "scripts/nist_bridge.c", "nist_bridge.c")
        archive.write(SITE / "scripts/nist_extra.c", "nist_extra.c")
        archive.write(SITE / "scripts/wasm_runtime.c", "wasm_runtime.c")
        archive.write(weak, "random-defaults.c")
        for name in ("crypto_statistics_math.h", "crypto_compression.c", "crypto_gamma.cc"):
            archive.write(find(crypto, name), name)
        archive.writestr("nist-flags.json", json.dumps(nist_flags))
        archive.write(SITE / "nist-sources.json", "nist-sources.json")
        archive.writestr("manifest.json", json.dumps(manifest, indent=2))
        archive.write(pvs.parent / "LICENSE", "PVS-LICENSE")
        if statistics:
            archive.write(SITE / "lib/boost-LICENSE.txt", "BOOST-LICENSE.txt")
        if compression:
            archive.write(SITE / "lib/bzip2-LICENSE.txt", "BZIP2-LICENSE.txt")
    run(["python3", SITE / "scripts/export_crypto_sources.py", output])
    pending.rename(output / "manifest.json")
    active = {module, *(suite.get("module", module) for suite in suites)}
    for old in [*output.glob("*.mjs"), *output.glob("*.wasm")]:
        if (old.name.removesuffix(".wasm") + ".mjs" if old.suffix == ".wasm" else old.name) not in active:
            old.unlink()
    print(f"Built and checked {len(suites)} suites: {output}", flush=True)


if __name__ == "__main__":
    main()
