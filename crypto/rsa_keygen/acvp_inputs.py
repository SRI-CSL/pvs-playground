"""Frame the NIST RSA-KeyGen-FIPS186-5 projection for the generated-C test."""
import argparse
import gzip
import json
import math
import struct
import sys
from pathlib import Path


def cases(projection):
    for group in projection["testGroups"]:
        width = group["modulo"] // 16
        profile = {128: 0, 192: 1, 256: 2}[width]
        for test in group["tests"]:
            tcid = test["tcId"]
            values = {k: int(test[k], 16) for k in ("p", "q", "n", "e", "dmp1", "dmq1", "iqmp")}
            p, q, e = values["p"], values["q"], values["e"]
            d = pow(e, -1, math.lcm(p - 1, q - 1))
            assert values["n"] == p * q
            assert (values["dmp1"], values["dmq1"], values["iqmp"]) == (
                d % (p - 1), d % (q - 1), pow(q, -1, p)
            )
            mode = tcid in (1, 4, 13, 14, 15)
            strong = tcid in (1, 4)
            stream = b""
            if mode:
                count = ([5, 4, 4] if strong else [4, 3, 2])[profile]
                bases = [2, 3, 5, 7, 11][:count]
                # First candidate misses the size bound, base 0 must be resampled
                # and the first q draw is too close to p. Round both even draws.
                draws = [0, p - 1, 0, *bases, p, q - 1, *bases]
                stream = b"".join(value.to_bytes(width, "big") for value in draws)
            fields = [bytes.fromhex(test["e"]), p.to_bytes(width, "big"), q.to_bytes(width, "big"),
                      values["n"].to_bytes(2 * width, "big"), d.to_bytes(2 * width, "big"),
                      *(values[k].to_bytes(width, "big") for k in ("dmp1", "dmq1", "iqmp")), stream]
            yield struct.pack(">BBBBBB", tcid, profile, mode, strong, group["pMod8"], group["qMod8"])
            for value in fields:
                yield struct.pack(">H", len(value)) + value


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("projection", type=Path)
    parser.add_argument("--gzip", action="store_true")
    options = parser.parse_args()
    data = b"".join(cases(json.loads(options.projection.read_bytes())))
    sys.stdout.buffer.write(gzip.compress(data, mtime=0) if options.gzip else data)
