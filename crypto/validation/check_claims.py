#!/usr/bin/env python3
"""Typecheck the standalone functional claims in a source-only PVS context."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

from pvs_cli import add_pvs_argument

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
add_pvs_argument(parser)
args = parser.parse_args()
pvs = args.pvs
with tempfile.TemporaryDirectory(prefix="crypto-claims-") as temp:
    stage = Path(temp)
    sources = [p for p in ROOT.rglob("*.pvs") if not {"pvsbin", "reproducers"}.intersection(p.parts)]
    for p in sources:
        dest = stage / p.relative_to(ROOT)
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(p, dest)
    env = dict(os.environ, PVS_LOG_DIR=temp,
               PVS_LIBRARY_PATH=os.pathsep.join(filter(None, [temp,os.environ.get("PVS_LIBRARY_PATH")])))
    for p in sorted(source for source in sources if source.stem.endswith("_claims")):
        name = p.stem
        action = (f'(handler-case (let ((th (get-typechecked-theory "{name}" nil t))) '
                  '(unless (and th (typechecked? th)) (error "Incomplete typecheck")) '
                  '(format t "~%CLAIMS-OK ~a~%" (id th)) (uiop:quit 0)) '
                  '(error (e) (format t "~%FAILED ~a~%" e) (uiop:quit 1)))')
        run = subprocess.run([pvs, "-raw", "-E", action], cwd=stage/p.parent.relative_to(ROOT),
                             stdin=subprocess.DEVNULL, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, errors="replace")
        if run.returncode or f"CLAIMS-OK {name}" not in run.stdout:
            raise SystemExit(run.stdout[-5000:])
        print(f"Typechecked {p.relative_to(ROOT)}", flush=True)
