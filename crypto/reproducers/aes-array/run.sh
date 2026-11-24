#!/bin/sh
set -eu
case $# in
    0) ;;
    1) set -- --pvs "$1" ;;
    *) echo 'Usage: run.sh [pvs]' >&2; exit 2 ;;
esac
here=$(dirname "$0")
exec python3 "$here/../run.py" "$here/fixed_array.pvs" "$@"
