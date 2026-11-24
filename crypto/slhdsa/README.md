# SLH-DSA

The twelve FIPS 205 parameter sets share WOTS+, XMSS, FORS and hypertree signing and verification. Profiles 0–5 select SHAKE and profiles 6–11 select SHA2, both in the order 128s, 128f, 192s, 192f, 256s, 256f. The SHA2 functions use the 22-octet compressed address, SHA-256 for single-node F and PRF, SHA-256 or SHA-512 for H and Tₗ, HMAC for PRF_msg and the prescribed MGF1 expansion for H_msg. The SHAKE functions use the full 32-octet address and SHAKE256. [FIPS 205 §§4–11](https://doi.org/10.6028/NIST.FIPS.205)

| Theory | Interfaces and assurance |
| --- | --- |
| `slh_wots` | Generates, signs and recovers WOTS+ public keys. The saved `chain_split` proof composes consecutive chain segments at every valid endpoint for both hash families. |
| `slh_verify` | Implements internal and context-framed public verification. The verifier checks key, signature and context lengths before using fields. The saved `invalid_signature_length` lemma covers every profile. |
| `slh_sign` | Derives keys from the three algorithm-specified seeds. Signs an internal or framed octet message using supplied optional randomness. |
| `slh_random` | Gets seeds and hedging input from the shared PRNG attachment. QED type and termination obligations cover the deterministic and provider-backed frontends. |
| `slh_prehash` | HashSLH-DSA signs and verifies all twelve prehash choices using the hash identifier, context, OID and selected digest. The hash input can include a partial final octet. |

The proof files also cover array bounds, parameter-dependent lengths and termination. General signature correctness, the cryptographic hardness assumptions, timing behavior and provider assurance remain separate claims.

Run the following commands from the crypto directory.

```sh
python3 validation/check.py wots slh_verify slh_sign slh_hash
python3 validation/check.py slh_sha2_verify slh_sha2_sign slh_sha2_hash
```

The offline verification samples contain 24 pure/internal cases per hash family, 19 SHAKE prehash cases and 20 SHA2 prehash cases. The two 128f key-generation and signing fixtures reproduce every byte of NIST's keys and valid signatures using cases 87 (SHAKE) and 2 (SHA2). The negative fixtures include altered keys, signatures and messages. To convert a complete NIST sigVer projection to the same binary format, run `python3 slhdsa/acvp_inputs.py internalProjection.json --family SHA2`, adding `--prehash` for HashSLH-DSA. The projection contains 168 pure/internal cases and 84 prehash cases per family. [NIST ACVP SLH-DSA signature verification vectors](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/SLH-DSA-sigVer-FIPS205)

The proof-only theory `slh_claims` states that a key generated from three seed strings verifies its signatures for every supported parameter set, pure or prehashed message, allowed context and signing randomizer. The general correctness proofs are open.
