# Pairwise key agreement

`ff_agreement.pvs` implements FFC DH, both forms of FFC MQV, range checks and full subgroup validation. The interfaces accept domain parameters whose primality, order and provenance have already been assured. `ff_groups.pvs` supplies the ten safe-prime groups listed in Appendix D. For MQV1, the recipient supplies its static pair in both roles. The public entry points compute the local second public key from the corresponding private scalar. [NIST SP 800-56A Rev. 3](https://csrc.nist.gov/pubs/sp/800/56/a/r3/final)

`ec_mqv.pvs` implements full and one-pass ECC MQV over the five prime-field Weierstrass curves in `ecc/prime_curve.pvs`. The primitive checks received affine points against the curve equation. All five curves have cofactor one. `full_public_valid` additionally computes the subgroup-order multiple and checks that it equals the identity. `dsa_verify.pvs` verifies a legacy DSA signature against an externally supplied digest and assured FFC parameters. [FIPS 186-5](https://csrc.nist.gov/pubs/fips/186-5/final)

Run the generated C tests from the crypto directory. The cases cover FFC static DH, MQV1 and MQV2, P-256 full and one-pass MQV, all ten named group constructors, and DSA verification of an original and an altered digest. [NIST CAVP key agreement vectors](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/key-management/key-establishment) [RFC 6979 Appendix A.2.1](https://www.rfc-editor.org/rfc/rfc6979#appendix-A.2.1)

```sh
python3 validation/check.py key-agreement
```

`dh_schemes` implements both participant roles for all seven Section 6 scheme patterns over the FFC and prime-field ECC primitives. These include ephemeral, static, full unified, one-pass unified, one-pass DH, full MQV and one-pass MQV. The two-component schemes encode the ephemeral contribution before the static contribution. Failure of either required primitive yields an empty failed result. The caller supplies protected local keys, the peer's received public values and the authenticated domain. The selector identifies which local and peer key fields participate.

`dh_derivation` combines successful agreement output with the SP 800-56C one-step hash or HMAC KDF. It accepts agreed encoded FixedInfo and provides an optional format with explicit four-octet length fields, ordered party identifiers and contributions. The static-scheme formatter requires party U's nonce. The shared `crypto_prelude/key_confirmation/pairwise_confirmation` theory supplies a §5.9 HMAC-SHA-256 confirmation profile. The surrounding protocol supplies the authenticated identities and the nonce, transports the messages and destroys transient state. [SP 800-56A Rev. 3 §§5.8, 6](https://doi.org/10.6028/NIST.SP.800-56Ar3) · [SP 800-56C Rev. 2 §4](https://doi.org/10.6028/NIST.SP.800-56Cr2)

Run `python3 validation/check.py dh-schemes`. The offline fixture gives one NIST KASVS known answer for each of the seven schemes, both roles and both primitive families. The generated C checks both the field-width shared secret and the derived keying material. The fixture generator takes the 2016 FFC and ECC archives as its two arguments. [NIST key-establishment test vectors](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/key-management/key-establishment)

The proof-only theory `dh_agreement_claims` states the Full Unified agreement property for two ECC participants with valid static and ephemeral private scalars and the corresponding peer public keys. It also states agreement for all seven ECC patterns and successful DH agreement for both roles in the five DH patterns over every named Appendix D group. These group-law and encoding proofs are open.
