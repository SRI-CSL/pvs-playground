"""Adapt the repository's existing validation drivers for WebAssembly."""
import gzip
import hashlib
import importlib.util
from pathlib import Path
import re
import shutil
import sys


def load(path):
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location(path.stem, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def asset(data, directory, suffix):
    digest = hashlib.sha256(data).hexdigest()
    name = digest[:20] + suffix
    directory.mkdir(exist_ok=True)
    (directory / name).write_bytes(data)
    return {"path": directory.name + "/" + name, "sha256": digest}


def prepare_drivers(suites, crypto, stage, output, find, inputs, repository):
    checks = load(find(crypto, "check.py"))
    aes = load(find(crypto, "check_aes.py"))
    assessments = load(find(crypto, "check_assessments.py"))
    definitions = {}
    for suite in suites:
        key = suite.get("driver")
        if not key:
            continue
        if key in checks.SUITES:
            theories, harness = checks.SUITES[key]
            original = find(crypto, suite["theory"] + ".pvs").parent / Path(harness).name
            if not original.exists():
                original = find(crypto, Path(harness).name)
            fixture, expected = checks.FIXTURES.get(key, (None, None))
        elif key in aes.MODE_CHECKS:
            theories, original, fixture, expected = [aes.MODE_CHECKS[key]], find(crypto, key + "_checks.c"), None, None
            suite["generator"] = "aes"
        else:
            leaf, harness, fixture = assessments.SUITES[key]
            theories, original, expected = [leaf], find(crypto, harness), None
            suite["statistics"] = key in ("sts", "entropy")
        destination = stage / "drivers" / key
        destination.mkdir(parents=True, exist_ok=True)
        for path in [original, *original.parent.glob("*.h")]:
            shutil.copyfile(path, destination / path.name)
            inputs[path.relative_to(repository).as_posix()] = hashlib.sha256(path.read_bytes()).hexdigest()
        suite["driverSource"] = "application/drivers/" + key + "/" + original.name
        if fixture:
            path = find(crypto, suite["theory"] + ".pvs").parent / Path(fixture).name
            if not path.exists():
                path = find(crypto, Path(fixture).name)
            suite["fixture"] = asset(gzip.decompress(path.read_bytes()), output / "fixtures", ".bin")
            inputs[path.relative_to(repository).as_posix()] = hashlib.sha256(path.read_bytes()).hexdigest()
        # Assertions and the exit code remain authoritative; require the driver's
        # success marker too, so a silent or incomplete invocation cannot pass.
        if not expected:
            markers = re.findall(r'puts\("([^"\n]+passed\.?)"\)', original.read_text())
            if key == "ec-signing":
                markers = [f"P-{bits} ECDSA key generation, signing, verification and ECDH passed." for bits in (192, 224, 256, 384, 521)]
            if not markers:
                raise ValueError(f"No success marker for {key}")
            suite["expected"] = markers
        else:
            suite["expected"] = [expected]
        definitions[key] = {"theories": [Path(t).name for t in theories], "source": destination / original.name}
    return definitions
