#!/usr/bin/env python3
"""Generate AES in a clean context and run the compiled PVS test declarations."""
import argparse
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import zipfile

from pvs_cli import add_pvs_argument, pvs2c_runtime

ROOT = Path(__file__).resolve().parents[1]
MODULES = {
    "crypto_prelude": ["crypto_octets", "simplifications", "hex", "bytevectors", "bytevector_tests"],
    "aes": ["Rijndael", "aes_fips197", "aes_fips197_tests"],
}


MODE_CHECKS = {"modes": "aes_modes", "gcm": "gcm", "ccm": "ccm", "gcm_bits": "gcm_bits",
               "key_wrap": "key_wrap", "xts": "xts", "cbc_cs": "cbc_cs", "fpe": "fpe", "srtp": "srtp_kdf"}


DRBG_AND_KDF = {
    "aes-conditioning": ("random_bits", ["ctr_drbg", "aes_conditioning"], 8),
    "cmac-kdf": ("kdf", ["prf_iteration", "cmac_kdf", "cmac_kdf_examples"], 3),
    "ctr-drbg": ("random_bits", ["ctr_drbg", "ctr_drbg_examples"], 6),
}


def generate(stage, pvs, directory, name, env, replay=()):
    replays = " ".join(f'(crypto-replay "{theory}")' for theory in replay)
    action = (f'(handler-case (progn {replays} (tc "{name}") (pvs2c-theory "{name}" t) '
              f'(uiop:quit 0)) (error (e) (format t "~%FAILED ~a~%" e) (uiop:quit 1)))')
    load = ["-L", ROOT / "validation/replay-generate.lisp"] if replay else []
    result = subprocess.run([pvs, "-raw", *load, "-E", action], cwd=stage / directory,
                            env=env, stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True, errors="replace")
    header = stage / directory / "pvs2c/include" / f"{name}_c.h"
    if result.returncode or not header.exists():
        raise SystemExit(result.stdout[-7000:])
    for theory in replay:
        line = next((line for line in result.stdout.splitlines() if line.startswith("Checked ")
                     and line.endswith(f" in {theory}.")), None)
        if line is None:
            raise SystemExit(f"Missing proof replay for {theory}")
        print(line, flush=True)


def cavp_cases(archive):
    with zipfile.ZipFile(archive) as vectors:
        for bits in (128, 192, 256):
            for family in ("GFSbox", "KeySbox", "VarKey", "VarTxt"):
                name = f"ECB{family}{bits}.rsp"
                fields = {}
                direction = None
                seen = set()
                for line in vectors.read(name).decode("ascii").splitlines():
                    line = line.strip()
                    if line in ("[ENCRYPT]", "[DECRYPT]"):
                        direction = line[1:-1]
                    elif " = " in line:
                        key, value = line.split(" = ")
                        if key == "COUNT":
                            fields.clear()
                        fields[key] = value
                        if all(k in fields for k in ("KEY", "PLAINTEXT", "CIPHERTEXT")):
                            key, plain, cipher = (fields[k] for k in ("KEY", "PLAINTEXT", "CIPHERTEXT"))
                            if (direction is None or len(bytes.fromhex(key)) * 8 != bits or
                                    len(bytes.fromhex(plain)) != 16 or len(bytes.fromhex(cipher)) != 16):
                                raise ValueError(f"Malformed case in {name}")
                            seen.add(direction)
                            a, b = (plain, cipher) if direction == "ENCRYPT" else (cipher, plain)
                            yield f"{direction[0]} {key} {a} {b}\n"
                            fields.clear()
                if seen != {"ENCRYPT", "DECRYPT"}:
                    raise ValueError(f"Missing encrypt/decrypt cases in {name}")


