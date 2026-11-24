#!/usr/bin/env python3
"""Replay saved proofs, generate C and execute the selected conformance cases."""
import argparse
import gzip
import os
import re
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile

from pvs_cli import add_pvs_argument, pvs2c_runtime

ROOT = Path(__file__).resolve().parents[1]
WORDS = ["crypto_prelude/crypto_words"]
SHS = [*WORDS, "sha2/secure_hash"]
KECCAK = [*WORDS, "sha3/keccak"]
HMAC = [*SHS, "crypto_prelude/crypto_buffers", "sha3/keccak", "hmac/keyed_hash"]
ED25519 = [*SHS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_u256", "eddsa/ed25519"]
ED448 = [*KECCAK, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs", "eddsa/ed448"]
SLH_WOTS = [*SHS, "crypto_prelude/crypto_buffers", "sha2/sha2_stream", "sha3/keccak", "slhdsa/slh_wots"]
SLH_VERIFY = [*SLH_WOTS, "slhdsa/slh_verify"]
SLH_HASH = [*SLH_VERIFY, "slhdsa/slh_sign", "crypto_prelude/prehash/crypto_prehash", "slhdsa/slh_prehash"]
SUITES = {
    "random": (["crypto_prelude/crypto_random", "random_bits/health_tests"], "random_checks.c"),
    "ascon": ([*WORDS, "ascon/ascon", "ascon/ascon_options"], "ascon_checks.c"),
    "sha2": ([*SHS, "sha2/secure_hash_examples"], None),
    "sha2-cavp": (SHS, "shs_checks.c"),
    "sha3": ([*KECCAK, "sha3/sp800_185", "sha3/keccak_examples"], None),
    "edwards-isogeny": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                         "ecc_extra/montgomery", "ecc_extra/curve_maps", "ecc_extra/edwards_isogeny",
                         "ecc_extra/isogeny_examples"], None),
    "montgomery": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                    "ecc_extra/montgomery", "ecc_extra/curve_maps", "ecc_extra/montgomery_examples"], None),
    "appendix-h": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                   "ecc_extra/appendix_h", "ecc_extra/appendix_h_ecc"], "../ecc_extra/appendix_h_check.c"),
    "binary-encoding": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                         "ecc_extra/binary_parameters", "ecc_extra/binary_curve",
                         "ecc_extra/binary_encoding", "ecc_extra/binary_encoding_examples"], None),
    "binary-ecdsa": ([*SHS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                      "ecc_extra/binary_parameters", "ecc_extra/binary_curve", "ecc_extra/binary_ecdsa"],
                     "../ecc_extra/binary_cavp.c"),
    "wots": (SLH_WOTS, "wots_checks.c"),
    "slh_verify": (SLH_VERIFY, "../slhdsa/acvp_verify.c"),
    "slh_sign": ([*SLH_VERIFY, "slhdsa/slh_sign"], "../slhdsa/acvp_sign.c"),
    "slh_hash": (SLH_HASH, "../slhdsa/acvp_hash.c"),
    "slh_sha2_verify": (SLH_VERIFY, "../slhdsa/acvp_verify.c"),
    "slh_sha2_sign": ([*SLH_VERIFY, "slhdsa/slh_sign"], "../slhdsa/acvp_sign.c"),
    "slh_sha2_hash": (SLH_HASH, "../slhdsa/acvp_hash.c"),
    "hmac": ([*HMAC, "hmac/hmac_drbg", "hmac/hmac_examples"], None),
    "hmac-reseed": ([*HMAC, "hmac/hmac_drbg", "hmac/drbg_reseed_examples"], None),
    "hash-drbg": ([*HMAC, "hmac/hmac_drbg", "crypto_prelude/crypto_add_bytes",
                   "random_bits/hash_drbg", "random_bits/hash_drbg_examples"], None),
    "pbkdf2": ([*HMAC, "kdf/password_kdf", "kdf/password_kdf_examples"], None),
    "key-agreement": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                       "crypto_prelude/crypto_montgomery", "crypto_prelude/crypto_associate",
                       "ecc/nist_prime_curves", "ecc/prime_curve", "key_agreement/ff_agreement",
                       "key_agreement/ff_groups", "key_agreement/ec_mqv", "key_agreement/dsa_verify"],
                      "../key_agreement/checks.c"),
    "protocol-kdf": ([*HMAC, "sha3/sp800_185", "kdf/prf_iteration", "kdf/prf_kdf",
                      "crypto_prelude/crypto_buffer_lengths", "kdf/protocol_kdf",
                      "kdf/tls_legacy_prf"], "protocol_kdf_checks.c"),
    "prf-kdf": ([*HMAC, "sha3/sp800_185", "kdf/prf_iteration", "kdf/prf_kdf",
                 "kdf/establishment_kdf", "kdf/prf_kdf_examples"], None),
    "ed25519": ([*ED25519, "eddsa/ed25519_examples"], None),
    "ed25519-keygen": ([*ED25519, "crypto_prelude/crypto_random", "crypto_prelude/crypto_random_buffers",
                        "crypto_prelude/crypto_seeds",
                        "eddsa/ed25519_random"], "ed25519_key_checks.c"),
    "ed448": ([*ED448, "eddsa/ed448_examples"], None),
    "ed448-keygen": ([*ED448, "eddsa/ed448_examples", "crypto_prelude/crypto_random",
                      "crypto_prelude/crypto_random_buffers", "eddsa/ed448_random"], "ed448_key_checks.c"),
    "mlkem": ([*KECCAK, "crypto_prelude/crypto_buffers", "mlkem/mlkem_ring",
               "mlkem/mlkem_encoding", "mlkem/mlkem", "crypto_prelude/crypto_random",
               "crypto_prelude/crypto_random_buffers", "crypto_prelude/crypto_seeds", "mlkem/mlkem_random"], "../mlkem/acvp.c"),
    "mldsa": ([*SHS, "sha3/keccak", "crypto_prelude/crypto_buffers",
               "crypto_prelude/crypto_random", "crypto_prelude/crypto_random_buffers",
               "crypto_prelude/crypto_seeds", "crypto_prelude/prehash/crypto_prehash",
               "mldsa/mldsa_ring", "mldsa/mldsa_encoding", "mldsa/mldsa", "mldsa/mldsa_sign",
               "mldsa/mldsa_prehash", "mldsa/mldsa_random"], "../mldsa/acvp.c"),
}
HBS = [*SHS, "sha3/keccak", "crypto_prelude/crypto_buffers", "crypto_prelude/prehash/hbs_hash",
       "crypto_prelude/crypto_random", "crypto_prelude/crypto_random_buffers"]
