# Missing declaration for a PVS enumeration

Run `python3 reproducers/run.py reproducers/enum_type/enum_type.pvs`. PVS accepts the declaration and translates it. On revision `9c378be8`, the generated header uses `enum_type__direction_adt_t` before any declaration of that C type. Clang reports an unknown type name. A corrected backend should compile the program and print `enum_type.changes ==> true`.

This arose when representing the Keccak step mappings. The executable SHA-3 and hash selection paths use bounded Prelude integers with named values.
