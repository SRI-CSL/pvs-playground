#!/usr/bin/env python3
"""Extract WebAssembly function-body payloads as hex.

The PVS interpreter in this demo starts at a Wasm function body payload: the
local-declaration vector followed by instruction bytes.  In a .wasm module,
each code-section body is wrapped in a u32 body size.  This script removes that
wrapper and prints the payload that the PVS interpreter expects.
"""

from __future__ import annotations

import argparse
from pathlib import Path


def read_u32_leb(data: bytes, offset: int) -> tuple[int, int]:
    result = 0
    shift = 0
    start = offset
    while offset < len(data):
        byte = data[offset]
        offset += 1
        result |= (byte & 0x7F) << shift
        if byte < 0x80:
            return result, offset
        shift += 7
        if shift >= 35:
            break
    raise ValueError(f"invalid u32 LEB128 at byte {start}")


def code_bodies(module: bytes) -> list[bytes]:
    if len(module) < 8 or module[:4] != b"\0asm" or module[4:8] != b"\x01\0\0\0":
        raise ValueError("not a WebAssembly 1.0 module")

    offset = 8
    while offset < len(module):
        section_id = module[offset]
        offset += 1
        section_size, offset = read_u32_leb(module, offset)
        section_end = offset + section_size
        if section_end > len(module):
            raise ValueError("section extends beyond end of file")

        if section_id == 10:
            count, body_offset = read_u32_leb(module, offset)
            bodies: list[bytes] = []
            for _ in range(count):
                body_size, body_offset = read_u32_leb(module, body_offset)
                body_end = body_offset + body_size
                if body_end > section_end:
                    raise ValueError("function body extends beyond code section")
                bodies.append(module[body_offset:body_end])
                body_offset = body_end
            return bodies

        offset = section_end

    raise ValueError("module has no code section")


def hex_lines(data: bytes, width: int = 16) -> str:
    rows = []
    for start in range(0, len(data), width):
        rows.append(" ".join(f"{byte:02X}" for byte in data[start : start + width]))
    return "\n".join(rows)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("module", type=Path)
    parser.add_argument("--body", type=int, default=0, help="zero-based code body index")
    parser.add_argument("--output", type=Path, help="write hex to this path")
    parser.add_argument("--list", action="store_true", help="list body sizes and exit")
    args = parser.parse_args()

    bodies = code_bodies(args.module.read_bytes())
    if args.list:
        for i, body in enumerate(bodies):
            print(f"{i}: {len(body)} bytes")
        return 0

    if args.body < 0 or args.body >= len(bodies):
        raise SystemExit(f"body index {args.body} out of range 0..{len(bodies) - 1}")

    text = hex_lines(bodies[args.body]) + "\n"
    if args.output:
        args.output.write_text(text, encoding="utf-8")
    else:
        print(text, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