SUITES.update({
    "rsa-keygen": ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                    "crypto_prelude/crypto_montgomery", "crypto_prelude/crypto_integer_ops",
                    "crypto_prelude/crypto_random", "crypto_prelude/crypto_random_buffers",
                    "rsa_keygen/rsa_primes", "rsa_keygen/rsa_keygen"], "../rsa_keygen/acvp.c"),
    "lms": ([*HBS, "crypto_prelude/crypto_seeds", "stateful_signatures/lms_hash",
             "stateful_signatures/lms", "stateful_signatures/hss", "stateful_signatures/lms_sign",
             "stateful_signatures/hss_sign"], "../stateful_signatures/acvp.c"),
    "xmss": ([*HBS, "stateful_signatures/xmss_wots", "stateful_signatures/xmss",
              "stateful_signatures/xmss_sign"], "../stateful_signatures/xmss_vectors.c"),
})
SUITES["rsa-provable"] = (
    [*SUITES["rsa-keygen"][0], "sha2/secure_hash", "sha3/keccak", "crypto_prelude/prehash/crypto_prehash",
     "rsa_keygen/shawe_taylor", "rsa_keygen/rsa_provable"], "../rsa_keygen/provable.c")
SUITES["rsa-auxiliary"] = (
    [*SUITES["rsa-provable"][0], "rsa_keygen/rsa_auxiliary"], "../rsa_keygen/auxiliary.c")
