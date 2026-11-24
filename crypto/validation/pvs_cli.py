"""Command-line discovery for the PVS validation runners."""
import argparse
import os
from pathlib import Path
import shutil


def pvs_executable(value):
    executable = shutil.which(os.path.expanduser(value))
    if executable is None:
        raise argparse.ArgumentTypeError(
            f"cannot find executable {value!r}; put pvs on PATH, set PVS_BIN, or pass --pvs"
        )
    return Path(executable).resolve()


def add_pvs_argument(parser):
    parser.add_argument("--pvs", type=pvs_executable, default=os.environ.get("PVS_BIN") or "pvs",
                        help="PVS executable (default: PVS_BIN or pvs on PATH)")


def pvs2c_runtime(pvs):
    override = os.environ.get("PVS2C_RUNTIME")
    return Path(override).expanduser().resolve() if override else pvs.parent / "lib/pvs2c"
