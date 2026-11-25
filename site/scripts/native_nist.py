"""Frame official ACVP projections for the repository's conformance drivers."""
import base64
import importlib.util
import json
from pathlib import Path
import subprocess
from collections import Counter


def module(path):
    spec = importlib.util.spec_from_file_location("acvp_converter", path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def framed(identifier, data):
    return {"id": str(identifier), "data": base64.b64encode(data).decode(), "expected": "pass"}


def prepare_native_nist(selected, source, begin, packet, crypto, find, cache):
    def projection(name):
        key = name + "-internalProjection.json"
        return key, json.loads(source(key))

    def converter(theory):
        return find(crypto, theory + ".pvs").parent / "acvp_inputs.py"

    for key, theory, names, scope in [
        ("mlkem", "mlkem", ["ML-KEM-keyGen-FIPS203", "ML-KEM-encapDecap-FIPS203"],
         "All published sample cases for ML-KEM-512/768/1024: key generation, encapsulation, decapsulation and key checks."),
        ("mldsa", "mldsa", ["ML-DSA-keyGen-FIPS204", "ML-DSA-sigGen-FIPS204", "ML-DSA-sigVer-FIPS204"],
         "All published sample cases for ML-DSA-44/65/87, with additional pure/prehash external-interface comparisons. Internal mu cases use the repository's message-representative converter."),
        ("lms", "lms", ["LMS-sigVer-1.0", "LMS-sigVer-SP800-208"],
         "All published LMS verification sample cases from both ACVP revisions. The driver also checks HSS rollover."),
    ]:
        begin(key, "ACVP " + key.upper(), scope, "digital-signatures" if key != "mlkem" else "key-establishment")
        if key not in selected:
            continue
        for name in names:
            archive, _ = projection(name)
            result = subprocess.check_output(["python3", converter(theory), cache / archive], text=True)
            rows = [framed("tcId " + line.split()[1 if key == "lms" else 2] + " / " + line.split()[0 if key == "lms" else 1], (line + "\n").encode())
                    for line in result.splitlines()]
            packet(key, archive, name + "/internalProjection.json", rows)

    begin("rsa", "ACVP RSA signatures", "Every non-randomized-message sample in RSA-SigGen-FIPS186-5; PKCS#1 v1.5 and PSS verification. PSS also compares the recovered encoding with the NIST salt.", "digital-signatures")
    if "rsa" in selected:
        archive, data = projection("RSA-SigGen-FIPS186-5")
        rows = [framed(int.from_bytes(b[3:7], "big"), b) for b in module(converter("rsa_encoding")).cases(data, False)]
        excluded = {"Randomized-message signatures": sum("randomValue" in t for g in data["testGroups"] for t in g["tests"])}
        packet("rsa", archive, "RSA-SigGen-FIPS186-5/internalProjection.json", rows, excluded)

    begin("rsa-keygen", "ACVP RSA key generation", "All 15 published factor/CRT samples (2048/3072/4096 bits); five also reproduce probable-prime generation using prepared random draws. Includes additional driver rejection checks.", "digital-signatures")
    if "rsa-keygen" in selected:
        archive, data = projection("RSA-KeyGen-FIPS186-5")
        payload = b"".join(module(converter("rsa_keygen")).cases(data))
        rows, offset = [], 0
        while offset < len(payload):
            start, identifier = offset, payload[offset]
            offset += 6
            for _ in range(9):
                length = int.from_bytes(payload[offset:offset + 2], "big")
                offset += 2 + length
            rows.append(framed(identifier, payload[start:offset]))
        if offset != len(payload):
            raise ValueError("Malformed RSA key generation frames")
        packet("rsa-keygen", archive, "RSA-KeyGen-FIPS186-5/internalProjection.json", rows)

    slh = None
    for key, family, prehash in [("slh-verify", "SHAKE", False), ("slh-hash", "SHAKE", True),
                                 ("slh-sha2-verify", "SHA2", False), ("slh-sha2-hash", "SHA2", True)]:
        begin(key, "ACVP " + ("HashSLH-DSA " if prehash else "SLH-DSA ") + family,
              "Every published verification sample for this hash family and interface, across all six parameter sets; includes expected rejection cases.", "digital-signatures")
        if key in selected:
            archive, data = projection("SLH-DSA-sigVer-FIPS205")
            slh = slh or module(converter("slh_verify"))
            rows = [framed(int.from_bytes(b[3:7], "big"), b) for b in slh.cases(data, False, prehash, family)]
            packet(key, archive, "SLH-DSA-sigVer-FIPS205/internalProjection.json", rows)

    begin("ascon", "ACVP Ascon", "All published Hash256, XOF128, CXOF128 and AEAD128 samples, including partial-bit inputs/outputs, nonce masking, truncated tags and authentication rejection.", "https://csrc.nist.gov/pubs/sp/800/232/final")
    if "ascon" in selected:
        for algorithm in ("Hash256", "XOF128", "CXOF128", "AEAD128"):
            name = "Ascon-" + algorithm + "-SP800-232"
            archive, data = projection(name)
            rows = []
            for group in data["testGroups"]:
                for t in group["tests"]:
                    if algorithm == "AEAD128":
                        enc = group["direction"] == "encrypt"
                        args = ["ascon-aead", int(enc), t["key"], t.get("secondKey", "00" * 16), t["nonce"],
                                t["adLen"], t["ad"] or "-", t["payloadLen"], t["pt" if enc else "ct"] or "-", t["tagLen"], t["tag"]]
                        # Encryption receives no expected ciphertext or tag.
                        if enc: args[-1] = "-"
                        expected = t["ct"] + t["tag"] if enc else t["pt"] if t["testPassed"] else "false"
                    else:
                        args = ["ascon-hash", algorithm, t["len"], t["msg"] or "-", t.get("outLen", 256), t.get("csLen", 0), t.get("cs", "") or "-"]
                        expected = t["md"]
                    rows.append({"id": str(t["tcId"]), "input": " ".join(map(str, args)), "expected": expected.lower()})
            packet("ascon", archive, name + "/internalProjection.json", rows)

    curves = {"P-" + str(n): i for i, n in enumerate((192, 224, 256, 384, 521))}
    hashes = {"SHA-1": 0, **{"SHA2-" + n: i for i, n in enumerate(("224", "256", "384", "512", "512/224", "512/256"), 1)}}
    for key, name in [("ecdsa", "ECDSA-SigVer-FIPS186-5"), ("ecdh", "KAS-ECC-CDH-Component-Sp800-56Ar3")]:
        begin(key, "ACVP " + key.upper(), "All published prime-curve samples supported by this interface" + (" with SHA-1/SHA-2 digests; expected accept/reject results." if key == "ecdsa" else "; compares the full-width shared secret."), "digital-signatures" if key == "ecdsa" else "key-establishment")
        if key not in selected: continue
        archive, data = projection(name)
        rows, excluded = [], Counter()
        for group in data["testGroups"]:
            curve = group["curve"]
            if curve not in curves or (key == "ecdsa" and group["hashAlg"] not in hashes):
                excluded[curve + " / " + group.get("hashAlg", "binary curve")] += len(group["tests"])
                continue
            for t in group["tests"]:
                fields = [t[k] for k in (("qx", "qy", "r", "s", "message") if key == "ecdsa" else ("privateIut", "publicServerX", "publicServerY"))]
                args = [key, curves[curve], *([hashes[group["hashAlg"]]] if key == "ecdsa" else []), *(v or "-" for v in fields)]
                rows.append({"id": str(t["tcId"]), "input": " ".join(map(str, args)), "expected": str(t["testPassed"]).lower() if key == "ecdsa" else t["z"].lower()})
        packet(key, archive, name + "/internalProjection.json", rows, excluded)