SUITES["keccak-p"] = ([*KECCAK, "sha3/keccak_p"], "../sha3/keccak_p_checks.c")
SUITES["dh-schemes"] = (
    [*HMAC, "sha3/sp800_185", "kdf/prf_iteration", "kdf/prf_kdf", "kdf/establishment_kdf",
     "crypto_prelude/crypto_limbs", "crypto_prelude/crypto_montgomery", "crypto_prelude/crypto_associate",
     "ecc/nist_prime_curves", "ecc/prime_curve", "key_agreement/ff_agreement", "key_agreement/ec_mqv",
     "key_agreement/dh_schemes", "key_agreement/dh_derivation"], "../key_agreement/dh_cavp.c")
FIXTURES = {
    "appendix-h": ("ecc_extra/appendix_h_vectors.txt.gz", "Appendix H: 11 domain, CDH and ECDSA cases passed"),
    "binary-ecdsa": ("ecc_extra/binary_cavp.txt.gz", "Binary ECDSA CAVP: 20 of 20 cases passed"),
    "keccak-p": ("sha3/keccak_p_sample.txt.gz", "Keccak-p permutations: 29 of 29 checks passed"),
    "dh-schemes": ("key_agreement/dh_cavp.txt.gz", "SP 800-56A participant and KDF vectors: 28 of 28 passed"),
    "rsa-provable": ("rsa_keygen/provable_sample.txt.gz", "RSA provable generation: 2 of 2 cases passed"),
    "rsa-auxiliary": ("rsa_keygen/auxiliary_sample.txt.gz", "RSA auxiliary generation: 2 of 2 cases passed"),
    "rsa-keygen": ("rsa_keygen/acvp_sample.bin.gz", "RSA key generation: 27 of 27 checks passed"),
    "lms": ("stateful_signatures/lms_sample.txt.gz", "LMS/HSS vectors: 20 of 20 cases passed"),
    "xmss": ("stateful_signatures/xmss_sample.txt.gz", "XMSS reference: 18 of 18 checks passed"),
    "sha2-cavp": ("sha2/shavs_sample.txt.gz", "SHAVS: 105 bit-oriented cases passed"),
    "mlkem": ("mlkem/acvp_sample.txt.gz", "ML-KEM ACVP: 12 of 12 cases passed"),
    "mldsa": ("mldsa/acvp_sample.txt.gz", "ML-DSA ACVP: 30 of 30 cases passed"),
    "slh_sha2_verify": ("slhdsa/acvp_sha2_verify_sample.bin.gz",
                        "SLH-DSA SHA2 ACVP verification: 24 of 24 cases passed."),
    "slh_sha2_sign": ("slhdsa/acvp_sha2_sign_sample.bin.gz",
                      "SLH-DSA SHA2-128f ACVP key generation and signing passed."),
    "slh_sha2_hash": ("slhdsa/acvp_sha2_hash_sample.bin.gz",
                      "HashSLH-DSA SHA2 ACVP verification: 20 of 20 cases passed."),
    "slh_verify": ("slhdsa/acvp_verify_sample.bin.gz",
                   "SLH-DSA SHAKE ACVP verification: 24 of 24 cases passed."),
    "slh_sign": ("slhdsa/acvp_sign_sample.bin.gz",
                 "SLH-DSA SHAKE-128f ACVP key generation and signing passed."),
    "slh_hash": ("slhdsa/acvp_hash_sample.bin.gz",
                 "HashSLH-DSA SHAKE ACVP verification: 19 of 19 cases passed."),
}


EC = [*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
      "ecc/nist_prime_curves", "ecc/prime_curve", "ecc/ecdsa"]
SUITES["ec"] = (EC, "ec_checks.c")
RANDOM_SOURCE = ["crypto_prelude/crypto_random", "crypto_prelude/crypto_random_buffers"]
SUITES["ec-signing"] = (list(dict.fromkeys([*HMAC, *EC, "hmac/hmac_drbg", *RANDOM_SOURCE,
                                            "ecc/ecdsa_signing", "crypto_prelude/prehash/crypto_prehash",
                                            "ecc/ecdsa_extra_bits"])), "ec_checks.c")
