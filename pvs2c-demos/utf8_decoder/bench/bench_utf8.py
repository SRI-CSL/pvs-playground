#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import os
import shlex
import shutil
import statistics
import subprocess
import sys
import time
from collections import defaultdict
from dataclasses import asdict
from pathlib import Path
from typing import Iterable

ROOT = Path(__file__).resolve().parents[1]
REPO = ROOT.parents[1]
sys.dont_write_bytecode = True
sys.path.insert(0, str(ROOT))

from validate_utf8tests import TestCase, parse_expected  # noqa: E402


def hex_bytes(data: bytes) -> str:
    return data.hex()


def expected_replace(case: TestCase) -> bytes:
    return case.test_bytes if case.valid else case.replace_bytes


def expected_skip(case: TestCase) -> bytes:
    return case.test_bytes if case.valid else case.skip_bytes


def case_rows(cases: list[TestCase]) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    for case in cases:
        rows.append(
            {
                "number": case.number,
                "valid": case.valid,
                "input_hex": hex_bytes(case.test_bytes),
                "replace_hex": hex_bytes(expected_replace(case)),
                "skip_hex": hex_bytes(expected_skip(case)),
            }
        )
    return rows


def c_array(name: str, data: bytes) -> str:
    if not data:
        return f"static const uint8_t {name}[] = {{0x00}};\n"
    values = ", ".join(f"0x{byte:02x}" for byte in data)
    return f"static const uint8_t {name}[] = {{{values}}};\n"


def generate_c_header(cases: list[TestCase], path: Path) -> None:
    lines = [
        "#ifndef UTF8BENCH_CASES_H\n",
        "#define UTF8BENCH_CASES_H\n\n",
        "#include <stddef.h>\n",
        "#include <stdint.h>\n\n",
        "typedef struct {\n",
        "  const char *number;\n",
        "  int valid;\n",
        "  const uint8_t *input;\n",
        "  size_t input_len;\n",
        "  const uint8_t *replace;\n",
        "  size_t replace_len;\n",
        "  const uint8_t *skip;\n",
        "  size_t skip_len;\n",
        "} bench_case_t;\n\n",
    ]
    for index, case in enumerate(cases):
        lines.append(c_array(f"case_{index}_input", case.test_bytes))
        lines.append(c_array(f"case_{index}_replace", expected_replace(case)))
        lines.append(c_array(f"case_{index}_skip", expected_skip(case)))
    lines.append("\nstatic const bench_case_t bench_cases[] = {\n")
    for index, case in enumerate(cases):
        lines.append(
            f'  {{"{case.number}", {1 if case.valid else 0}, '
            f"case_{index}_input, {len(case.test_bytes)}, "
            f"case_{index}_replace, {len(expected_replace(case))}, "
            f"case_{index}_skip, {len(expected_skip(case))}}},\n"
        )
    lines.append("};\n")
    lines.append(
        "static const size_t bench_case_count = "
        "sizeof(bench_cases) / sizeof(bench_cases[0]);\n\n"
    )
    lines.append("#endif\n")
    path.write_text("".join(lines), encoding="ascii")


def run_command(cmd: list[str], *, cwd: Path = ROOT) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        cmd,
        cwd=cwd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=True,
    )


def ensure_pvs2c_bench(build_dir: Path) -> Path:
    required = [
        ROOT / "pvs2c/include/utf8_decoder_c.h",
        ROOT / "pvs2c/src/utf8_decoder_c.o",
    ]
    if any(not path.exists() for path in required):
        run_command(["make", "all"])

    pvs_location = Path(os.environ.get("PVS_LOCATION", str(Path.home() / "git/PVS")))
    include_dir = pvs_location / "lib/pvs2c/include"
    prelude = pvs_location / "lib/pvs2c/lib/libpvs-prelude.a"
    out = build_dir / "pvs2c_utf8_bench"

    cc = os.environ.get("CC", "cc")
    cflags = shlex.split(
        os.environ.get("CFLAGS", "-O2 -w -foptimize-sibling-calls -fPIC")
    )
    cmd = [
        cc,
        *cflags,
        f"-I{include_dir}",
        "-Ipvs2c/include",
        f"-I{build_dir}",
        "-include",
        "../pvs2c_compat.h",
        "pvs2c/src/utf8_decoder_c.o",
        "bench/pvs2c_utf8_bench.c",
        "-o",
        str(out),
        str(prelude),
        "-lgmp",
        "-lm",
    ]
    run_command(cmd)
    return out


