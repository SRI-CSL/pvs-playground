"""Build the private-operation fixture from NIST RSA DecryptionPrimitive test case 1."""
import gzip
import hashlib
import hmac
import json
import struct
import sys

def mgf1(s, n):
    return b"".join(hashlib.sha256(s+i.to_bytes(4,"big")).digest()
                    for i in range((n+31)//32))[:n]

def xor(a,b):
    return bytes(x^y for x,y in zip(a,b,strict=True))

def project(case, peer):
    n,e,d,ct,pt=[bytes.fromhex(case[k]) for k in ("n","e","d","ct","pt")]
    k=len(n)
    msg=b"transported secret"
    label=b"participants"
    seed=bytes(range(32))
    db=hashlib.sha256(label).digest()+bytes(k-66-len(msg))+b"\x01"+msg
    masked=xor(db,mgf1(seed,k-33))
    em=b"\x00"+xor(seed,mgf1(masked,32))+masked
    def rsa(x, exponent):
        return pow(int.from_bytes(x,"big"),int.from_bytes(exponent,"big"),int.from_bytes(n,"big")).to_bytes(k,"big")
    assert case["testPassed"] and rsa(ct,d)==pt and rsa(pt,e)==ct
    z=(2).to_bytes(k,"big")
    values=(n,e,d,ct,pt,label,msg,rsa(em,e),rsa(z,e))
    # Use the independent key pair from tcId 3 for the other party in KAS2.
    pn,pe,pd=[bytes.fromhex(peer[key]) for key in ("n","e","d")]
    def counted(value):
        return len(value).to_bytes(4,"big")+value
    ctx=b"".join(map(counted,(b"A256",b"Alice",b"Bob")))
    nonce=bytes(range(32))
    def derive(secret,info):
        return b"".join(hashlib.sha256(i.to_bytes(4,"big")+secret+info).digest() for i in (1,2))[:48]
    z_other=(3).to_bytes(len(pn),"big")
    one=derive(z,ctx+counted(nonce))
    two=derive(z+z_other,ctx)
    mac=hmac.digest(two[:32],b"KC_2_U"+b"AliceBobU-dataV-dataoptional","sha256")[:16]
    values+=pn,pe,pd,one,two,mac
    return b"".join(struct.pack(">I",len(v))+v for v in values)

if __name__=="__main__":
    cases=json.load(open(sys.argv[1]))["testGroups"][0]["tests"]
    assert cases[0]["tcId"]==1 and cases[2]["tcId"]==3
    sys.stdout.buffer.write(gzip.compress(project(cases[0],cases[2]),mtime=0))
