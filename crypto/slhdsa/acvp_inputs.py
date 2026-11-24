"""Convert NIST SLH-DSA sigVer internalProjection.json to length-framed cases."""
import argparse
import gzip
import json
from pathlib import Path
from struct import pack
import sys

PROFILES = ["128s", "128f", "192s", "192f", "256s", "256f"]


HASH_OIDS = ["SHA2-256", "SHA2-384", "SHA2-512", "SHA2-224", "SHA2-512/224", "SHA2-512/256",
             "SHA3-224", "SHA3-256", "SHA3-384", "SHA3-512", "SHAKE-128", "SHAKE-256"]


def cases(projection, sample=False, prehash=False, family="SHAKE"):
    seen = set()
    for group in projection["testGroups"]:
        name = group["parameterSet"]
        if not name.startswith(f"SLH-DSA-{family}-") or (group.get("preHash") == "preHash") != prehash:
            continue
        profile = PROFILES.index(name.split("-")[-1]) + (6 if family == "SHA2" else 0)
        external = group["signatureInterface"] == "external"
        for case in group["tests"]:
            expected = case["testPassed"]
            selector = 1 + HASH_OIDS.index(case["hashAlg"]) if prehash else external
            key = (selector, expected) if prehash else (profile, external, expected)
            if sample and key in seen:
                continue
            seen.add(key)
            values = [bytes.fromhex(case.get(k, "")) for k in ("pk", "signature", "context", "message")]
            yield pack(">BBBI", profile, selector, expected, case["tcId"]) + b"".join(
                pack(">I", len(v)) + v for v in values)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("projection", type=Path)
    parser.add_argument("--sample", action="store_true")
    parser.add_argument("--gzip", action="store_true")
    parser.add_argument("--prehash", action="store_true")
    parser.add_argument("--family", choices=("SHAKE", "SHA2"), default="SHAKE")
    args = parser.parse_args()
    data = b"".join(cases(json.loads(args.projection.read_bytes()), args.sample, args.prehash, args.family))
    sys.stdout.buffer.write(gzip.compress(data, mtime=0) if args.gzip else data)
