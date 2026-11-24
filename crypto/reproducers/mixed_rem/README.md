# Remainder at mixed unsigned widths

Run `python3 reproducers/run.py reproducers/mixed_rem/mixed_rem.pvs`. PVS typechecks the theory. On revision `9c378be8`, generated C calls `rem_uint64_uint32` and the distributed runtime header has no declaration for it. Clang rejects the translation unit. A corrected backend should print `mixed_rem.wide_value ==> true`.

The operational arithmetic uses the Prelude `u64rem` attachment and establishes the narrower output bound in PVS.
