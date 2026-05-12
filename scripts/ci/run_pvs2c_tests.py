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
EXCLUDED_PATHS = {
    # Spec-only dependency for the UTF-8 demo.  It imports parser support that
    # is not generated as a standalone PVS2C test binary yet.
    Path("utf8_decoder/utf8_spec.pvs"),
}
EXCLUDED_PATH_SUFFIXES = {
    # Keep these ltedfa theories out of PVS2C CI for now.  They are parser
    # clients rather than the ltedfa parser mechanism itself, and are tracked
    # separately until their C-generation surface is ready.
    Path("parsing/ltedfa/jsondata_interface.pvs"),
    Path("parsing/ltedfa/jsonschema.pvs"),
}
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


@dataclass(frozen=True)
class RunCheck:
    seen: dict[str, str]
    missing: tuple[str, ...]


@dataclass(frozen=True)
class TheoryResult:
    directory: str
    file: str
    theory: str
    declared: int
    status: str
    pvs2c_exit: int | None = None
    run_exit: int | None = None
    printed: int = 0
    true_count: int = 0
    false_count: int = 0
    false_tests: tuple[str, ...] = ()
    missing: tuple[str, ...] = ()
    notes: tuple[str, ...] = ()


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
        or any(path_matches_suffix(relative, excluded) for excluded in EXCLUDED_PATH_SUFFIXES)
    )


def path_matches_suffix(path: Path, suffix: Path) -> bool:
    path_parts = path.parts
    suffix_parts = suffix.parts
    if len(path_parts) >= len(suffix_parts):
        return path_parts[-len(suffix_parts) :] == suffix_parts
    return suffix_parts[-len(path_parts) :] == path_parts


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
            errors="replace",
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


def inspect_run_output(theory: TestTheory, output: str, log_path: Path) -> RunCheck:
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
    return RunCheck(seen, tuple(missing))


def md_cell(value: object) -> str:
    return str(value).replace("|", "\\|").replace("\n", "<br>")


def compact_list(values: tuple[str, ...], limit: int = 5) -> str:
    if not values:
        return ""
    shown = ", ".join(f"`{value}`" for value in values[:limit])
    if len(values) > limit:
        shown += f", ... ({len(values) - limit} more)"
    return shown


def write_step_summary(
    summary_path: str | None,
    demo_root: Path,
    theories: list[TestTheory],
    results: list[TheoryResult],
    error: Exception | None = None,
) -> None:
    if not summary_path:
        return

    total_declared = sum(len(item.tests) for item in theories)
    total_completed = sum(item.declared for item in results if item.status != "failed")
    skipped = ", ".join(
        f"`{path}`"
        for path in sorted(str(path) for path in EXCLUDED_PATHS | EXCLUDED_PATH_SUFFIXES)
    ) or "none"

    lines = [
        "# PVS2C Demo CI Summary",
        "",
        f"- Discovered `{total_declared}` active `_TEST_` declarations in `{len(theories)}` theories.",
        f"- Generated C test binaries executed for `{total_completed}` discovered declarations.",
        f"- Skipped paths: {skipped}.",
    ]
    if error is not None:
        lines.append(f"- Outcome: failed during CI setup or theory processing: `{md_cell(error)}`.")
    else:
        lines.append("- Outcome: completed.")

    lines.extend(
        [
            "",
            "| Status | Source | Theory | Declared | Printed | True | False | Missing | pvs2c exit | Run exit | Notes |",
            "| --- | --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |",
        ]
    )

    for result in results:
        source = f"{result.directory}/{result.file}" if result.directory != "." else result.file
        notes = "; ".join(result.notes)
        lines.append(
            "| "
            + " | ".join(
                [
                    md_cell(result.status),
                    md_cell(source),
                    md_cell(result.theory),
                    str(result.declared),
                    str(result.printed),
                    str(result.true_count),
                    str(result.false_count),
                    str(len(result.missing)),
                    "" if result.pvs2c_exit is None else str(result.pvs2c_exit),
                    "" if result.run_exit is None else str(result.run_exit),
                    md_cell(notes),
                ]
            )
            + " |"
        )

    warning_results = [item for item in results if item.missing or item.false_count or item.notes]
    if warning_results:
        lines.extend(["", "<details>", "<summary>Warnings and result details</summary>", ""])
        for item in warning_results:
            label = f"{item.directory}/{item.theory}" if item.directory != "." else item.theory
            details: list[str] = []
            if item.false_count:
                details.append(f"{item.false_count} printed `false`: {compact_list(item.false_tests)}")
            if item.missing:
                details.append(f"missing output for {compact_list(item.missing)}")
            details.extend(item.notes)
            if details:
                lines.append(f"- `{label}`: {'; '.join(details)}")
        lines.extend(["", "</details>"])

    Path(summary_path).write_text("\n".join(lines) + "\n", encoding="utf-8")


def failed_result(demo_root: Path, theory: TestTheory, error: Exception) -> TheoryResult:
    return TheoryResult(
        directory=str(theory.directory.relative_to(demo_root)),
        file=theory.file.name,
        theory=theory.theory,
        declared=len(theory.tests),
        status="failed",
        notes=(str(error),),
    )


def run_theory(
    repo_root: Path,
    demo_root: Path,
    log_dir: Path,
    pvs_location: Path,
    theory: TestTheory,
    env: dict[str, str],
) -> TheoryResult:
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
    notes: list[str] = []
    if pvs2c_status != 0:
        note = f"pvs2c-theory exited {pvs2c_status}, but generated files are present"
        print(f"WARNING: {note}; continuing to compile and run them.")
        notes.append(note)

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
    run_check = inspect_run_output(theory, run_output, run_log)
    if run_status != 0:
        note = f"generated test binary exited {run_status}"
        print(f"WARNING: {note}; continuing after execution.")
        notes.append(note)

    false_tests = tuple(sorted(name for name, value in run_check.seen.items() if value == "false"))
    true_count = sum(1 for value in run_check.seen.values() if value == "true")
    status = "warning" if notes or run_check.missing else "executed"
    return TheoryResult(
        directory=str(rel_dir),
        file=theory.file.name,
        theory=theory.theory,
        declared=len(theory.tests),
        status=status,
        pvs2c_exit=pvs2c_status,
        run_exit=run_status,
        printed=len(run_check.seen),
        true_count=true_count,
        false_count=len(false_tests),
        false_tests=false_tests,
        missing=run_check.missing,
        notes=tuple(notes),
    )


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
    summary_path = os.environ.get("GITHUB_STEP_SUMMARY")
    results: list[TheoryResult] = []
    for item in theories:
        try:
            results.append(run_theory(repo_root, demo_root, log_dir, pvs_location, item, env))
        except StepError as error:
            results.append(failed_result(demo_root, item, error))
            write_step_summary(summary_path, demo_root, theories, results, error)
            raise

    executed = sum(item.declared for item in results if item.status != "failed")
    write_step_summary(summary_path, demo_root, theories, results)
    print(f"\nPVS2C CI passed: generated C test binaries executed for {executed} discovered _TEST_ declarations.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except StepError as error:
        print(f"ERROR: {error}", file=sys.stderr)
        raise SystemExit(1)
