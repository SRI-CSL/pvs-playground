(module
  (func $affine (export "affine") (param i32 i32) (result i32)
    local.get 0
    i32.const 7
    i32.mul
    local.get 1
    i32.const 3
    i32.mul
    i32.add
    i32.const 11
    i32.add))
