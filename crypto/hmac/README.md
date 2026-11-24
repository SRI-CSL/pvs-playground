# HMAC and HMAC_DRBG

`keyed_hash.pvs` supports HMAC for the seven FIPS 180-4 hashes and the four fixed-output SHA-3 hashes. It hashes overlong keys, pads short keys and provides full and octet-truncated tags. The digest and block lengths follow the selected hash. [FIPS 198-1](https://doi.org/10.6028/NIST.FIPS.198-1)

`hmac_drbg.pvs` implements instantiation, update, reseed, generation with additional input, and reseed-before-generate for the seven Table 2 algorithms. It accepts requests for one through 524288 bits, preserves the leftmost bits in a partial final octet, and reports failure at the reseed limit. The input APIs model the deterministic mechanism. The caller provides the required entropy, nonce and security-strength checks for the function envelope. [SP 800-90A Rev. 1 §§9, 10.1.2](https://doi.org/10.6028/NIST.SP.800-90Ar1)

Run `python3 validation/check.py hmac hmac-reseed`. The suites replay the saved proofs, including the reseed-counter reset and expiry properties. Generated C checks three NIST HMAC examples, two consecutive DRBG results, and CAVP reseed and prediction-resistance cases with personalization and additional input. [NIST intermediate values](https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values) · [DRBGVS vectors](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/random-number-generators)
