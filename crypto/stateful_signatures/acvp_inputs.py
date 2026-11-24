"""Convert the two NIST LMS sigVer internalProjection.json files to test rows."""
import json
import sys

for path in sys.argv[1:]:
    with open(path, encoding="utf-8") as source:
        groups = json.load(source)["testGroups"]
    for group in groups:
        for test in group["tests"]:
            print("L", test["tcId"], int(test["testPassed"]), group["publicKey"],
                  test["signature"], test["message"] or "-")
