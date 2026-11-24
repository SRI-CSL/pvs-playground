# Distinct field names on records with the same layout

Run `python3 reproducers/run.py reproducers/record_fields/record_fields.pvs` from the crypto directory. PVS accepts the source. On PVS revision `9c378be8`, PVS2C reuses the first record representation and Clang reports that the generated structure has no member named `ok`. The first record names that Boolean field `carry`. A corrected backend should compile the program and print `record_fields.nonzero_succeeds ==> true`.

This arose in RSA probable-prime candidate rounding. The operational theory consistently uses the shared carry record.