SUITES["rbg"] = ([*HMAC, "hmac/hmac_drbg", *RANDOM_SOURCE, "crypto_prelude/crypto_xor",
                  "random_bits/rbg_constructions", "random_bits/rbg_tree"], "rbg_checks.c")
SUITES["key-generation"] = ([*HMAC, *RANDOM_SOURCE, "crypto_prelude/crypto_xor",
                             "key_generation/key_generation"], "key_generation_checks.c")
RSA = [*HMAC, "crypto_prelude/crypto_limbs", "crypto_prelude/crypto_montgomery",
       "rsa/rsa_primitive", "rsa/rsa_encoding"]
SUITES["rsa-private"] = ([*RSA, *RANDOM_SOURCE, "rsa/rsa_random"], "../rsa/private_checks.c")
FIXTURES["rsa-private"] = ("rsa/private_sample.bin.gz", "RSA private operation, OAEP, RSASVE, PSS and failure checks passed.")
SUITES["rsa-kas"] = ([*RSA, *RANDOM_SOURCE, "rsa/rsa_random", "sha3/sp800_185", "kdf/prf_iteration",
                      "kdf/prf_kdf", "kdf/establishment_kdf", "crypto_prelude/key_confirmation/pairwise_confirmation",
                      "rsa/rsa_kas"], "../rsa/private_checks.c")
FIXTURES["rsa-kas"] = ("rsa/private_sample.bin.gz", "KAS1, KAS2 and key confirmation checks passed.")
SUITES["storage-random"] = ([*HMAC, *RANDOM_SOURCE, "kdf/password_kdf", "kdf/storage_random"], "storage_random_checks.c")
SUITES["kem"] = (list(dict.fromkeys([*HMAC, *SUITES["mlkem"][0],
                                      "crypto_prelude/key_confirmation/pairwise_confirmation",
                                      "kem/composite_kem", "kem/kem_confirmation"])), "kem_checks.c")
SUITES["hash-conditioning"] = ([*HMAC, *RANDOM_SOURCE, "random_bits/hash_conditioning"], "conditioning_checks.c")
SUITES["iv-generation"] = ([*WORDS, "crypto_prelude/crypto_buffers", *RANDOM_SOURCE, "modes/iv_generation"], "iv_generation_checks.c")
SUITES["bit-derivation"] = ([*HMAC, "crypto_prelude/crypto_bit_prefix", "hmac/hash_truncation",
                            "sha3/sp800_185", "sha3/squeeze_bits", "kdf/prf_iteration", "kdf/prf_kdf",
                            "kdf/establishment_kdf", "kdf/bit_derivation"], "bit_derivation_checks.c")
SUITES["mcv"] = ([*WORDS, "crypto_prelude/crypto_buffers", "crypto_prelude/crypto_limbs",
                 "crypto_prelude/crypto_montgomery", "crypto_prelude/crypto_integer_ops",
                 "random_bits/mcv_estimate", "random_bits/mcv_entropy"], "mcv_checks.c")
SUITES["rsa"] = (RSA, "../rsa/acvp.c")
FIXTURES["rsa"] = ("rsa/acvp_sample.bin.gz", "RSA ACVP signatures: 18 of 18 cases passed.")


