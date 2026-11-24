"""Frame the two probable/auxiliary-prime NIST RSA key-generation groups."""
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
    if g["randPQ"] not in ("probableWithProvableAux", "probableWithProbableAux"):
        continue
    for t in g["tests"][:1] if args.sample else g["tests"]:
        seeded = "xP1" not in t
        names = ("xP", "xQ") if seeded else ("xP1", "xP2", "xP", "xQ1", "xQ2", "xQ")
        # The ACVP projections sometimes include an extra leading 00 octet.
        # Each DRBG request returns exactly ceil(bitlen/8) octets.
        widths = dict(zip(("xP1", "xP2", "xQ1", "xQ2"),t["bitlens"]))
        starts = "".join(int(t[k],16).to_bytes((widths.get(k,g["modulo"]//2)+7)//8,"big").hex()
                         for k in names)
        rows.append(" ".join(map(str, [t["tcId"], {2048: 0, 4096: 2}[g["modulo"]],
                              int(seeded), g["pMod8"], g["qMod8"], *t["bitlens"],
                              t["e"], t["seed"], starts, t["p"], t["q"]])))
data = ("\n".join(rows) + "\n").encode()
sys.stdout.buffer.write(gzip.compress(data, mtime=0) if args.gzip else data)
