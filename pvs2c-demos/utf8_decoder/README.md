# UTF-8 Streaming Decoder PVS2C Demo

This demo implements a UTF-8 byte stream validator, sanitizer, and codepoint
decoder in executable PVS and runs the generated C against the `utf8tests`
suite from the `utf8tests` git submodule:
<https://github.com/flenniken/utf8tests>.

The decoder state tracks the number of continuation bytes still needed, the
legal range for the next continuation byte, and the partially accumulated
Unicode scalar value. The range checks encode the Unicode well-formed UTF-8
constraints directly:

- no overlong encodings (`C0`, `C1`, `E0 80..9F`, `F0 80..8F`)
- no surrogate scalar values (`ED A0..BF`)
- no values above `U+10FFFF` (`F4 90..BF`, `F5..FF`)
- noncharacters such as `U+FFFE` and `U+FFFF` remain valid UTF-8

The sanitizer follows the same maximal-subpart behavior as the reference
decoder used by `utf8tests`: when an invalid byte breaks a pending multi-byte
sequence, the pending sequence is skipped or replaced and the breaking byte is
processed again as the start of the next sequence.

Run the demo with:

```sh
make -C pvs2c-demos/utf8_decoder run
```

After a fresh clone, initialize the upstream test suite with:

```sh
git submodule update --init --recursive pvs2c-demos/utf8_decoder/utf8tests
```

The run target typechecks the PVS theories, generates C with PVS2C, runs the
generated `_TEST_` formulas, produces skip/replace artifacts from
`utf8tests.bin`, and validates those artifacts against `utf8tests.txt`.
