"""Prepare checksum-pinned, independently supplied NIST expected results."""
from collections import Counter
import hashlib
import io
import json
from pathlib import Path
import re
import subprocess
import zipfile

SITE = Path(__file__).resolve().parents[1]
HASHES = {name: index for index, name in enumerate(
    ["SHA-1", "SHA-224", "SHA-256", "SHA-384", "SHA-512", "SHA-512/224", "SHA-512/256"])}
HASHES.update({"SHA" + str(bits): index for index, bits in enumerate([1, 224, 256, 384, 512])})
HASHES.update({"SHA2-" + str(bits): index for index, bits in enumerate([1, 224, 256, 384, 512])})
HASHES.update({"SHA512_224": 5, "SHA512_256": 6})
PAGES = "https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/"


def records(text):
    """Preserve section options and repeated fields such as AdditionalInput."""
    options, fields = {}, {}
    for line in text.splitlines() + [""]:
        line = line.strip()
        if not line or line.startswith("["):
            if fields:
                yield dict(options), fields
                fields = {}
            if line.startswith("["):
                value = line[1:-1]
                if "=" in value:
                    key, value = value.split("=", 1)
                    options[key.strip()] = value.strip()
                else:
                    options["section"] = value
        elif not line.startswith("#"):
            key, value = line.split("=", 1)
            fields.setdefault(key.strip().lower(), []).append(value.strip())


def value(fields, key, default="", index=0):
    return fields.get(key.lower(), [default] * (index + 1))[index]


def request(*items):
    return " ".join(str(item).lower() if str(item) else "-" for item in items)


def case(identifier, query, expected):
    expected = str(expected).lower()
    if not re.fullmatch(r"[0-9a-f]*|true|false", expected):
        raise ValueError(f"Invalid expected result: {identifier}")
    return {"id": str(identifier), "input": query, "expected": expected}


