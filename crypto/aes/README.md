# AES

`aes_fips197.pvs` exposes AES-128, AES-192 and AES-256 encryption and decryption on 16-byte blocks. The 192- and 256-bit key schedules implement FIPS 197 Algorithm 2 and reuse the forward and inverse rounds from `Rijndael.pvs`. The original `Rijndael`, `invRijndael` and 16-byte string entry points remain available. [FIPS 197-upd1](https://csrc.nist.gov/pubs/fips/197/final)

## Generated C

From the crypto directory, the following builds the theories in a temporary directory and replays the 26 local AES-192/256 type obligations and runs nine shared bytevector checks, the three original AES-128 checks, and four AES-192/256 checks under AddressSanitizer and UndefinedBehaviorSanitizer.

```sh
python3 validation/check_aes.py
```

AES requires PVS2C to preserve the size of fixed arrays. PVS revision `9c378be8` emitted a 17-element loop for `below(16)`. Run the [fixed-array regression](../reproducers/aes-array/README.md) to check a generator.

To run the 2,078 additional AESAVS vectors, supply the NIST AES Known Answer Test archive. The runner reads all twelve ECB response files covering GFSbox, KeySbox, VarKey and VarTxt in both directions at each key size. [NIST CAVP block cipher vectors](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/block-ciphers)

```sh
python3 validation/check_aes.py --kat-zip KAT_AES.zip
```

## PVS proofs

Typecheck `Rijndael_proofs` and `aes_fips197_proofs` in the `aes` context. Add a directory containing NASA PVS Library's `algebra` and its dependencies to `PVS_LIBRARY_PATH`. The executable AES theories require only the PVS Prelude and this repository's `crypto_prelude`.

The source-only inverse audit replayed 377 declarations across the twenty repository theories listed in the runner. These include all 69 declarations in `Rijndael`, 61 in `Rijndael_proofs`, six in `aes_fips197_proofs`, three in `aes_modes_proofs`, and the shared polynomial, matrix, byte-vector and conversion dependencies. NASAlib supplies the imported algebra library. The original historical tactics were recovered from the matching PVS regression. [PVS AES regression development](https://github.com/samowre/pvs-tests/tree/0a90021/bugs/2022-09-13_Shankar)

```sh
python3 validation/check_aes_inverse.py --nasalib NASAlib
```
