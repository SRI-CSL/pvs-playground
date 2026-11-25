#!/usr/bin/env bash
# Build the pinned generator in an isolated directory; never use a system PVS.
set -euo pipefail
destination=$1
revision=$2
if [[ ! -d "$destination/.git" ]]; then
  git init "$destination"
  git -C "$destination" fetch --depth 1 https://github.com/SRI-CSL/PVS.git "$revision"
  git -C "$destination" checkout --detach FETCH_HEAD
fi
test "$(git -C "$destination" rev-parse HEAD)" = "$revision"
cd "$destination"
if [[ ! -f .browser-runner-ready ]]; then
  ./configure > configure.log 2>&1
  if ! make > build.log 2>&1; then tail -150 build.log; exit 1; fi
  if ! ./pvs -raw -E '(progn (pvs2c-prelude) (uiop:quit 0))' < /dev/null > prelude.log 2>&1; then
    tail -150 prelude.log
    exit 1
  fi
  test -f lib/pvs2c/include/pvslib.h
  touch .browser-runner-ready
fi
