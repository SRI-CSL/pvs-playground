#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class TestCase:
    number: str
    valid: bool
    test_bytes: bytes
    skip_bytes: bytes = b""
    replace_bytes: bytes = b""


VALID_HEX_RE = re.compile(r"^([0-9.]+)\s*:\s*valid hex\s*:\s*(.+)$", re.IGNORECASE)
VALID_RE = re.compile(r"^([0-9.]+)\s*:\s*valid\s*:\s*(.*)$", re.IGNORECASE)
INVALID_HEX_RE = re.compile(
    r"^([0-9.]+)\s*:\s*invalid hex\s*:\s*([0-9a-f A-F]+)\s*:\s*([^:]+)\s*:\s*(.+)$",
    re.IGNORECASE,
)


def from_hex(text: str) -> bytes:
    return bytes.fromhex("".join(text.split()))


def parse_expected(path: Path) -> list[TestCase]:
    cases: list[TestCase] = []
    seen: set[str] = set()
    for line_number, raw in enumerate(path.read_text(encoding="ascii").splitlines(), start=1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue

        invalid = INVALID_HEX_RE.match(line)
        if invalid:
            number, test_hex, skip_hex, replace_hex = invalid.groups()
            skip_text = skip_hex.strip()
            case = TestCase(
                number=number,
                valid=False,
                test_bytes=from_hex(test_hex),
                skip_bytes=b"" if skip_text == "nothing" else from_hex(skip_text),
                replace_bytes=from_hex(replace_hex),
            )
        else:
            valid_hex = VALID_HEX_RE.match(line)
            if valid_hex:
                number, test_hex = valid_hex.groups()
                case = TestCase(number=number, valid=True, test_bytes=from_hex(test_hex))
            else:
                valid = VALID_RE.match(line)
                if not valid:
                    raise ValueError(f"{path}:{line_number}: unsupported utf8tests line: {raw!r}")
                number, payload = valid.groups()
                case = TestCase(number=number, valid=True, test_bytes=payload.encode("ascii"))

        if case.number in seen:
            raise ValueError(f"{path}:{line_number}: duplicate test number {case.number}")
        seen.add(case.number)
        cases.append(case)
    return cases


def parse_artifact(path: Path) -> dict[str, bytes]:
    table: dict[str, bytes] = {}
    for line_number, raw in enumerate(path.read_bytes().splitlines(), start=1):
        parts = raw.split(b":", 2)
        if len(parts) != 3:
            raise ValueError(f"{path}:{line_number}: malformed artifact line")
        number = parts[0].decode("ascii")
        status = parts[1].decode("ascii")
        if status not in {"valid", "invalid"}:
            raise ValueError(f"{path}:{line_number}: unknown status {status!r}")
        if number in table:
            raise ValueError(f"{path}:{line_number}: duplicate test number {number}")
        table[number] = parts[2]
    return table


def hex_bytes(data: bytes) -> str:
    return "nothing" if not data else " ".join(f"{byte:02x}" for byte in data)


def check_artifact(expected_path: Path, artifact_path: Path, mode: str) -> int:
    expected = parse_expected(expected_path)
    artifact = parse_artifact(artifact_path)
    failures: list[str] = []

    if len(artifact) != len(expected):
        failures.append(f"expected {len(expected)} cases, got {len(artifact)}")

    for case in expected:
        if case.number not in artifact:
            failures.append(f"{case.number}: missing artifact case")
            continue
        want = case.test_bytes if case.valid else (
            case.skip_bytes if mode == "skip" else case.replace_bytes
        )
        got = artifact[case.number]
        if got != want:
            failures.append(
                f"{case.number}: expected {hex_bytes(want)}; got {hex_bytes(got)}"
            )

    for number in artifact:
        if all(case.number != number for case in expected):
            failures.append(f"{number}: unexpected artifact case")

    if failures:
        print(f"FAIL utf8tests {mode}: {len(failures)} mismatches")
        for failure in failures[:25]:
            print(f"  {failure}")
        if len(failures) > 25:
            print(f"  ... {len(failures) - 25} more")
        return 1

    print(f"PASS utf8tests {mode}: {len(expected)} cases")
    return 0


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description="Validate utf8tests artifacts.")
    parser.add_argument("--expected", type=Path, required=True)
    parser.add_argument("--skip", type=Path)
    parser.add_argument("--replace", type=Path)
    args = parser.parse_args(argv)

    if args.skip is None and args.replace is None:
        parser.error("at least one of --skip or --replace is required")

    rc = 0
    if args.skip is not None:
        rc |= check_artifact(args.expected, args.skip, "skip")
    if args.replace is not None:
        rc |= check_artifact(args.expected, args.replace, "replace")
    return rc


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
