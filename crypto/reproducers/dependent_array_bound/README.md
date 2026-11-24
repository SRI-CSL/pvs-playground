# Dependent array bound enters the Lisp debugger

The five-line theory defines a zero-filled `uint32` array whose index type is `upto(max(n,256))`. It uses only the PVS Prelude.

Run from the crypto directory with the PVS2C image under test.

```sh
python3 reproducers/run.py reproducers/dependent_array_bound/dependent_array_bound.pvs
```

On the affected PVS2C build, the theory typechecked, then `pvs2c-theory` entered the SBCL debugger before emitting the theory's C translation unit. The debugger identified the following method and condition. The runner exits unsuccessfully on this image.

```text
debugger invoked on a SIMPLE-CONDITION
  pvs2ir-type*(arraytype)
((:METHOD PVS2IR-TYPE* (ARRAYTYPE T)) ARRAY[upto(max(n, 256)) -> uint32] ...)
source: (BREAK "pvs2ir-type*(arraytype)")
```

The same Lisp method also stopped on `ARRAY[below(n+257)->uint32]`. The operational suffix sorter passes a precomputed `pos_uint32` capacity and uses `ARRAY[below(cap)->uint32]`.