def parse_csv(stdout: str) -> list[dict[str, str]]:
    return list(csv.DictReader(stdout.splitlines()))


def run_external(
    name: str,
    cmd: list[str],
    *,
    cwd: Path = ROOT,
) -> list[dict[str, str]]:
    try:
        completed = run_command(cmd, cwd=cwd)
    except subprocess.CalledProcessError as exc:
        sys.stderr.write(f"\n{name} failed\n")
        sys.stderr.write(exc.stdout)
        sys.stderr.write(exc.stderr)
        raise
    return parse_csv(completed.stdout)


def median_ns(samples: list[float]) -> float:
    samples.sort()
    return samples[len(samples) // 2]


def python_sanitize_replace(data: bytes) -> bytes:
    return data.decode("utf-8", "replace").encode("utf-8")


def benchmark_python(
    cases: list[TestCase], iterations: int, trials: int
) -> list[dict[str, str]]:
    rows: list[dict[str, str]] = []
    sink = 0
    for case in cases:
        expected = expected_replace(case)
        actual = python_sanitize_replace(case.test_bytes)
        ok = actual == expected

        warmups = min(iterations, 64)
        for _ in range(warmups):
            sink += len(python_sanitize_replace(case.test_bytes))

        samples: list[float] = []
        for _ in range(trials):
            start = time.perf_counter_ns()
            for _ in range(iterations):
                sink += len(python_sanitize_replace(case.test_bytes))
            end = time.perf_counter_ns()
            samples.append((end - start) / iterations)

        rows.append(
            {
                "implementation": (
                    f"Python {sys.version_info.major}."
                    f"{sys.version_info.minor}.{sys.version_info.micro}"
                ),
                "mode": "replace",
                "case": case.number,
                "valid": "1" if case.valid else "0",
                "input_bytes": str(len(case.test_bytes)),
                "expected_bytes": str(len(expected)),
                "ns_per_op": f"{median_ns(samples):.2f}",
                "ok": "yes" if ok else "no",
            }
        )

    if sink == -1:
        print("unreachable sink", file=sys.stderr)
    return rows


def write_results_csv(rows: list[dict[str, str]], path: Path) -> None:
    fieldnames = [
        "implementation",
        "mode",
        "case",
        "valid",
        "input_bytes",
        "expected_bytes",
        "ns_per_op",
        "ok",
    ]
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def grouped_rows(rows: Iterable[dict[str, str]]) -> dict[str, list[dict[str, str]]]:
    groups: dict[str, list[dict[str, str]]] = defaultdict(list)
    for row in rows:
        groups[row["implementation"]].append(row)
    return groups


def write_summary(
    rows: list[dict[str, str]],
    path: Path,
    *,
    iterations: int,
    trials: int,
    cases_count: int,
) -> None:
    lines = [
        "# UTF-8 Decoder Benchmark Summary\n\n",
        f"- Corpus: flenniken/utf8tests, {cases_count} parsed cases\n",
        "- Mode: replacement sanitization; valid cases must round-trip unchanged\n",
        f"- Timing: median of {trials} trials, {iterations} iterations per trial, "
        "excluding process startup and corpus parsing\n",
        "- Unit: microseconds per single test-case sanitization operation\n\n",
        "| Implementation | Correct cases | Median us/op | P95 us/op | Max us/op |\n",
        "| --- | ---: | ---: | ---: | ---: |\n",
    ]
    for impl, impl_rows in grouped_rows(rows).items():
        values = sorted(float(row["ns_per_op"]) / 1000.0 for row in impl_rows)
        ok_count = sum(1 for row in impl_rows if row["ok"] == "yes")
        median = statistics.median(values)
        p95 = values[min(len(values) - 1, int(len(values) * 0.95))]
        lines.append(
            f"| {impl} | {ok_count}/{len(impl_rows)} | "
            f"{median:.3f} | {p95:.3f} | {max(values):.3f} |\n"
        )
    path.write_text("".join(lines), encoding="utf-8")


def nice_log_ticks(min_value: float, max_value: float) -> list[float]:
    import math

    low = math.floor(math.log10(min_value))
    high = math.ceil(math.log10(max_value))
    ticks: list[float] = []
    for exp in range(low, high + 1):
        for multiplier in (1, 2, 5):
            value = multiplier * (10**exp)
            if min_value <= value <= max_value:
                ticks.append(value)
    return ticks


def svg_text(
    x: float,
    y: float,
    text: str,
    *,
    size: int = 15,
    fill: str = "#202124",
    anchor: str = "start",
    weight: str = "normal",
) -> str:
    import html

    return (
        f'<text x="{x:.1f}" y="{y:.1f}" font-family="Arial, Helvetica, sans-serif" '
        f'font-size="{size}" font-weight="{weight}" fill="{fill}" '
        f'text-anchor="{anchor}">{html.escape(text)}</text>'
    )


def draw_cactus_svg(rows: list[dict[str, str]], path: Path, *, iterations: int, trials: int) -> None:
    import math

    groups = grouped_rows(rows)
    all_us = [float(row["ns_per_op"]) / 1000.0 for row in rows]
    min_us = max(min(all_us) * 0.8, 0.001)
    max_us = max(all_us) * 1.25
    width, height = 1200, 760
    left, right, top, bottom = 105, 245, 78, 95
    plot_w = width - left - right
    plot_h = height - top - bottom

    colors = [
        "#1967d2",
        "#d93025",
        "#188038",
        "#b06000",
        "#7b1fa2",
        "#00838f",
    ]

    def x_pos(rank: int, count: int) -> float:
        if count <= 1:
            return left
        return left + (rank - 1) * plot_w / (count - 1)

    def y_pos(us: float) -> float:
        low = math.log10(min_us)
        high = math.log10(max_us)
        return top + (high - math.log10(us)) * plot_h / (high - low)

    elements: list[str] = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
        f'viewBox="0 0 {width} {height}">',
        '<rect width="100%" height="100%" fill="white"/>',
        svg_text(
            left,
            34,
            "UTF-8 Replacement Decoder Cactus Plot",
            size=28,
            weight="700",
        ),
        svg_text(
            left,
            60,
            f"median of {trials} trials x {iterations} iterations per utf8tests case",
            size=15,
            fill="#5f6368",
        ),
        (
            f'<rect x="{left}" y="{top}" width="{plot_w}" height="{plot_h}" '
            'fill="none" stroke="#dadce0" stroke-width="1"/>'
        ),
    ]

    def line(x1: float, y1: float, x2: float, y2: float, color: str, width_px: float = 1) -> str:
        return (
            f'<line x1="{x1:.2f}" y1="{y1:.2f}" x2="{x2:.2f}" y2="{y2:.2f}" '
            f'stroke="{color}" stroke-width="{width_px}" stroke-linecap="round"/>'
        )

    def path_line(points: list[tuple[float, float]], color: str) -> str:
        coords = " ".join(f"{x:.2f},{y:.2f}" for x, y in points)
        return (
            f'<polyline points="{coords}" fill="none" stroke="{color}" '
            'stroke-width="3" stroke-linejoin="round" stroke-linecap="round"/>'
        )

    ticks = nice_log_ticks(min_us, max_us)
    for tick in ticks:
        y = y_pos(tick)
        elements.append(line(left, y, left + plot_w, y, "#eef0f1"))
        elements.append(
            svg_text(left - 14, y + 5, f"{tick:g}", size=15, fill="#5f6368", anchor="end")
        )

    max_count = max(len(group) for group in groups.values())
    for tick in range(0, max_count + 1, 50):
        x = left if tick == 0 else x_pos(tick, max_count)
        elements.append(line(x, top + plot_h, x, top + plot_h + 6, "#5f6368"))
        elements.append(
            svg_text(x, top + plot_h + 29, str(tick), size=15, fill="#5f6368", anchor="middle")
        )

    elements.append(
        svg_text(
            left + plot_w / 2,
            height - 38,
            "Cases, sorted fastest to slowest per implementation",
            size=18,
            fill="#3c4043",
            anchor="middle",
        )
    )
    elements.append(
        (
            f'<text x="28" y="{top + plot_h / 2}" font-family="Arial, Helvetica, sans-serif" '
            'font-size="18" fill="#3c4043" text-anchor="middle" '
            'transform="rotate(-90 28 '
            f'{top + plot_h / 2})">us/op, log scale</text>'
        )
    )

    for color, (impl, impl_rows) in zip(colors, groups.items()):
        values = sorted(float(row["ns_per_op"]) / 1000.0 for row in impl_rows)
        points = [(x_pos(index + 1, len(values)), y_pos(value)) for index, value in enumerate(values)]
        if len(points) == 1:
            x, y = points[0]
            elements.append(f'<circle cx="{x:.2f}" cy="{y:.2f}" r="3" fill="{color}"/>')
        else:
            elements.append(path_line(points, color))

    legend_x = left + plot_w + 28
    legend_y = top + 10
    for color, (impl, impl_rows) in zip(colors, groups.items()):
        ok_count = sum(1 for row in impl_rows if row["ok"] == "yes")
        values = sorted(float(row["ns_per_op"]) / 1000.0 for row in impl_rows)
        elements.append(line(legend_x, legend_y + 9, legend_x + 28, legend_y + 9, color, 4))
        elements.append(svg_text(legend_x + 38, legend_y + 5, impl, size=15))
        elements.append(
            svg_text(
                legend_x + 38,
                legend_y + 27,
                f"ok {ok_count}/{len(impl_rows)}, med {statistics.median(values):.3f} us",
                size=15,
                fill="#5f6368",
            )
        )
        legend_y += 54

    elements.append("</svg>\n")
    path.write_text("\n".join(elements), encoding="utf-8")


