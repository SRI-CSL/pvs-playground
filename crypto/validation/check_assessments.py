#!/usr/bin/env python3
"""Typecheck SP 800-22/90B/90C, generate C, compile and run the selected fixtures."""
import argparse
import gzip
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile

from pvs_cli import add_pvs_argument, pvs2c_runtime

ROOT = Path(__file__).resolve().parents[1]
SUITES = {
    "sts": ("statistical_tests/sts_suite", "statistics_checks.c", "statistical_tests/pi_sample.bin.gz"),
    "entropy": ("random_bits/entropy_assessment", "entropy_assessment_checks.c", "random_bits/rand1_short.bin.gz"),
    "constructions": ("random_bits/rbg_profiles", "rbg_profile_checks.c", None),
}

def run(stage, name, pvs):
    leaf, main, fixture = SUITES[name]
    for folder in ROOT.iterdir():
        if folder.name not in ("reproducers", "validation") and folder.is_dir():
            for source in folder.glob("*.pvs"):
                dest = stage / source.relative_to(ROOT)
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(source, dest)
    theory = Path(leaf).name
    directory = stage / Path(leaf).parent
    env = dict(os.environ, PVS_LOG_DIR=str(stage),
               PVS_LIBRARY_PATH=os.pathsep.join(filter(None, [str(stage), os.environ.get("PVS_LIBRARY_PATH")])))
    action = (f'(handler-case (progn (crypto-replay-generate "{theory}" nil) (uiop:quit)) '
              '(error (e) (format t "~%FAILED ~a~%" e) (uiop:quit 1)))')
    shared = ROOT / "crypto_prelude"
    with (stage / "generate.log").open("w") as log:
        cmd = [pvs, "-raw", "-L", ROOT / "validation/replay-generate.lisp",
               "-L", shared / "crypto-random-attachments.lisp", "-L", shared / "crypto-statistics-attachments.lisp",
               "-E", action]
        result = subprocess.run(cmd, cwd=directory, env=env, stdin=subprocess.DEVNULL, stdout=log, stderr=subprocess.STDOUT)
    output = (stage / "generate.log").read_text(errors="replace")
    if result.returncode or f"CRYPTO-OK {theory}" not in output:
        raise SystemExit(output[-5000:])
    print(f"Typechecked and generated {leaf}", flush=True)
    runtime = pvs2c_runtime(pvs)
    generated = sorted(stage.glob("*/pvs2c"))
    sources = [p for d in generated for p in sorted((d / "src").glob("*_c.c"))]
    sanitizer = ["-fsanitize=address,undefined", "-fno-sanitize-recover=all"]
    cppflags = shlex.split(os.environ.get("CPPFLAGS", ""))
    cflags = shlex.split(os.environ.get("CFLAGS", ""))
    flags = ["-O2", "-g", *cflags, *cppflags, "-Werror=int-to-pointer-cast", *sanitizer,
             "-Wno-incompatible-pointer-types", "-Wno-deprecated-declarations",
             "-include", shared / "crypto_bits_compat.h", "-I", runtime / "include"]
    for d in generated:
        flags += ["-I", d / "include"]
    cc = shlex.split(os.environ.get("CC", "cc"))
    linker = cc
    objects = []
    libs = []
    if name in ("sts", "entropy"):
        flags += ["-include", shared / "crypto_statistics_math.h"]
        linker = shlex.split(os.environ.get("CXX", "c++"))
        cxxflags = shlex.split(os.environ.get("CXXFLAGS", ""))
        obj = stage / "gamma.o"
        subprocess.run([*linker, "-std=c++17", "-O2", *cxxflags, *cppflags, *sanitizer,
                        "-c", shared / "crypto_gamma.cc", "-o", obj], check=True)
        objects.append(obj)
        libs.append("-lm")
    if name == "entropy":
        sources.append(shared / "crypto_compression.c")
        libs.append("-lbz2")
    gmp_cflags = shlex.split(subprocess.check_output(["pkg-config", "--cflags", "gmp"], text=True))
    libs += shlex.split(subprocess.check_output(["pkg-config", "--libs", "gmp"], text=True))
    for i, source in enumerate([*sources, ROOT / "validation" / main]):
        obj = stage / f"{i}-{source.stem}.o"
        subprocess.run([*cc, *flags, *gmp_cflags, "-c", source, "-o", obj], check=True)
        objects.append(obj)
    binary = stage / "checked"
    ldflags = shlex.split(os.environ.get("LDFLAGS", ""))
    subprocess.run([*linker, *ldflags, *sanitizer, *objects, runtime / "lib/libpvs-prelude.a",
                    *libs, "-o", binary], check=True)
    data = gzip.decompress((ROOT / fixture).read_bytes()) if fixture else None
    subprocess.run([binary], input=data, check=True)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("suite", choices=SUITES)
    add_pvs_argument(parser)
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix=f"pvs-{args.suite}-") as tmp:
        run(Path(tmp), args.suite, args.pvs)
