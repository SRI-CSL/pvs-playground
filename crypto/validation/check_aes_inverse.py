#!/usr/bin/env python3
"""Force offline replay of the AES and mode inverse proofs from source."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

from pvs_cli import add_pvs_argument

ROOT = Path(__file__).resolve().parents[1]
THEORIES = {
    "crypto_prelude": (
        "crypto_octets", "crypto_blocks", "simplifications", "hex", "bytevectors",
        "sums_def", "sums_abelian_group", "sums_ring", "polynomials",
        "polynomials_division", "pol_modulo", "sq_matrices", "vectors",
        "abelian_byte_prerequisites",
    ),
    "aes": ("Rijndael", "aes_fips197", "Rijndael_proofs", "aes_fips197_proofs"),
    "modes": ("aes_modes", "aes_modes_proofs"),
}


def replay(stage, pvs, nasalib):
    # PVS may save compiled libraries or update a proof file while typechecking.
    # Give it private copies of both the application and its algebra library.
    algebra = stage / "libraries" / "algebra"
    algebra.mkdir(parents=True)
    for pattern in ("*.pvs", "*.prf", "pvs-strategies"):
        for path in (nasalib / "algebra").glob(pattern):
            shutil.copyfile(path, algebra / path.name)
    for directory, names in THEORIES.items():
        dest = stage / directory
        dest.mkdir()
        for name in names:
            pvsfile = ROOT / directory / f"{name}.pvs"
            shutil.copyfile(pvsfile, dest / pvsfile.name)
            proof = pvsfile.with_suffix(".prf")
            if proof.is_file():
                shutil.copyfile(proof, dest / proof.name)
    env = dict(os.environ, PVS_LOG_DIR=str(stage), PVS_LIBRARY_PATH=str(algebra.parent))
    for directory, names in THEORIES.items():
        forms = " ".join(f'(inverse-replay "{name}")' for name in names)
        action = (f'(handler-case (progn {forms} (uiop:quit 0)) '
                  '(error (e) (format t "~%FAILED ~a~%" e) (uiop:quit 1)))')
        command = [pvs, "-raw", "-L", ROOT / "validation/replay-aes-inverse.lisp", "-E", action]
        with (stage / f"{directory}.log").open("w+") as log:
            result = subprocess.run(command, cwd=stage / directory, env=env, stdin=subprocess.DEVNULL,
                                    stdout=log, stderr=subprocess.STDOUT)
            log.seek(0)
            report = [line.rstrip() for line in log if line.startswith(("Checked ", "Open ", "FAILED "))]
            print("\n".join(report), flush=True)
            if result.returncode or len([s for s in report if s.startswith("Checked ")]) != len(names):
                log.seek(0)
                raise SystemExit("".join(log.readlines()[-35:]))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    add_pvs_argument(parser)
    parser.add_argument("--nasalib", type=Path, required=True, help="NASAlib directory containing algebra")
    args = parser.parse_args()
    if not (args.nasalib / "algebra/group.pvs").is_file():
        parser.error("--nasalib must contain algebra/group.pvs")
    with tempfile.TemporaryDirectory(prefix="aes-inverse-") as temp:
        replay(Path(temp), args.pvs, args.nasalib.expanduser().resolve())
