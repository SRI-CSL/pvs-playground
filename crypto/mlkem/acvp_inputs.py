"""Print input lines for acvp.c from NIST internalProjection.json files."""
import json
import sys

fields = {
    "keygen": ("d", "z", "ek", "dk"),
    "encapsulation": ("ek", "m", "c", "k"),
    "decapsulation": ("dk", "c", "k"),
    "encapsulationKeyCheck": ("ek", "testPassed"),
    "decapsulationKeyCheck": ("dk", "testPassed"),
}
for path in sys.argv[1:]:
    with open(path, encoding="utf-8") as source:
        groups = json.load(source)["testGroups"]
    for group in groups:
        rank = int(group["parameterSet"].split("-")[-1]) // 256
        operation = group.get("function", "keygen")
        for case in group["tests"]:
            values = [case[key] for key in fields[operation]]
            print(rank, operation, case["tcId"],
                  *(int(v) if isinstance(v, bool) else v for v in values))
