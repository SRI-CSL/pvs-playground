# ML-DSA

The parameter argument is 0 for ML-DSA-44, 1 for ML-DSA-65, and 2 for ML-DSA-87. The PVS theories cover deterministic key generation, deterministic and hedged signing, signature verification, external message representatives, pure ML-DSA and HashML-DSA. Key generation and hedged signing use the shared checked PRNG attachment. Callers supply a fresh stream for each draw. A failed draw, exhausted sampler or exhausted signing loop returns an explicit failure. [FIPS 204](https://csrc.nist.gov/pubs/fips/204/final)

The ring uses canonical residues and 64-bit products. Sampling and signing use the exhaustion bounds in Appendix C. Verification checks lengths, strictly increasing hint positions, monotone row endings, zero padding, the response norm and the challenge. The pure interface accepts a partial final message octet in SHAKE bit order. The prehash interface accepts all twelve Algorithm 4 hash identifiers using the bit order of the selected hash.

The checked-in fixture contains 30 cases covering all parameter sets. The full NIST projections supplied 75 key-generation vectors, 360 signing vectors and 180 verification vectors. The harness also calls the pure and HashML-DSA public interfaces on the 270 external-interface vectors, for 885 comparisons in total. The core tests use independently computed message representatives. The checked PRNG provider in the harness supplies only the explicit ACVP seed or signing randomness. Build the harness with PVS2C output from the complete import chain of `mldsa_random` and the shared RNG attachments. To run additional cases, pipe output from `python3 mldsa/acvp_inputs.py KEYGEN SIGGEN SIGVER` into that binary.

| NIST ACVP source projection | SHA-256 of the checked file |
| --- | --- |
| [Key generation](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/ML-DSA-keyGen-FIPS204) | `e67ee6540d40e11506c3c4e3b1f79fc1cefcd49820db99fc61f87cc8ba463baf` |
| [Signature generation](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/ML-DSA-sigGen-FIPS204) | `72dcaf5f69853ca267ccd16af9cb40949786aca0fcfbf05d1ebeba132b93af22` |
| [Signature verification](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/ML-DSA-sigVer-FIPS204) | `47cdd6314c7f746d02421ffcba89d4dbc7bb875ac49e07a029fdfc26fba55437` |

The typechecked `mldsa_claims` theory states signing/verification agreement for pure ML-DSA, HashML-DSA, and supplied message representatives. These statements quantify over successfully generated keys and successful signing attempts. Their general proofs are open.
