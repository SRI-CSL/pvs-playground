#!/usr/bin/env python3
"""Expose generated C and headers from the checked build for the site browser."""
import json
from pathlib import Path, PurePosixPath
import shutil
import sys
import zipfile

output = Path(sys.argv[1]).resolve()
code = output / "code"
shutil.rmtree(code, ignore_errors=True)
files = []
with zipfile.ZipFile(output / "sources.zip") as archive:
    for entry in archive.infolist():
        path = PurePosixPath(entry.filename)
        if path.is_absolute() or ".." in path.parts:
            raise SystemExit(f"Invalid source archive path: {path}")
        if path.suffix not in (".c", ".h"):
            continue
        destination = code / path
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(archive.read(entry))
        files.append(path.as_posix())
(output / "code.json").write_text(json.dumps(sorted(files), indent=2) + "\n")
print(f"Exported {len(files)} C files and headers")