def run_suite(suite, stage, pvs, env, replay=True):
    theories, harness = SUITES[suite]
    runtime = pvs2c_runtime(pvs)
    includes = [runtime / "include"]
    sources = []
    env = {**env, "PVS_LIBRARY_PATH": os.pathsep.join(
        part for part in (str(stage), env.get("PVS_LIBRARY_PATH")) if part)}
    for item in theories:
        source = Path(item)
        name = source.name
        directory = stage / source.parent
        directory.mkdir(parents=True, exist_ok=True)
        saved = (ROOT / source.with_suffix(".prf")).is_file()
        replay_theory = replay and saved
        for suffix in ((".pvs", ".prf") if replay_theory else (".pvs",)):
            shutil.copy(ROOT / source.with_suffix(suffix), directory)
        lisp_replay = "t" if replay_theory else "nil"
        action = (f'(handler-case (progn (crypto-replay-generate "{name}" {lisp_replay}) (uiop:quit 0)) '
                  '(error (e) (format t "~%FAILED ~a~%" e) (uiop:quit 1)))')
        cmd = [pvs, "-raw", "-L", ROOT / "crypto_prelude/crypto-random-attachments.lisp",
               "-L", ROOT / "validation/replay-generate.lisp", "-E", action]
        result = subprocess.run(cmd, cwd=directory, env=env, stdin=subprocess.DEVNULL,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
        if result.returncode or f"CRYPTO-OK {name}" not in result.stdout:
            raise SystemExit(result.stdout[-6000:])
        if replay_theory:
            print(next(line for line in result.stdout.splitlines()
                       if line.startswith("Checked ") and line.endswith(f" in {name}.")), flush=True)
        else:
            note = " No saved proof file." if replay and not saved else ""
            print(f"Generated {name}.{note}", flush=True)
        include_dir = directory / "pvs2c/include"
        if include_dir not in includes:
            includes.append(include_dir)
        # Length equations are proof-only and emit no C translation unit.
        if item != "crypto_prelude/crypto_buffer_lengths":
            sources.append(directory / f"pvs2c/src/{name}_c.c")

    gmp = subprocess.check_output(["pkg-config", "--cflags", "--libs", "gmp"], text=True)
    cmd = [*shlex.split(env.get("CC", "cc")), "-std=c11", "-O1", "-g",
           "-Wno-deprecated-declarations", "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
           "-include", ROOT / "crypto_prelude/crypto_bits_compat.h"]
    for include_dir in includes:
        cmd.extend(["-I", include_dir])
    binary = stage / f"check_{suite}"
    if harness:
        main_file = ROOT / "validation" / harness
    else:
        # PVS2C generates a reporting main for _TEST_ declarations.
        main_file = directory / f"pvs2c/src/{name}.c"
    subprocess.run([*cmd, *sources, main_file, runtime / "lib/libpvs-prelude.a",
                    *shlex.split(gmp), "-o", binary], check=True)
    if harness:
        if suite in FIXTURES:
            fixture, expected_message = FIXTURES[suite]
            cases = gzip.decompress((ROOT / fixture).read_bytes())
            result = subprocess.run([binary], input=cases, capture_output=True, check=True)
            print(result.stdout.decode(), end="")
            if expected_message not in result.stdout.decode():
                raise SystemExit(f"Incomplete case results for {suite}")
        else:
            subprocess.run([binary], check=True)
        return
    text = (ROOT / source.with_suffix(".pvs")).read_text()
    expected = set(re.findall(r"^\s*(\w+)\s*:\s*_TEST_\b", text, re.M | re.I))
    run = subprocess.run([binary], text=True, stdout=subprocess.PIPE, check=True)
    print(run.stdout, end="")
    passed = set(re.findall(rf"^{name}\.(\w+) ==> true$", run.stdout, re.M))
    if not expected or passed != expected:
        raise SystemExit(f"Test results differ for {name}: expected {expected}, passed {passed}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("suites", nargs="*", help="available suites: " + ", ".join(SUITES))
    parser.add_argument("--generate-only", action="store_true", help="typecheck and test generated C without proof replay")
    add_pvs_argument(parser)
    args = parser.parse_args()
    pvs = args.pvs
    for suite in args.suites or SUITES:
        if suite not in SUITES:
            parser.error(f"unknown suite {suite}")
        with tempfile.TemporaryDirectory(prefix=f"pvs-{suite}-") as path:
            stage = Path(path)
            run_suite(suite, stage, pvs, dict(os.environ, PVS_LOG_DIR=str(stage)), replay=not args.generate_only)


if __name__ == "__main__":
    main()