def selected_implementations(args: argparse.Namespace) -> list[str]:
    if args.implementations == ["all"]:
        return ["pvs2c", "python", "node", "perl"]
    return args.implementations


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(
        description="Benchmark UTF-8 replacement decoders against flenniken/utf8tests."
    )
    parser.add_argument("--iterations", type=int, default=5000)
    parser.add_argument("--trials", type=int, default=3)
    parser.add_argument(
        "--implementations",
        nargs="+",
        default=["all"],
        choices=["all", "pvs2c", "python", "node", "perl"],
    )
    args = parser.parse_args(argv)

    if args.iterations <= 0 or args.trials <= 0:
        parser.error("iterations and trials must be positive")

    build_dir = ROOT / "build/utf8bench"
    build_dir.mkdir(parents=True, exist_ok=True)

    cases = parse_expected(ROOT / "utf8tests/utf8tests.txt")
    cases_json = build_dir / "utf8bench_cases.json"
    cases_json.write_text(json.dumps(case_rows(cases), indent=2), encoding="utf-8")
    generate_c_header(cases, build_dir / "utf8bench_cases.h")

    rows: list[dict[str, str]] = []
    implementations = selected_implementations(args)

    if "pvs2c" in implementations:
        bench_bin = ensure_pvs2c_bench(build_dir)
        rows.extend(
            run_external(
                "PVS2C",
                [str(bench_bin), "replace", str(args.iterations), str(args.trials)],
            )
        )

    if "python" in implementations:
        rows.extend(benchmark_python(cases, args.iterations, args.trials))

    if "node" in implementations:
        node = shutil.which("node")
        if node is None:
            print("Skipping Node TextDecoder: node not found", file=sys.stderr)
        else:
            rows.extend(
                run_external(
                    "Node TextDecoder",
                    [
                        node,
                        "bench/node_utf8_bench.js",
                        str(cases_json),
                        "replace",
                        str(args.iterations),
                        str(args.trials),
                    ],
                )
            )

    if "perl" in implementations:
        perl = shutil.which("perl")
        if perl is None:
            print("Skipping Perl Encode: perl not found", file=sys.stderr)
        else:
            rows.extend(
                run_external(
                    "Perl Encode",
                    [
                        perl,
                        "bench/perl_utf8_bench.pl",
                        str(cases_json),
                        "replace",
                        str(args.iterations),
                        str(args.trials),
                    ],
                )
            )

    if not rows:
        print("No benchmark rows produced", file=sys.stderr)
        return 1

    results_csv = build_dir / "utf8bench_results.csv"
    plot_svg = build_dir / "utf8bench_cactus.svg"
    summary_md = build_dir / "utf8bench_summary.md"
    write_results_csv(rows, results_csv)
    write_summary(
        rows,
        summary_md,
        iterations=args.iterations,
        trials=args.trials,
        cases_count=len(cases),
    )
    draw_cactus_svg(rows, plot_svg, iterations=args.iterations, trials=args.trials)

    print(f"cases: {len(cases)}")
    print(f"results: {results_csv}")
    print(f"summary: {summary_md}")
    print(f"plot: {plot_svg}")
    for impl, impl_rows in grouped_rows(rows).items():
        ok_count = sum(1 for row in impl_rows if row["ok"] == "yes")
        values = sorted(float(row["ns_per_op"]) / 1000.0 for row in impl_rows)
        print(
            f"{impl}: ok {ok_count}/{len(impl_rows)}, "
            f"median {statistics.median(values):.3f} us/op, max {max(values):.3f} us/op"
        )

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
