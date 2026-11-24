#!/usr/bin/env python3
"""Typecheck, translate and run a standalone PVS2C regression in a clean context."""
import argparse
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT.parent / "validation"))
from pvs_cli import add_pvs_argument, pvs2c_runtime

def run(theory, stage, pvs):
    source = stage / theory.name
    shutil.copy(theory, source)
    name = theory.stem
    if not re.fullmatch(r"[A-Za-z][\w]*", name):
        raise ValueError("Expected a PVS theory with an identifier matching its filename")
    action = (f'(handler-case (progn (tc "{name}") (pvs2c-theory "{name}" t) (uiop:quit 0)) '
              '(error (e) (format t "~%Failed: ~a~%" e) (uiop:quit 1)))')
    runtime = pvs2c_runtime(pvs)
    env = dict(os.environ, PVS_LOG_DIR=str(stage))
    subprocess.run([pvs, "-raw", "-E", action], cwd=stage, env=env,
                   stdin=subprocess.DEVNULL, check=True)
    src = stage / "pvs2c/src"
    if not (src / f"{name}_c.c").is_file():
        raise SystemExit(f"{name}: translation stopped before generating the theory C file")
    gmp = shlex.split(subprocess.check_output(["pkg-config", "--cflags", "--libs", "gmp"], text=True))
    cc = shlex.split(os.environ.get("CC", "cc"))
    if theory.resolve() == ROOT / "aes-array/fixed_array.pvs":
        generated = (src / "fixed_array_c.c").read_text()
        _, _, body = generated.partition("fixed_array__block_t fixed_array__complement(")
        if not re.search(r"new_fixed_array__block\(16\)", body) or not re.search(r"for \(.*< 16;", body):
            bounds = [line.strip() for line in body.splitlines() if "new_fixed_array__block(" in line or "for (" in line]
            raise SystemExit("\n".join([*bounds, "Expected an allocation and loop bound of 16."]))
        binary = stage / "check"
        subprocess.run([*cc, "-O1", "-g", "-fsanitize=address", "-fno-sanitize-recover=all",
                        "-I", runtime / "include", "-I", stage / "pvs2c/include", ROOT / "aes-array/check.c",
                        src / "fixed_array_c.c", runtime / "lib/libpvs-prelude.a", *gmp, "-o", binary], check=True)
        subprocess.run([binary], check=True)
        return
    expected = set(re.findall(r"^\s*(\w+)\s*:\s*_TEST_\b", source.read_text(), re.M | re.I))
    if not expected:
        # Diagnose the emitted translation unit statically. No executable is linked.
        for unit in sorted(src.glob("*_c.c")):
            subprocess.run([*cc, "-std=c11", "-O1", "-Werror=uninitialized", "-fsyntax-only",
                            "-I", runtime / "include", "-I", stage / "pvs2c/include",
                            *shlex.split(subprocess.check_output(["pkg-config", "--cflags", "gmp"], text=True)),
                            unit], check=True)
        print(f"{name}: generated C passed the static compiler check")
        return
    exe = stage / name
    subprocess.run([*cc, "-std=c11", "-O1", "-g", "-fsanitize=address,undefined",
                    "-fno-sanitize-recover=all", "-Wno-deprecated-declarations",
                    "-I", runtime / "include", "-I", stage / "pvs2c/include",
                    *sorted(src.glob("*_c.c")), src / f"{name}.c",
                    runtime / "lib/libpvs-prelude.a", *gmp, "-o", exe], check=True)
    test = subprocess.run([exe], capture_output=True, text=True)
    print(test.stdout, end="")
    print(test.stderr, file=sys.stderr, end="")
    actual = set(re.findall(rf"^{name}\.(\w+) ==> true$", test.stdout, re.M))
    if test.returncode or not expected or expected != actual:
        raise SystemExit(f"{name}: executable returned {test.returncode}, unconfirmed {sorted(expected - actual)}")
    print(f"{name}: all {len(expected)} results matched")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("theory", type=Path, help="standalone .pvs file with _TEST_ declarations")
    add_pvs_argument(parser)
    parser.add_argument("--keep", type=Path, help="new directory in which to retain generated C")
    args = parser.parse_args()
    pvs = args.pvs
    if args.keep:
        args.keep.mkdir()
        run(args.theory, args.keep.resolve(), pvs)
    else:
        with tempfile.TemporaryDirectory(prefix="pvs-reproducer-") as temp:
            run(args.theory, Path(temp), pvs)