def check(stage, args):
    pvs = args.pvs
    runtime = pvs2c_runtime(pvs)
    modules = {k: list(v) for k, v in MODULES.items()}
    if args.suite in MODE_CHECKS or args.suite in DRBG_AND_KDF:
        modules["crypto_prelude"].append("crypto_blocks")
        modules["modes"] = ["aes_modes"]
    if args.suite in MODE_CHECKS and args.suite != "modes":
        modules["crypto_prelude"] += ["crypto_buffers", "crypto_block_io", "crypto_words"]
        modules["modes"].append(MODE_CHECKS[args.suite])
    if args.suite in DRBG_AND_KDF:
        app, theories, expected_tests = DRBG_AND_KDF[args.suite]
        modules["crypto_prelude"] += ["crypto_buffers", "crypto_block_io", "crypto_words"]
        modules[app] = theories
    if args.suite == "aes-conditioning":
        modules["kdf"] = ["prf_iteration", "cmac_kdf"]
    if args.suite == "gcm_bits":
        modules["modes"].insert(-1, "gcm")
    if args.suite == "fpe":
        modules["crypto_prelude"].append("crypto_radix")
    if args.suite in ("xts", "cbc_cs"):
        modules["crypto_prelude"].append("crypto_bit_splice")
    replay = {
        "crypto_prelude": [name for name in modules["crypto_prelude"]
                           if name in ("crypto_words", "crypto_blocks", "crypto_buffers", "crypto_block_io", "crypto_radix")],
        "aes": ["aes_fips197"],
        "modes": modules.get("modes", []),
    }
    if args.suite in DRBG_AND_KDF:
        replay[app] = theories
    if args.suite == "fpe":
        # The saved scalar proofs predate the variable-length radix development.
        for folder, name in (("crypto_prelude", "crypto_radix"), ("modes", "fpe")):
            if not (ROOT / folder / f"{name}.prf").exists():
                replay[folder] = [theory for theory in replay[folder] if theory != name]
                print(f"{name}: new proof obligations open", flush=True)
    if args.generate_only:
        replay = {folder: [] for folder in modules}
    for directory, names in modules.items():
        (stage / directory).mkdir()
        for name in names:
            shutil.copy(ROOT / directory / f"{name}.pvs", stage / directory)
            if name in replay.get(directory, ()):
                shutil.copy(ROOT / directory / f"{name}.prf", stage / directory)
    env = dict(os.environ, PVS_LOG_DIR=str(stage))
    generate(stage, pvs, "crypto_prelude", "bytevector_tests", env, replay["crypto_prelude"])
    generate(stage, pvs, "aes", "aes_fips197_tests", env, replay["aes"])
    if args.suite in MODE_CHECKS:
        generate(stage, pvs, "modes", MODE_CHECKS[args.suite], env, replay["modes"])
    if args.suite in DRBG_AND_KDF:
        generate(stage, pvs, app, theories[-1], env, replay=replay[app])
    cdirs = [stage / d / "pvs2c" for d in modules]
    sources = [src for d in cdirs for src in sorted((d / "src").glob("*_c.c"))]
    flags = [*shlex.split(os.environ.get("CC", "cc")), "-O1", "-g",
             "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
             "-Wno-incompatible-pointer-types", "-Wno-deprecated-declarations",
             "-I", runtime / "include", "-include", ROOT / "crypto_prelude/crypto_bits_compat.h"]
    for directory in cdirs:
        flags.extend(["-I", directory / "include"])
    gmp_cflags = shlex.split(subprocess.check_output(["pkg-config", "--cflags", "gmp"], text=True))
    gmp_libs = shlex.split(subprocess.check_output(["pkg-config", "--libs", "gmp"], text=True))
    objects = []
    for src in sources:
        obj = stage / f"{src.parent.parent.parent.name}-{src.stem}.o"
        subprocess.run([*flags, *gmp_cflags, "-c", src, "-o", obj], check=True)
        objects.append(obj)

    def build(main):
        binary = stage / main.stem
        subprocess.run([*flags, *gmp_cflags, main, *objects, runtime / "lib/libpvs-prelude.a",
                        *gmp_libs, "-o", binary], check=True)
        return binary

    for folder, name, count in (("crypto_prelude", "bytevector_tests", 9),
                                ("aes", "Rijndael", 3), ("aes", "aes_fips197_tests", 4)):
        binary = build(stage / folder / "pvs2c/src" / f"{name}.c")
        lines = subprocess.check_output([binary], text=True).splitlines()
        if len(lines) != count or not all(line.endswith(" ==> true") for line in lines):
            raise SystemExit("\n".join(lines))
        print("\n".join(lines), flush=True)
    if args.kat_zip:
        cases = list(cavp_cases(args.kat_zip))
        executable = build(ROOT / "validation/aes_kat.c")
        subprocess.run([executable], input="".join(cases), text=True, check=True)
        print(f"Passed {len(cases)} AESAVS ECB encrypt/decrypt cases.")
    if args.suite in MODE_CHECKS:
        subprocess.run([build(ROOT / "validation/modes_checks.c")], check=True)
    if args.suite in MODE_CHECKS and args.suite != "modes":
        subprocess.run([build(ROOT / "validation" / f"{args.suite}_checks.c")], check=True)
    if args.suite == "aes-conditioning":
        subprocess.run([build(ROOT / "validation/aes_conditioning_checks.c")], check=True)
    elif args.suite in DRBG_AND_KDF:
        binary = build(stage / app / f"pvs2c/src/{theories[-1]}.c")
        answers = subprocess.check_output([binary], text=True).splitlines()
        if len(answers) != expected_tests or not all(line.endswith(" ==> true") for line in answers):
            raise SystemExit("\n".join(answers))
        print("\n".join(answers))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("suite", nargs="?", choices=["aes", *MODE_CHECKS, *DRBG_AND_KDF], default="aes")
    add_pvs_argument(parser)
    parser.add_argument("--generate-only", action="store_true", help="typecheck and test generated C without proof replay")
    parser.add_argument("--kat-zip", type=Path, help="NIST CAVP KAT_AES.zip")
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix="pvs-aes-") as directory:
        check(Path(directory), args)
