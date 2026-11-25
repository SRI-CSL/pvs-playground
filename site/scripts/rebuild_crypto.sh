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
flags=(-O2 -I gmp-build/install/include -I runtime/include -include "$PWD/crypto_bits_compat.h")
while IFS= read -r -d '' path; do flags+=(-I "$path"); done < <(find application -type d -path '*/pvs2c/include' -print0)
index=0
while IFS= read -r -d '' source; do
  emcc "${flags[@]}" -Wno-incompatible-pointer-types -Wno-deprecated-declarations -c "$source" -o "objects/$index.o"
  index=$((index + 1))
done < <(find application runtime/src -name '*_c.c' -o -name pvslib.c | sort | tr '\n' '\0')
counter=0
while IFS= read -r theory; do
  source=$(find application -path "*/pvs2c/src/$theory.c")
  emcc "${flags[@]}" -Dmain="example_$counter" -c "$source" -o "objects/main-$counter.o"
  counter=$((counter + 1))
done < <(node -e 'for (const s of require("./manifest.json").suites) console.log(s.theory)')
emcc "${flags[@]}" dispatch.c objects/*.o gmp-build/install/lib/libgmp.a --no-entry \
  -sMODULARIZE=1 -sEXPORT_ES6=1 -sENVIRONMENT=web,worker,node \
  "-sEXPORTED_FUNCTIONS=['_run_example']" -sALLOW_MEMORY_GROWTH=1 \
  -sMAXIMUM_MEMORY=536870912 -sSTACK_SIZE=8388608 -sASSERTIONS=1 -o crypto.mjs
