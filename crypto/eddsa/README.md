# Edwards-curve signatures

The pure and prehash interfaces cover Ed25519, Ed25519ph, Ed448 and Ed448ph. Both theories derive a verification key from a seed, sign octet strings and verify signatures. Ed25519ph, Ed448 and Ed448ph accept contexts up to 255 octets. The verifiers check canonical point and scalar encodings, public-key subgroup membership and the uncofactored verification equation. Ed25519 uses eight little-endian 32-bit limbs and SHA-512. Ed448 uses fourteen 32-bit limbs and SHAKE256. [FIPS 186-5 §§7.4–7.8](https://doi.org/10.6028/NIST.FIPS.186-5) · [SP 800-186 §§3.2.3, D.1.3](https://doi.org/10.6028/NIST.SP.800-186)

The random-key frontends obtain 32 or 57 seed octets from the caller's RBG stream. An incomplete acquisition reports failure and clears the result. The provider supplies the stream's freshness and security strength.

Run `python3 validation/check.py ed25519 ed25519-keygen ed448 ed448-keygen`. The generated C reproduces published public keys and signatures and checks pure and context-bearing prehash verification. Cases also exercise noncanonical encodings, altered messages and provider failures. [RFC 8032 §7](https://www.rfc-editor.org/rfc/rfc8032#section-7)

Saved PVS proofs cover type and termination obligations, limb-comparison reflexivity, rejection of out-of-range response scalars, and provider failure. Field-arithmetic refinement, general signature round trips, implementation timing properties and provider assurance remain open.

The proof-only theories `ed25519_claims` and `ed448_claims` state pure and prehashed signing correctness for verification keys that pass the model's subgroup checks. These universally quantified claims have open proofs.
