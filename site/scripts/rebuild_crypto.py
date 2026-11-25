#!/usr/bin/env python3
"""Recompile an exported source bundle without PVS or the original repository."""
import json
from pathlib import Path
import subprocess


def run(args):
    subprocess.run(list(map(str, args)), check=True)


manifest = json.loads(Path('manifest.json').read_text())
flags = ['emcc', '-O2', '-Wno-incompatible-pointer-types', '-Wno-deprecated-declarations',
         '-include', 'crypto_bits_compat.h', '-I', 'runtime/include', '-I', 'gmp-build/install/include']
for path in sorted(Path('application').rglob('pvs2c/include')):
    flags += ['-I', path]
statistics = any(s.get('statistics') for s in manifest['suites'])
if statistics:
    flags += ['-include', 'crypto_statistics_math.h']
compression = any(s.get('driver') == 'entropy' for s in manifest['suites'])
if compression:
    flags += ['--use-port=bzip2']
sources = sorted(Path('application').rglob('*_c.c')) + sorted(Path('runtime/src').glob('*.c')) + [Path('wasm_runtime.c')]
if compression:
    sources += [Path('crypto_compression.c')]
objects = []
for i, source in enumerate(sources):
    obj = Path('objects') / f'{i}.o'
    run([*flags, '-c', source, '-o', obj]); objects.append(obj)
if statistics:
    obj = Path('objects/gamma.o')
    run(['em++', '-O2', '-std=c++17', '--use-port=boost_headers', '-c', 'crypto_gamma.cc', '-o', obj]); objects.append(obj)
run(['emar', 'rcs', 'objects/common.a', *objects])
settings = ['--no-entry', '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=web,worker,node',
            "-sEXPORTED_FUNCTIONS=['_run_example','_nist_eval']", "-sEXPORTED_RUNTIME_METHODS=['ccall','FS']",
            '-sALLOW_MEMORY_GROWTH=1', '-sMAXIMUM_MEMORY=536870912', '-sSTACK_SIZE=8388608', '-sASSERTIONS=1', '-Wl,--wrap=exp2__exp2']
legacy = []
for s in manifest['suites']:
    if s.get('driver'): continue
    main = next(Path('application').rglob(s['theory'] + '.c'))
    obj = Path('objects') / f"main-{s['index']}.o"
    run([*flags, f"-Dmain=example_{s['index']}", '-c', main, '-o', obj]); legacy.append(obj)
legacy_flags = json.loads(Path('nist-flags.json').read_text())
run([*flags, *legacy_flags, 'dispatch.c', 'nist_bridge.c', *legacy, 'random-defaults.c', 'objects/common.a',
     'gmp-build/install/lib/libgmp.a', *settings, '-o', 'crypto.mjs'])
for s in manifest['suites']:
    if not s.get('driver'): continue
    obj = Path('objects') / (s['driver'] + '-main.o')
    run([*flags, '-c', s['driverSource'], '-o', obj])
    adapter_flags = ['-DNIST_' + name.upper().replace('-', '_') for name in s.get('nist', [])]
    run([*flags, *adapter_flags, Path(s['driverSource']).parent / 'browser.c', obj, 'nist_extra.c', 'random-defaults.c',
         'objects/common.a', 'gmp-build/install/lib/libgmp.a', '-sFORCE_FILESYSTEM=1', '-sINVOKE_RUN=0', *settings, '-o', s['driver'] + '.mjs'])
