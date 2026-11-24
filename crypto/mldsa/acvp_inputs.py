"""Translate NIST ACVP ML-DSA internalProjection.json files to acvp.c cases."""
import hashlib
import json
import sys

# DER id-sha* OIDs in FIPS 204 Algorithm 4.
hashes = {"SHA2-256": (1, "sha256"), "SHA2-384": (2, "sha384"),
          "SHA2-512": (3, "sha512"), "SHA2-224": (4, "sha224"),
          "SHA2-512/224": (5, "sha512_224"), "SHA2-512/256": (6, "sha512_256"),
          **{f"SHA3-{n}": (i, f"sha3_{n}") for i, n in enumerate((224,256,384,512),7)},
          "SHAKE-128": (11, "shake_128"), "SHAKE-256": (12, "shake_256")}


def representative(group, case):
    if group["externalMu"]:
        return case["mu"]
    msg = bytes.fromhex(case["message"])
    if group["signatureInterface"] == "external":
        ctx = bytes.fromhex(case["context"])
        pre = group["preHash"] == "preHash"
        if pre:
            oid, name = hashes[case["hashAlg"]]
            h = hashlib.new(name, msg)
            dig = h.digest(32 if oid == 11 else 64) if oid >= 11 else h.digest()
            msg = bytes.fromhex("06096086480165030402") + bytes([oid]) + dig
        msg = bytes([int(pre), len(ctx)]) + ctx + msg
    tr = hashlib.shake_256(bytes.fromhex(case["pk"])).digest(64)
    return hashlib.shake_256(tr + msg).hexdigest(64)


for path in sys.argv[1:]:
    with open(path, encoding="utf-8") as vector_file:
        groups = json.load(vector_file)["testGroups"]
    for group in groups:
        profile = {"ML-DSA-44":0, "ML-DSA-65":1, "ML-DSA-87":2}[group["parameterSet"]]
        for case in group["tests"]:
            if "seed" in case:
                args = ["keygen", case["tcId"], case["seed"], case["pk"], case["sk"]]
            elif "testPassed" in case:
                args = ["verify", case["tcId"], case["pk"], representative(group,case),
                        case["signature"], int(case["testPassed"])]
            else:
                args = ["sign", case["tcId"], case["sk"], representative(group,case),
                        case.get("rnd", "00"*32), case["signature"]]
            print(profile, *args)
            if group.get("signatureInterface") == "external":
                oid = 0 if group["preHash"] == "pure" else hashes[case["hashAlg"]][0]
                msg, ctx = case["message"] or "-", case["context"] or "-"
                if "testPassed" in case:
                    print(profile, "verify_external", case["tcId"], oid, case["pk"],
                          msg, ctx, case["signature"], int(case["testPassed"]))
                else:
                    print(profile, "sign_external", case["tcId"], oid, case["sk"],
                          msg, ctx, case.get("rnd", "00"*32), case["signature"])
