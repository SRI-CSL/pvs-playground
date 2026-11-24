# PVS2C fixed-array bound

The PVS type `ARRAY[below(16) -> uint8]` has exactly 16 indices. `fixed_array.pvs` maps bytewise complement over that array. The runner inspects the emitted allocation and loop bounds first. When both are 16, the C driver supplies a 16-byte sample and checks the result. Running the reproducer requires Clang or GCC with AddressSanitizer, GMP, pkg-config and a built PVS2C runtime.

Run the check from the crypto directory with the PVS executable under test on `PATH` or selected with `--pvs`.

```sh
python3 reproducers/run.py reproducers/aes-array/fixed_array.pvs
```

On PVS revision `9c378be8bd18b0e763041a629349704886bbc1ef`, the runner reports the allocation and loop limit of 17 and exits before compiling the sample. A corrected generator allocates 16 elements and passes the C check.
