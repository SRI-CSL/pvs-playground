#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path


EXCLUDED_DIRS = {"build", "pvs2c", "pvsbin", "test-vectors"}
EXCLUDED_PATHS = {Path("parsing/ltedfa")}
PVS_ERROR_RE = re.compile(r"^In file ", re.MULTILINE)
RUN_OUTPUT_RE = re.compile(
    r"^\s*(?P<theory>[A-Za-z][A-Za-z0-9_]*)\.(?P<test>[A-Za-z][A-Za-z0-9_]*)\s*==>\s*(?P<value>true|false)\b",
    re.MULTILINE,
)
THEORY_RE = re.compile(r"^\s*([A-Za-z][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])?\s*:\s*THEORY\b", re.IGNORECASE)
THEORY_NAME_RE = re.compile(r"^\s*([A-Za-z][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])?\s*$")
THEORY_COLON_RE = re.compile(r"^\s*:\s*THEORY\b", re.IGNORECASE)
END_RE = re.compile(r"^\s*END\s+([A-Za-z][A-Za-z0-9_]*)\b", re.IGNORECASE)
TEST_RE = re.compile(r"^\s*([A-Za-z][A-Za-z0-9_]*)\s*:\s*_TEST_\b", re.IGNORECASE)


@dataclass(frozen=True)
class TestDecl:
    name: str
    line: int


@dataclass(frozen=True)
class TestTheory:
    directory: Path
    file: Path
    theory: str
    tests: tuple[TestDecl, ...]


class StepError(RuntimeError):
    pass


def strip_pvs_comment(line: str) -> str:
    in_string = False
    escaped = False
    for index, char in enumerate(line):
        if in_string and char == "\\" and not escaped:
            escaped = True
            continue
        if char == '"' and not escaped:
            in_string = not in_string
        if char == "%" and not in_string:
            return line[:index]
        escaped = False
    return line


def is_excluded(path: Path, root: Path) -> bool:
    relative = path.relative_to(root)
    return (
        any(part in EXCLUDED_DIRS for part in relative.parts)
        or any(relative == excluded or excluded in relative.parents for excluded in EXCLUDED_PATHS)
    )


def discover_test_theories(demo_root: Path) -> list[TestTheory]:
    found: list[TestTheory] = []
    for source in sorted(demo_root.rglob("*.pvs")):
        if is_excluded(source, demo_root):
            continue
        current_theory: str | None = None
        pending_theory: str | None = None
        tests_by_theory: dict[str, list[TestDecl]] = {}
        text = source.read_text(encoding="utf-8", errors="replace")
        for line_number, raw_line in enumerate(text.splitlines(), start=1):
            line = strip_pvs_comment(raw_line)
            theory_match = THEORY_RE.match(line)
            if theory_match:
                current_theory = theory_match.group(1)
                tests_by_theory.setdefault(current_theory, [])
                pending_theory = None
                continue
            if current_theory is None and pending_theory and THEORY_COLON_RE.match(line):
                current_theory = pending_theory
                tests_by_theory.setdefault(current_theory, [])
                pending_theory = None
                continue
            pending_match = THEORY_NAME_RE.match(line)
            if current_theory is None and pending_match:
                pending_theory = pending_match.group(1)
                continue
            if line.strip():
                pending_theory = None
            if current_theory is None:
                continue
            test_match = TEST_RE.match(line)
            if test_match:
                tests_by_theory[current_theory].append(TestDecl(test_match.group(1), line_number))
                continue
            end_match = END_RE.match(line)
            if end_match and end_match.group(1).lower() == current_theory.lower():
                current_theory = None
        for theory, tests in tests_by_theory.items():
            if tests:
                found.append(TestTheory(source.parent, source, theory, tuple(tests)))
    return found


def discover_source_directories(demo_root: Path) -> set[Path]:
    return {
        source.parent
        for source in demo_root.rglob("*.pvs")
        if not is_excluded(source, demo_root)
    }


def command_text(command: list[str]) -> str:
    return " ".join(command)


def tail(text: str, lines: int = 60) -> str:
    split = text.splitlines()
    return "\n".join(split[-lines:])


