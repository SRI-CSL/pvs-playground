# PVS2C reverses a mixed-width comparison

The theory takes the shorter of a digest's byte length and four times a curve's limb count. The 7-limb inputs should give 3 for a 3-octet digest and 28 for a 40-octet digest. Both PVS definitions express the same calculation.

From the crypto directory, run

```sh
python3 reproducers/run.py reproducers/curve-digest-width/curve_digest_width.pvs
```

On the affected generator, the generated executable reported

```text
curve_digest_width.inferred_short ==> false
curve_digest_width.inferred_long ==> false
curve_digest_width.bounded_short ==> true
curve_digest_width.bounded_long ==> true
```

The inferred local `n` becomes a GMP integer. PVS2C translates `len > n` into `mpz_cmp_ui(n, len) > 0`, so the two failing evaluations return 28 and 40 respectively. Declaring `n: uint16` emits the native `len > n` comparison and both tests pass. The Appendix H ECDSA implementation uses the explicitly typed width for truncating a message digest.