def prepare_nist(suites, cache, output):
    sources = json.loads((SITE / "nist-sources.json").read_text())
    selected = {name for suite in suites for name in suite.get("nist", [])}
    cache = cache / "nist"
    cache.mkdir(exist_ok=True)
    directory = output / "nist"
    directory.mkdir(exist_ok=True)
    sets = {}

    def source(name):
        spec = sources[name]
        path = cache / name
        if not path.exists() or hashlib.sha256(path.read_bytes()).hexdigest() != spec["sha256"]:
            temporary = path.with_suffix(".download")
            subprocess.run(["curl", "-fsSL", "--retry", "3", "--max-time", "180", spec["url"], "-o", temporary], check=True)
            temporary.replace(path)
        data = path.read_bytes()
        if hashlib.sha256(data).hexdigest() != spec["sha256"]:
            raise ValueError(f"NIST checksum mismatch: {name}")
        return data

    def begin(key, label, scope, page):
        if key in selected:
            sets[key] = {"id": key, "label": label, "scope": scope, "source": PAGES + page,
                         "files": [], "count": 0, "excluded": {}}

    def packet(key, archive, member, rows, excluded=None, extra_sources=()):
        if key not in selected:
            return
        spec = sources[archive]
        data = (json.dumps(rows, separators=(",", ":")) + "\n").encode()
        digest = hashlib.sha256(data).hexdigest()
        name = digest[:20] + ".json"
        (directory / name).write_bytes(data)
        sets[key]["files"].append({"name": member, "path": name, "sha256": digest, "count": len(rows),
                                  "archive": spec["url"], "archiveSha256": spec["sha256"],
                                  "additionalSources": [sources[name] for name in extra_sources]})
        sets[key]["count"] += len(rows)
        for reason, count in (excluded or {}).items():
            sets[key]["excluded"][reason] = sets[key]["excluded"].get(reason, 0) + count

    begin("aes", "AESAVS ECB KAT", "All ECB known-answer files; encrypt and decrypt, 128/192/256-bit keys", "block-ciphers")
    if "aes" in selected:
        with zipfile.ZipFile(io.BytesIO(source("KAT_AES.zip"))) as archive:
            names = sorted(name for name in archive.namelist() if re.fullmatch(r"ECB(GFSbox|KeySbox|VarKey|VarTxt)(128|192|256)\.rsp", name))
            if len(names) != 12:
                raise ValueError("Expected all 12 AES ECB KAT files")
            for name in names:
                rows = []
                for options, fields in records(archive.read(name).decode("ascii")):
                    enc = options["section"] == "ENCRYPT"
                    rows.append(case(value(fields, "count"), request("aes", int(enc), value(fields, "key"),
                        value(fields, "plaintext" if enc else "ciphertext")), value(fields, "ciphertext" if enc else "plaintext")))
                packet("aes", "KAT_AES.zip", name, rows)

    for key, filename, label in [("sha", "shabittestvectors.zip", "SHAVS bit-oriented"),
                                ("sha3", "sha-3bytetestvectors.zip", "SHA3VS byte-oriented"),
                                ("shake", "shakebytetestvectors.zip", "SHAKE byte-oriented")]:
        begin(key, label, "ShortMsg, LongMsg and Monte Carlo response files" if key != "shake" else
              "ShortMsg, LongMsg, VariableOut and Monte Carlo response files", "secure-hashing")
        if key not in selected:
            continue
        with zipfile.ZipFile(io.BytesIO(source(filename))) as archive:
            for name in sorted(name for name in archive.namelist() if name.endswith(".rsp")):
                family = re.sub(r"(ShortMsg|LongMsg|Monte|VariableOut)\.rsp$", "", Path(name).name)
                alg = HASHES[family] if key == "sha" else ["SHA3_224", "SHA3_256", "SHA3_384", "SHA3_512", "SHAKE128", "SHAKE256"].index(family)
                seed, next_length, rows = None, None, []
                for options, fields in records(archive.read(name).decode("ascii")):
                    if "seed" in fields or (key == "shake" and "Monte" in name and "output" not in fields):
                        seed = value(fields, "seed") or value(fields, "msg")
                        continue
                    expected = value(fields, "md") or value(fields, "output")
                    if "Monte" in name:
                        if key == "shake":
                            low = (int(options["Minimum Output Length (bits)"]) + 7) // 8
                            high = int(options["Maximum Output Length (bits)"]) // 8
                            query = request("shake-monte", alg, seed, low, high, high if next_length is None else next_length)
                            next_length = low + int(expected[-4:], 16) % (high - low + 1)
                        else:
                            query = request(key + "-monte", alg, seed)
                        seed = expected
                    else:
                        bits = int(value(fields, "len", options.get("Input Length", "0")))
                        message = value(fields, "msg") if bits else ""
                        query = request(key, alg, bits, message, len(expected) * 4)
                    rows.append(case(value(fields, "count", value(fields, "len")), query, expected))
                packet(key, filename, name, rows)

    begin("hmac", "HMACVS", "Every HMAC.rsp case for SHA-1, SHA-224/256/384/512, including truncated tags", "message-authentication")
    if "hmac" in selected:
        with zipfile.ZipFile(io.BytesIO(source("hmactestvectors.zip"))) as archive:
            rows = [case(value(fields, "count"), request("hmac", {20: 0, 28: 1, 32: 2, 48: 3, 64: 4}[int(options["L"])],
                         value(fields, "key"), value(fields, "msg"), value(fields, "tlen")), value(fields, "mac"))
                    for options, fields in records(archive.read("HMAC.rsp").decode("ascii"))]
            packet("hmac", "hmactestvectors.zip", "HMAC.rsp", rows)

    for key, name in [("hmac-drbg", "HMAC_DRBG"), ("hash-drbg", "Hash_DRBG"), ("ctr-drbg", "CTR_DRBG")]:
        begin(key, name + " DRBGVS", "All no-reseed, reseed and prediction-resistance cases" +
              (" for AES-128/192/256, with and without derivation function; TDEA excluded" if key == "ctr-drbg" else " for all seven SHA variants"), "random-number-generators")
        if key not in selected:
            continue
        with zipfile.ZipFile(io.BytesIO(source("drbgtestvectors.zip"))) as outer:
            for nested in sorted(outer.namelist()):
                reseed, pr = int("pr_false" in nested), int("pr_true" in nested)
                with zipfile.ZipFile(io.BytesIO(outer.read(nested))) as archive:
                    rows, excluded = [], Counter()
                    for options, fields in records(archive.read(name + ".rsp").decode("ascii")):
                        family = options["section"]
                        if key == "ctr-drbg" and not family.startswith("AES-"):
                            excluded[family + " (TDEA)"] += 1
                            continue
                        alg = int(family[4:7]) // 64 - 2 if key == "ctr-drbg" else HASHES[family]
                        df = int("use df" in family)
                        query = request(key, alg, df, pr, reseed, options["ReturnedBitsLen"], value(fields, "entropyinput"),
                            value(fields, "nonce"), value(fields, "personalizationstring"), value(fields, "entropyinputreseed"),
                            value(fields, "additionalinputreseed"), value(fields, "entropyinputpr"), value(fields, "additionalinput"),
                            value(fields, "entropyinputpr", index=1), value(fields, "additionalinput", index=1))
                        rows.append(case(f"{family} / {len(rows)} / COUNT {value(fields, 'count')}", query, value(fields, "returnedbits")))
                    packet(key, "drbgtestvectors.zip", nested + "/" + name + ".rsp", rows, excluded)

    archives = ["CounterMode", "FeedbackModenocounter", "FeedbackModewzeroiv", "FeedbackModeNOzeroiv", "PipelineModeWOCounter", "PipelineModewithCounter"]
    for key, prefix in [("kdf-hmac", "HMAC_"), ("kdf-cmac", "CMAC_AES")]:
        begin(key, "KBKDFVS " + ("HMAC" if key == "kdf-hmac" else "AES-CMAC"),
              "Counter, feedback and double-pipeline; counter before fixed data and after iteration data; counterless variants included", "key-derivation")
        if key not in selected:
            continue
        for index, name in enumerate(archives):
            mode = 0 if index == 0 else 1 if index < 4 else 2
            with zipfile.ZipFile(io.BytesIO(source(name + ".zip"))) as archive:
                member = next(name for name in archive.namelist() if name.endswith(".rsp"))
                rows, excluded = [], Counter()
                for options, fields in records(archive.read(member).decode("ascii")):
                    family = options["PRF"]
                    location = options.get("CTRLOCATION", "NONE")
                    if not family.startswith(prefix):
                        excluded[family] += 1
                        continue
                    if location not in ("NONE", "BEFORE_FIXED" if mode == 0 else "AFTER_ITER"):
                        excluded["Counter location " + location] += 1
                        continue
                    alg = HASHES[family[5:]] if key == "kdf-hmac" else int(family[8:]) // 64 - 2
                    width = int(options.get("RLEN", "0_BITS").split("_")[0]) // 8
                    bits = int(value(fields, "l"))
                    if bits % 8:
                        excluded["Non-byte output length"] += 1
                        continue
                    rows.append(case(f"{family} / {location} / r={width} / {len(rows)} / COUNT {value(fields, 'count')}",
                        request(key, alg, mode, width, value(fields, "ki"), value(fields, "fixedinputdata"), value(fields, "iv"), bits // 8), value(fields, "ko")))
                packet(key, name + ".zip", member, rows, excluded)

    for key, curve in [("ed25519", "ED-25519"), ("ed448", "ED-448"), ("pbkdf", None)]:
        begin(key, "ACVP " + (curve or "PBKDF2"), "Seeded public-key derivation, signing and verification; every published sample case for the matching curve" if curve else
              "All 50 published ACVP PBKDF2 sample cases (HMAC-SHA-224)", "digital-signatures" if curve else "key-derivation")
        if key not in selected:
            continue
        modes = ["KeyGen", "SigGen", "SigVer"] if curve else ["PBKDF"]
        for mode in modes:
            name = "EDDSA-" + mode + "-1.0" if curve else "PBKDF-1.0"
            prompt_name, expected_name = name + "-prompt.json", name + "-expectedResults.json"
            prompt = json.loads(source(prompt_name))
            expected = {group["tgId"]: group for group in json.loads(source(expected_name))["testGroups"]}
            internal_name = name + "-internalProjection.json"
            internal = {group["tgId"]: group for group in json.loads(source(internal_name))["testGroups"]} if mode == "SigGen" else {}
            rows = []
            for group in prompt["testGroups"]:
                if curve and group["curve"] != curve:
                    continue
                answers = {test["tcId"]: test for test in expected[group["tgId"]]["tests"]}
                for test in group["tests"]:
                    answer = answers.pop(test["tcId"])
                    ph, context = int(group.get("preHash", False)), test.get("context", "")
                    if mode == "KeyGen":
                        query, want = request(key, "key", answer["d"]), answer["q"]
                    elif mode == "SigGen":
                        query, want = request(key, "sign", ph, internal[group["tgId"]]["d"], test["message"], context), answer["signature"]
                    elif mode == "SigVer":
                        query, want = request(key, "verify", ph, test["q"], test["message"], context, test["signature"]), str(answer["testPassed"]).lower()
                    else:
                        if test["keyLen"] % 8:
                            raise ValueError("PBKDF non-byte key length")
                        query, want = request("pbkdf", HASHES[group["hmacAlg"]], test["password"].encode("utf-8").hex(), test["salt"],
                                              test["iterationCount"], test["keyLen"] // 8), answer["derivedKey"]
                    rows.append(case(f"tgId {group['tgId']} / tcId {test['tcId']}", query, want))
                if answers:
                    raise ValueError("Unmatched ACVP expected results")
            packet(key, prompt_name, name + "/prompt.json", rows,
                   extra_sources=[expected_name] + ([internal_name] if mode == "SigGen" else []))

    if set(sets) != selected or any(not entry["count"] for entry in sets.values()):
        raise ValueError("Unknown or empty NIST suite")
    (directory / "manifest.json").write_text(json.dumps({"sets": sets}, indent=2) + "\n")
    return sets