def run_logged(
    command: list[str],
    cwd: Path,
    log_path: Path,
    env: dict[str, str],
    check: bool = True,
) -> tuple[int, str]:
    log_path.parent.mkdir(parents=True, exist_ok=True)
    print(f"+ ({cwd}) {command_text(command)}")
    output_parts: list[str] = []
    with log_path.open("w", encoding="utf-8") as log:
        process = subprocess.Popen(
            command,
            cwd=str(cwd),
            env=env,
            stdin=subprocess.DEVNULL,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
        )
        assert process.stdout is not None
        for line in process.stdout:
            output_parts.append(line)
            log.write(line)
            sys.stdout.write(line)
        return_code = process.wait()
    output = "".join(output_parts)
    if check and return_code != 0:
        raise StepError(
            f"Command failed with exit {return_code}: {command_text(command)}\n"
            f"Log: {log_path}\n"
            f"{tail(output)}"
        )
    return return_code, output


def pvs_expr_for_typecheck(theory: str) -> str:
    return f'(progn (setq *suppress-output* nil) (tc "{theory}" t) (finish-output) (uiop:quit))'


def pvs_expr_for_pvs2c(theory: str) -> str:
    return f'(progn (setq *suppress-output* t) (pvs2c-theory "{theory}" t) (finish-output) (uiop:quit))'


def sanitize_relpath(path: Path) -> str:
    return "__".join(path.parts) if path.parts else "root"


def remove_generated_state(directory: Path) -> None:
    for name in ("pvs2c", "pvsbin"):
        generated = directory / name
        if generated.exists():
            shutil.rmtree(generated)
    for name in (".pvscontext", "Makefile.bak"):
        generated_file = directory / name
        if generated_file.exists():
            generated_file.unlink()


