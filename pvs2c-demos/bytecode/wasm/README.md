# Wasm i32 Bytecode Interpreter PVS2C Demo

This demo implements a small WebAssembly Core interpreter in executable PVS and
runs the generated C against real Wasm function-body bytecode.

The supported subset is intentionally small:

- i32 values only
- one-byte immediates
- i32 locals
- empty-result `block` and `loop`
- `br`, `br_if`, `return`, `end`
- `local.get`, `local.set`, `local.tee`
- `i32.const`, `i32.eqz`, `i32.eq`, `i32.ne`, `i32.add`, `i32.sub`, `i32.mul`

The PVS model uses predicate subtyping for the stack/control discipline:

- `push` only accepts stacks whose height is below `max_stack`
- `pop` only accepts nonempty stacks, and its result type records that the
  returned stack height is one smaller
- machine states are indexed by the byte string being executed, so the program
  counter type is bounded by the current body length
- control frames track `block`/`loop` bodies and matching `end` offsets
- branch depth selection is checked against the current control depth
- execution is total by construction through a fuel-bound runner

Run the demo with:

```sh
make -C pvs2c-demos/bytecode/wasm run
```

The checked-in examples are:

- `add.wat`: `add(40, 2) = 42`
- `affine.wat`: `affine(5, 9) = 5 * 7 + 9 * 3 + 11 = 73`
- `factorial.wat`: an iterative loop using `block`, `loop`, `br_if`, and `br`

Each `.body.hex` file is the WebAssembly function-body payload: the local
declaration vector followed by instruction bytes.  That is the payload inside a
standard `.wasm` code-section function body after the body-size LEB128 wrapper.

To rebuild body hex from WAT, install WABT and run:

```sh
make -C pvs2c-demos/bytecode/wasm compile-examples
```

Or manually:

```sh
wat2wasm examples/factorial.wat -o build/factorial.wasm
python3 tools/extract_wasm_body.py build/factorial.wasm --body 0
```

The `examples/*.c` files are equivalent source examples.  Toolchains vary in
which opcodes they emit, so the demo executes the WAT-derived bytecode by
default; C-compiled modules can be inspected with `tools/extract_wasm_body.py`
when the emitted body stays inside this demo's subset.

## Running Your Own Body Hex

The current C harness is table-driven.  To run another extracted function body,
put the hex payload in `examples/` and add a row to the `cases[]` table in
`driver.c`:

```c
{"my_example", "examples/my_example.body.hex", 2, {10, 20}, 128, 30},
```

The fields are:

- `name`: label printed in the PASS/FAIL output
- `path`: `.body.hex` file containing the extracted Wasm function-body payload
- `arity`: number of i32 arguments to pass, currently `0`, `1`, or `2`
- `args`: argument values; in the example, `arg0 = 10` and `arg1 = 20`
- `fuel`: maximum interpreter steps before the runner returns `fuel_status`
- `expected`: expected i32 return value

That row runs `my_example(10, 20)` with at most `128` interpreter steps and
expects the function to return `30`.  For arity `2`, the harness calls the
generated PVS2C entry point:

```c
wasm_i32__invoke2(pvs_body, 128, 10, 20)
```

After editing the table, run:

```sh
make -C pvs2c-demos/bytecode/wasm run PVS_LOCATION=/path/to/PVS
```
