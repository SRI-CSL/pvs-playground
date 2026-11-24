# PVS2C regression cases

Each directory isolates a translator, generated-C or runtime-interface issue encountered while using the standards as compiler inputs. The tests exercise the toolchain. They use synthetic values and have no dependency on cryptographic keys or a deployed system.

| Case | Observed phase and result |
|---|---|
| [Dependent array bound](dependent_array_bound/README.md) | The theory typechecks. PVS2C enters the Lisp debugger in `pvs2ir-type*(arraytype)` on `ARRAY[upto(max(n,256))->uint32]`. |
| [Fixed array](aes-array/README.md) | Generated allocation and loop bound are 17 for a 16-element PVS type. The runner checks the emitted bounds. |
| [Record fields](record_fields/README.md) | The generated C names a field that is absent from the chosen record representation. |
| [Enumeration](enum_type/README.md) | Generated header refers to an undeclared enumeration type. |
| [Mixed remainder](mixed_rem/README.md) | Generated C refers to an undeclared mixed-width runtime primitive. |
| [Digest width](curve-digest-width/README.md) | Inferred and explicitly bounded expressions produce different integer comparisons. |
| [Unsigned XOR](bare_xor/bare_xor.pvs) | Generated C calls an undeclared bare `u64xor`. The operational build includes the fixed-width compatibility header. |
| [Signed comparison](signed_compare/signed_compare.pvs) | The negative result of `strcmp` incorrectly makes the inequality test false. The positive and zero control cases pass. The OAEP theory uses structural equality. |
| [Subtraction](gmp_subtract/gmp_subtract.pvs) | Clang diagnoses an uninitialized destination in the emitted arbitrary-precision subtraction. The operational hash conditioner bounds its intermediate and uses Prelude unsigned subtraction. |

Run a single case from the crypto directory. The driver uses a temporary context. For the subtraction case it checks the generated translation unit with Clang's uninitialized-variable diagnostic. The fixed-array check inspects the generated bounds before running the C sample.

```sh
python3 reproducers/run.py reproducers/signed_compare/signed_compare.pvs
python3 reproducers/run.py reproducers/gmp_subtract/gmp_subtract.pvs
```

A nonzero result on an affected build identifies a discrepancy. Pass `--keep generated-case` to inspect the emitted files. The dependent-array case stops in the Lisp translator. The other eight cases reach generated code or its runtime interface.