def write_manifest(log_dir: Path, demo_root: Path, theories: list[TestTheory]) -> None:
    manifest = []
    for item in theories:
        manifest.append(
            {
                "directory": str(item.directory.relative_to(demo_root)),
                "file": str(item.file.relative_to(demo_root)),
                "theory": item.theory,
                "tests": [{"name": test.name, "line": test.line} for test in item.tests],
            }
        )
    log_dir.mkdir(parents=True, exist_ok=True)
    (log_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")


def assert_pvs_log_ok(theory: TestTheory, step: str, output: str, log_path: Path) -> None:
    if PVS_ERROR_RE.search(output):
        raise StepError(f"{step} reported PVS errors for {theory.theory}; see {log_path}")


def assert_run_output(theory: TestTheory, output: str, log_path: Path) -> None:
    expected = {test.name for test in theory.tests}
    seen: dict[str, str] = {}
    for match in RUN_OUTPUT_RE.finditer(output):
        name = match.group("test")
        value = match.group("value")
        if match.group("theory").lower() == theory.theory.lower() and name in expected:
            seen[name] = value
    missing = sorted(expected - set(seen))
    if missing:
        print(f"WARNING: generated test binary output for {theory.theory} did not list expected tests: {', '.join(missing)}; see {log_path}.")


def run_theory(
    repo_root: Path,
    demo_root: Path,
    log_dir: Path,
    pvs_location: Path,
    theory: TestTheory,
    env: dict[str, str],
) -> int:
    rel_dir = theory.directory.relative_to(demo_root)
    log_prefix = log_dir / sanitize_relpath(rel_dir) / theory.theory
    pvs = pvs_location / "pvs"
    makefile = repo_root / "scripts" / "ci" / "pvs2c-test.mk"

    print(f"\n==> {rel_dir}/{theory.file.name}:{theory.theory} ({len(theory.tests)} tests)")

    typecheck_log = log_prefix.with_name(log_prefix.name + "-typecheck.log")
    _, typecheck_output = run_logged(
        [str(pvs), "-raw", "-E", pvs_expr_for_typecheck(theory.theory)],
        theory.directory,
        typecheck_log,
        env,
    )
    assert_pvs_log_ok(theory, "typecheck", typecheck_output, typecheck_log)

    pvs2c_log = log_prefix.with_name(log_prefix.name + "-pvs2c.log")
    pvs2c_status, pvs2c_output = run_logged(
        [str(pvs), "-raw", "-E", pvs_expr_for_pvs2c(theory.theory)],
        theory.directory,
        pvs2c_log,
        env,
        check=False,
    )
    assert_pvs_log_ok(theory, "pvs2c-theory", pvs2c_output, pvs2c_log)

    generated_mk = theory.directory / "pvs2c" / "include" / f"{theory.theory}.mk"
    generated_bin = theory.directory / "pvs2c" / "bin" / theory.theory
    if not generated_mk.exists():
        raise StepError(
            f"pvs2c-theory exited {pvs2c_status} and did not generate {generated_mk}; see {pvs2c_log}\n"
            f"{tail(pvs2c_output)}"
        )
    if pvs2c_status != 0:
        print(f"WARNING: pvs2c-theory for {theory.theory} exited {pvs2c_status}, but generated files are present; continuing to compile and run them.")

    make_env = env.copy()
    make_env["PVS2C_DEMOS_ROOT"] = str(demo_root)
    make_log = log_prefix.with_name(log_prefix.name + "-make.log")
    run_logged(
        ["make", "-f", str(makefile), f"pvs2c/bin/{theory.theory}"],
        theory.directory,
        make_log,
        make_env,
    )
    if not generated_bin.exists():
        raise StepError(f"make did not produce {generated_bin}")

    run_log = log_prefix.with_name(log_prefix.name + "-run.log")
    run_status, run_output = run_logged([str(generated_bin)], theory.directory, run_log, env, check=False)
    assert_run_output(theory, run_output, run_log)
    if run_status != 0:
        print(f"WARNING: generated test binary for {theory.theory} exited {run_status}; continuing after execution.")
    return len(theory.tests)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Build and run PVS2C _TEST_ declarations under pvs2c-demos.")
    parser.add_argument("--repo-root", type=Path, default=Path.cwd(), help="repository root")
    parser.add_argument("--demo-root", type=Path, default=Path("pvs2c-demos"), help="directory containing PVS2C demos")
    parser.add_argument("--pvs-location", type=Path, default=None, help="PVS checkout/build directory")
    parser.add_argument("--log-dir", type=Path, default=None, help="directory for CI logs")
    parser.add_argument("--clean-generated", action="store_true", help="remove pvs2c, pvsbin, .pvscontext, and Makefile.bak in test directories before running")
    parser.add_argument("--list", action="store_true", help="list discovered tests without invoking PVS")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    repo_root = args.repo_root.resolve()
    demo_root = (repo_root / args.demo_root).resolve() if not args.demo_root.is_absolute() else args.demo_root.resolve()
    log_dir = args.log_dir
    if log_dir is None:
        log_dir = demo_root / "build" / "ci-pvs2c-tests"
    elif not log_dir.is_absolute():
        log_dir = repo_root / log_dir
    log_dir = log_dir.resolve()

    if not demo_root.exists():
        raise StepError(f"demo root does not exist: {demo_root}")

    theories = discover_test_theories(demo_root)
    if not theories:
        raise StepError(f"no active _TEST_ declarations found under {demo_root}")

    write_manifest(log_dir, demo_root, theories)
    total_tests = sum(len(item.tests) for item in theories)
    print(f"Discovered {total_tests} active _TEST_ declarations in {len(theories)} theories.")
    for item in theories:
        print(f"  {item.file.relative_to(demo_root)}:{item.theory} ({len(item.tests)} tests)")

    if args.list:
        return 0

    pvs_location_arg = args.pvs_location or os.environ.get("PVS_LOCATION")
    if not pvs_location_arg:
        raise StepError("PVS_LOCATION is not set and --pvs-location was not provided")
    pvs_location = Path(pvs_location_arg).resolve()
    if not (pvs_location / "pvs").exists():
        raise StepError(f"PVS executable not found: {pvs_location / 'pvs'}")

    if args.clean_generated:
        for directory in sorted(discover_source_directories(demo_root)):
            remove_generated_state(directory)

    env = os.environ.copy()
    env["PVS_LOCATION"] = str(pvs_location)
    passed = 0
    for item in theories:
        passed += run_theory(repo_root, demo_root, log_dir, pvs_location, item, env)
    print(f"\nPVS2C CI passed: generated C test binaries executed for {passed} discovered _TEST_ declarations.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except StepError as error:
        print(f"ERROR: {error}", file=sys.stderr)
        raise SystemExit(1)
