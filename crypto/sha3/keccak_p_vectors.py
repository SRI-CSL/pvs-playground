"""Generate bit-array FIPS 202 Algorithm 7 cases and check XKCP's four transcripts."""
import argparse
import gzip
import re
import sys
from pathlib import Path


def rc(t):
    bits = [1, 0, 0, 0, 0, 0, 0, 0]
    for _ in range(t % 255):
        bits = [0] + bits
        for j in (0, 4, 5, 6):
            bits[j] ^= bits[8]
        bits = bits[:8]
    return bits[0]


def permutation(state, log, count):
    w = 1 << log
    a = {(x, y, z): (state[x + 5*y] >> z) & 1 for x in range(5) for y in range(5) for z in range(w)}
    off = {(0, 0): 0}
    x, y = 1, 0
    for t in range(24):
        off[x, y] = (t+1)*(t+2)//2
        x, y = y, (2*x+3*y) % 5
    for ir in range(12+2*log-count, 12+2*log):
        c = {(x,z): sum(a[x,y,z] for y in range(5)) % 2 for x in range(5) for z in range(w)}
        a = {(x,y,z): v ^ c[(x-1)%5,z] ^ c[(x+1)%5,(z-1)%w] for (x,y,z),v in a.items()}
        b = {(y,(2*x+3*y)%5,(z+off[x,y])%w): v for (x,y,z),v in a.items()}
        a = {(x,y,z): v ^ ((1-b[(x+1)%5,y,z]) & b[(x+2)%5,y,z]) for (x,y,z),v in b.items()}
        for j in range(log+1):
            a[0,0,(1 << j)-1] ^= rc(j+7*ir)
    return [sum(a[i%5,i//5,z] << z for z in range(w)) for i in range(25)]


def row(log,n,src,dst):
    return " ".join([str(log),str(n),*(f"{x:x}" for x in src),*(f"{x:x}" for x in dst)])


parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("xkcp",type=Path,help="directory containing f200.txt, f400.txt, f800.txt, f1600.txt")
parser.add_argument("--gzip",action="store_true")
opts = parser.parse_args()
rows = []
for log in range(7):
    w = 1 << log
    state = [((i+1)*0x9e3779b97f4a7c15 + i*i) & ((1 << w)-1) for i in range(25)]
    for count in [1,12+2*log,19+2*log]:
        rows.append(row(log,count,state,permutation(state,log,count)))
    if w >= 8:
        transcript = (opts.xkcp/f"f{25*w}.txt").read_text()
        fields = [bytes.fromhex(v) for v in re.findall(r"(?:Input of permutation|State after permutation):\s*\n([^\n]+)",transcript)]
        assert len(fields)==4
        for k in (0,2):
            a,b = [[int.from_bytes(s[i:i+w//8],"little") for i in range(0,len(s),w//8)] for s in fields[k:k+2]]
            assert permutation(a,log,12+2*log)==b
            rows.append(row(log,12+2*log,a,b))
data=("\n".join(rows)+"\n").encode()
sys.stdout.buffer.write(gzip.compress(data,mtime=0) if opts.gzip else data)
