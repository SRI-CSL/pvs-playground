#!/usr/bin/env python3
"""Compile the checked-in WAT examples and extract PVS-ready body hex."""

from __future__ import annotations

import argparse
import shutil
import subprocess
from pathlib import Path

from extract_wasm_body import code_bodies, hex_lines


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--examples", type=Path, default=Path("examples"))
    parser.add_argument("--out-dir", type=Path, default=Path("build/wat-bodies"))
    args = parser.parse_args()

    wat2wasm = shutil.which("wat2wasm")
    if wat2wasm is None:
        raise SystemExit("wat2wasm was not found; install WABT to rebuild .wasm files")

    args.out_dir.mkdir(parents=True, exist_ok=True)
    for wat in sorted(args.examples.glob("*.wat")):
        wasm = args.out_dir / f"{wat.stem}.wasm"
        body_hex = args.out_dir / f"{wat.stem}.body.hex"
        subprocess.run([wat2wasm, str(wat), "-o", str(wasm)], check=True)
        bodies = code_bodies(wasm.read_bytes())
        if len(bodies) != 1:
            raise SystemExit(f"{wat} compiled to {len(bodies)} bodies; expected 1")
        body_hex.write_text(hex_lines(bodies[0]) + "\n", encoding="utf-8")
        print(f"{wat} -> {body_hex}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
