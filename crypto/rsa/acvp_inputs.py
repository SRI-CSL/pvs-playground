"""Frame the NIST ACVP RSA SigGen projection for the generated-C verifier."""
import argparse
import gzip
import json
import struct
import sys
from pathlib import Path

HASHES = ["SHA-1", "SHA2-224", "SHA2-256", "SHA2-384", "SHA2-512", "SHA2-512/224",
          "SHA2-512/256", "SHA3-224", "SHA3-256", "SHA3-384", "SHA3-512", "SHAKE-128", "SHAKE-256"]


def cases(projection, sample):
    for group in projection["testGroups"]:
        for item in group["tests"][:1] if sample else group["tests"]:
            if "randomValue" in item:
                continue
            pss = group["sigType"] == "pss"
            h = HASHES.index(group["hashAlg"])
            mask = ["mgf1", "shake-128", "shake-256"].index(group["maskFunction"]) if pss else 0
            fields = [group["n"], group["e"], item["message"], item["signature"], item.get("salt", "")]
            data = [bytes.fromhex(value) for value in fields]
            yield struct.pack(">BBBI", pss, h, mask, item["tcId"]) + b"".join(
                struct.pack(">I", len(b)) + b for b in data)


if __name__ == "__main__":
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("projection", type=Path)
    ap.add_argument("--sample", action="store_true")
    ap.add_argument("--gzip", action="store_true")
    opts = ap.parse_args()
    data = b"".join(cases(json.loads(opts.projection.read_bytes()), opts.sample))
    sys.stdout.buffer.write(gzip.compress(data,mtime=0) if opts.gzip else data)
