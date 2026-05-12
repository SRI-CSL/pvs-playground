# SQLite VDBE Bytecode Interpreter PVS2C Demo

This demo implements a small executable PVS model of SQLite's VDBE register
machine and runs the generated C over bytecode patterns taken from real
`EXPLAIN` output.

The supported subset is intentionally narrow:

- `Init`, `Goto`, `Halt`, `Transaction`
- `Explain` as a no-op when exposed by the SQLite C API
- `Integer`, `Add`, `Multiply`
- `OpenRead`, `Rewind`, `Column`, `Next`
- `Function` for `abs(1)`
- `Le` for the `x > 5` scan shape emitted as `if r[x] <= r[limit] goto ...`
- `ResultRow`

The model uses PVS features that matter for this kind of VM:

- SQL values are typed as `null`, `int32`, `text`, or `blob`.
- Register files carry an initialized bit per register; `ResultRow`,
  arithmetic, comparison, and function opcodes trap on uninitialized inputs.
- Cursor state is explicit, and table opcodes trap if a cursor is closed or
  positioned off-row.
- Machine states are indexed by the program being executed, so the program
  counter is bounded by the current `array_sequences` program length.
- Result buffers have bounded row and column counts, and `Halt` moves the
  program counter to the end of the current program.
- The executable structures use the PVS2C-friendly prelude integer types
  (`uint8`, `uint32`, `int32`) and `array_sequences` (`aseq`) instead of
  unbounded numeric or `finseq`-based data paths.

Run the demo with:

```sh
make -C pvs2c-demos/bytecode/sqlite_vdbe run
```

The C harness now has a small SQLite execution bridge.  It creates an in-memory
SQLite database, prepares `EXPLAIN <query>` with the SQLite C API, translates the
supported VDBE rows into generated PVS records, snapshots table `t` into the PVS
database representation, and calls `sqlite_vdbe__run` instead of stepping the
original query statement.  This is a public-API dispatch shim, not a patch to
SQLite's private `vdbe.c`.  The harness then runs the same query through native
SQLite as an oracle and compares the result cells.

The checked examples are:

- `SELECT 1 + 2 * 3`, expected result `7`
- `SELECT abs(x) FROM t`, over rows `(-7, 'neg')`, `(3, 'small')`, `(11, 'big')`
- `SELECT x, name FROM t WHERE x > 5`, expected row `(11, 'big')`

The `examples/*.explain` files are generated from the installed `sqlite3`
binary using the SQL in `examples/*.sql`.  Refresh them with:

```sh
make -C pvs2c-demos/bytecode/sqlite_vdbe refresh-explain
```

`sqlite_vdbe_tests.pvs` encodes the corresponding instruction records.  The
numeric opcode tags are local to this demo; the instruction order and `p1`,
`p2`, `p3`, and `p5` operands match the `EXPLAIN` rows.  The `p4` field is
normalized to compact tags where the interpreter needs semantic information
such as `abs(1)` or `BINARY-8`.
