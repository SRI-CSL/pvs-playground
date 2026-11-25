#!/usr/bin/env bash
# Run in the extracted sources.zip with Emscripten 4.0.23 on PATH.
set -euo pipefail
tar -xf gmp-6.3.0.tar.xz
mkdir -p gmp-build objects
cd gmp-build
CC_FOR_BUILD=cc emconfigure ../gmp-6.3.0/configure --host=wasm32-unknown-emscripten --disable-assembly --disable-shared --enable-static --prefix="$PWD/install"
emmake make -j2
emmake make install
cd ..
python3 rebuild.py
