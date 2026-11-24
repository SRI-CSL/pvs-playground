"""Frame the two provable-prime NIST RSA-KeyGen-FIPS186-5 groups."""
import argparse
import gzip
import json
import sys
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("projection", type=Path)
parser.add_argument("--sample", action="store_true")
parser.add_argument("--gzip", action="store_true")
args = parser.parse_args()
rows = []
for g in json.loads(args.projection.read_bytes())["testGroups"]:
    if g["randPQ"] not in ("provable", "provableWithProvableAux"):
        continue
    for test in g["tests"][:1] if args.sample else g["tests"]:
        sizes = [1] * 4 if g["randPQ"] == "provable" else test["bitlens"]
        rows.append(" ".join(map(str, [test["tcId"], {2048: 0, 4096: 2}[g["modulo"]],
                            {"SHA2-224": 4, "SHA2-512": 3}[g["hashAlg"]], *sizes,
                            test["e"], test["seed"], test["p"], test["q"]])))
data = ("\n".join(rows) + "\n").encode()
sys.stdout.buffer.write(gzip.compress(data, mtime=0) if args.gzip else data)
