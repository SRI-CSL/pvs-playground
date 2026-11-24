# Stateful hash-based signatures

These theories implement the LMS, HSS, XMSS, and XMSSMT profiles approved in [SP 800-208](https://csrc.nist.gov/pubs/sp/800/208/final). LMS and HSS use the wire formats and domain separators in [RFC 8554](https://www.rfc-editor.org/rfc/rfc8554) and the additional LMS identifiers in [RFC 9858](https://www.rfc-editor.org/rfc/rfc9858). XMSS and XMSSMT use [RFC 8391](https://www.rfc-editor.org/rfc/rfc8391) with the parameter identifiers, index conventions, and secret derivation in SP 800-208.

## Interfaces and bounds

- `lms_hash`, `lms`, and `hss` implement LM-OTS chains, Merkle verification, and HSS verification over canonical serialized inputs. The two SHA-256 and two SHAKE256 digest profiles support 24- and 32-octet digests, Winternitz widths 1, 2, 4, and 8, and tree heights 5, 10, 15, 20, and 25.
- `lms_sign` and `hss_sign` implement seed and identifier acquisition, root and authentication-path generation, signing, leaf reservation, and child-tree replacement for hierarchies of one through eight levels. Each HSS key uses one hash/digest profile throughout. Height and Winternitz width can vary by level. `keygen_hss` and `sign_hss` take separate streams for fresh child material, child certificates, and the message randomizer.
- `xmss_wots`, `xmss`, and `xmss_sign` implement WOTS+, address generation, L-trees, Merkle authentication paths, and the 12 XMSS and 32 XMSSMT parameter sets. `generate_xmss` draws three disjoint secret/public seed fields. `issue_xmss` returns a successor key state and a signature. Both constructions recompute subtrees directly, so large tree heights can make key generation and signing expensive.
- The signature APIs consume octet strings. Hashes and encoded fields use fixed-width Prelude integers. The shared hash primitives are in `crypto_prelude/prehash/hbs_hash`. The executable signing functions expose the key state needed by a protected cryptographic module.

Use each fresh random stream once. A deployment must serialize signing operations and atomically commit the successor state to rollback-resistant nonvolatile storage before releasing a signature or certificate. This includes an advanced state returned on a random-provider failure. The PVS values model the state transition. Persistence, anti-cloning, an approved random-bit generator, and the hardware protections in SP 800-208 are implementation obligations.

## Reproduce the checks

Run `python3 validation/check.py lms xmss` from the crypto directory. The driver replays each saved proof, translates the operational theories, and compares generated C against the bundled fixtures with address and undefined-behavior sanitizers.

The LMS/HSS harness verifies 16 published NIST cases, both signatures from [RFC 8554 Appendix F](https://www.rfc-editor.org/rfc/rfc8554#appendix-F), a byte-exact signature generated from the second RFC example’s seed, and a child-tree rollover. The source NIST ACVP internal-projection files have SHA-256 digests `015bb30cb60d4fb24bc69d0cb074965c5fd10d1c70b01d09a5914d4947e2dedf` and `298bf08f3dab576483b731dc58a4feab18b93e1e741bc6192133285962cf77dd`. [NIST SP800-208 vectors](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/LMS-sigVer-SP800-208) · [NIST 1.0 vectors](https://github.com/usnistgov/ACVP-Server/tree/master/gen-val/json-files/LMS-sigVer-1.0)

The XMSS fixture contains eight valid and eight altered signatures and two byte-exact key/signature checks from the [RFC authors’ reference implementation](https://github.com/XMSS/xmss-reference). Its source archive had SHA-256 digest `01e21ee0ec2c6269974118098741e6303a81efc43eb206f29d63833633e05db9`. The concatenated S_XMSS, SK_PRF, and SEED fields are consecutive bytes starting at zero. The message is hex `255b`. Single-tree OIDs 1, 13, 16, and 19 use index 3. Multi-tree OIDs 2, 34, 42, and 50 use index 65566. The exact generation checks use XMSSMT-SHA2_20/4_192.

The typechecked `hbs_claims` theory states LMS, HSS, XMSS, and XMSSMT signing/verification agreement, live HSS leaf consumption, and monotonically increasing XMSS indices. Their general proofs are open.
