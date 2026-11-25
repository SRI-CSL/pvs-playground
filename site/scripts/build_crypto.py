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
    args = parser.parse_args()
    pvs = shutil.which(os.path.expanduser(args.pvs))
    if not pvs:
        parser.error("Set PVS_BIN, put pvs on PATH, or pass --pvs")
    pvs = Path(pvs).resolve()
    repository = Path(subprocess.check_output(["git", "rev-parse", "--show-toplevel"], cwd=SITE, text=True).strip())
    crypto = args.crypto_root.resolve() if args.crypto_root else find(repository, "crypto_words.pvs").parent.parent
    runtime = Path(os.environ.get("PVS2C_RUNTIME", pvs.parent / "lib/pvs2c")).resolve()
    output, cache = args.output.resolve(), args.cache.resolve()
    output.mkdir(parents=True, exist_ok=True)
    # A failed rebuild must never leave a publishable old manifest.
    (output / "manifest.json").unlink(missing_ok=True)
    cache.mkdir(parents=True, exist_ok=True)
    gmp, gmp_source, emcc_version = gmp_library(cache)
    stage = cache / "application"
    shutil.rmtree(stage, ignore_errors=True)
    stage.mkdir()
    inputs = {}
    for source in crypto.rglob("*.pvs"):
        if "pvs2c" in source.relative_to(crypto).parts:
            continue
        destination = stage / source.relative_to(crypto)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, destination)
        inputs[source.relative_to(repository).as_posix()] = hashlib.sha256(source.read_bytes()).hexdigest()
    suites = json.loads((SITE / "crypto-runners.json").read_text())
    if args.suite:
        suites = [suite for suite in suites if suite["theory"] in args.suite]
        if {suite["theory"] for suite in suites} != set(args.suite):
            parser.error("Unknown suite")
    nist_sets = prepare_nist(suites, cache, output)
    env = {**os.environ, "PVS_LIBRARY_PATH": str(stage), "PVS_LOG_DIR": str(stage)}
    helper = find(crypto, "replay-generate.lisp")
    mains = []
    aes_ready = False
    for index, suite in enumerate(suites):
        theory = suite["theory"]
        original = find(crypto, theory + ".pvs")
        source = stage / original.relative_to(crypto)
        if suite.get("generator") == "aes" and not aes_ready:
            # Match validation/check_aes.py: prime the bytevector ABI before AES.
            primer = find(stage, "bytevector_tests.pvs")
            with (stage / "bytevectors.log").open("w") as log:
                run([pvs, "-raw", "-L", SITE / "scripts/pvs2c-compat.lisp", "-E", '(progn (tc "bytevector_tests") '
                     '(pvs2c-theory "bytevector_tests" t) (uiop:quit 0))'],
                    cwd=primer.parent, env=env, stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT)
            aes_ready = True
        generate = (f'(tc "{theory}") (pvs2c-theory "{theory}" t) (format t "CRYPTO-OK {theory}~%")'
                    if suite.get("generator") == "aes" else f'(crypto-replay-generate "{theory}" nil)')
        action = (f'(handler-case (progn {generate} (uiop:quit 0)) '
                  '(error (e) (format t "FAILED ~a~%" e) (uiop:quit 1)))')
        print(f"Generating {theory}", flush=True)
        with (stage / f"{theory}.log").open("w+", encoding="utf-8", errors="replace") as log:
            result = subprocess.run([pvs, "-raw", "-L", SITE / "scripts/pvs2c-compat.lisp", "-L", helper, "-E", action], cwd=source.parent,
                                    env=env, stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT,
                                    timeout=600)
            log.seek(0)
            transcript = log.read()
            if result.returncode or f"CRYPTO-OK {theory}" not in transcript:
                raise SystemExit(transcript[-10000:])
        expected = re.findall(r"^\s*(\w+)\s*:\s*_TEST_\b", original.read_text(), re.M | re.I)
        if not expected:
            raise SystemExit(f"No _TEST_ declarations in {original}")
        suite.update(index=index, source=original.relative_to(repository).as_posix(),
                     expected=[f"{theory}.{name} ==> true" for name in expected])
        mains.append(source.parent / f"pvs2c/src/{theory}.c")

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
    sources = sorted(stage.rglob("*_c.c")) + sorted((runtime / "src").glob("*.c")) + [SITE / "scripts/nist_bridge.c"]
    compiled = []
    for index, source in enumerate(sources + mains):
        obj = objects / f"{index}.o"
        extra = [f"-Dmain=example_{mains.index(source)}"] if source in mains else []
        run([*flags, *extra, "-c", source, "-o", obj])
        compiled.append(obj)
    dispatch = cache / "dispatch.c"
    dispatch.write_text("\n".join(f"int example_{i}(void);" for i in range(len(suites))) +
                        "\nint run_example(unsigned index) { switch(index) {\n" +
                        "\n".join(f"case {i}: return example_{i}();" for i in range(len(suites))) +
                        "\ndefault: return 2; } }\n")
    run([*flags, dispatch, *compiled, gmp / "lib/libgmp.a", "--no-entry", "-sMODULARIZE=1", "-sEXPORT_ES6=1",
         "-sENVIRONMENT=web,worker,node", "-sEXPORTED_FUNCTIONS=['_run_example','_nist_eval']", "-sEXPORTED_RUNTIME_METHODS=['ccall']", "-sALLOW_MEMORY_GROWTH=1",
         "-sMAXIMUM_MEMORY=536870912", "-sSTACK_SIZE=8388608", "-sASSERTIONS=1", "-o", output / "crypto.mjs"])
    # Hash names prevent a new JS loader from picking up a cached older Wasm binary.
    digest = hashlib.sha256((output / "crypto.wasm").read_bytes() + (output / "crypto.mjs").read_bytes()).hexdigest()[:16]
    module = f"crypto-{digest}.mjs"
    wasm = f"crypto-{digest}.wasm"
    loader = (output / "crypto.mjs").read_text().replace("crypto.wasm", wasm)
    (output / module).write_text(loader)
    (output / "crypto.wasm").rename(output / wasm)
    (output / "crypto.mjs").unlink()
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
        archive.write(SITE / "scripts/pvs2c-compat.lisp", "generator-compat.lisp")
        archive.write(SITE / "scripts/nist_bridge.c", "nist_bridge.c")
        archive.writestr("nist-flags.json", json.dumps(nist_flags))
        archive.write(SITE / "nist-sources.json", "nist-sources.json")
        archive.writestr("manifest.json", json.dumps(manifest, indent=2))
        archive.write(pvs.parent / "LICENSE", "PVS-LICENSE")
    run(["python3", SITE / "scripts/export_crypto_sources.py", output])
    pending.rename(output / "manifest.json")
    for old in [*output.glob("crypto-*.mjs"), *output.glob("crypto-*.wasm")]:
        if old.name not in (module, wasm):
            old.unlink()
    print(f"Built and checked {len(suites)} suites: {output}", flush=True)


if __name__ == "__main__":
    main()
