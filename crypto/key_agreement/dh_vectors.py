"""Extract one passing SHA-256 KASVS case per scheme, family and participant role."""
import argparse
import gzip
import re
import sys
from pathlib import Path
from zipfile import ZipFile

SCHEMES = {
    "FFC": ["Hybrid1", "Ephem", "HybridOneFlow", "OneFlow", "Static", "MQV2", "MQV1"],
    "ECC": ["FullUnified", "EphemeralUnified", "OnePassUnified", "OnePassDH",
            "StaticUnified", "FullMQV", "OnePassMQV"],
}


def cases(family, filename):
    with ZipFile(filename) as archive:
        for scheme, name in enumerate(SCHEMES[family]):
            for role, party_u in (("init", 1), ("resp", 0)):
                suffix = f"_{family}{name}_KDFConcat_NOKC_{role}.fax"
                entry = next(path for path in archive.namelist() if path.endswith(suffix))
                text = archive.read(entry).decode("ascii").replace("\r", "")
                group = "EC" if family == "ECC" else "FC"
                # EC selects the P-256 group in the 2016 projection.
                section = text.split(f"\n[{group} - SHA256]", 1)[1].split("\n[", 1)[0]
                header, *records = re.split(r"(?m)^COUNT = \d+\n", section)
                for row in records:
                    data = dict(re.findall(r"(?m)^(\w+) = ([^\n]*)", row))
                    if data["Result"].startswith("P"):
                        break
                else:
                    raise ValueError(f"No passing case in {entry}")
                if family == "FFC":
                    domain = dict(re.findall(r"(?m)^([PQG]) = (\w+)", header))
                    add = [domain[k] for k in ("P","Q","G")]
                    keys = ["XstatIUT","XephemIUT","YstatCAVS","YephemCAVS"]
                else:
                    add = []
                    keys = ["dsIUT","deIUT","QsCAVSx","QsCAVSy","QeCAVSx","QeCAVSy"]
                yield " ".join([family,str(scheme),str(party_u),*add,
                                *[data.get(k,"00") for k in keys],data["Z"],data["OI"],data["DKM"]])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("ffc", type=Path)
    parser.add_argument("ecc", type=Path)
    args = parser.parse_args()
    rows = [*cases("FFC",args.ffc), *cases("ECC",args.ecc)]
    sys.stdout.buffer.write(gzip.compress(("\n".join(rows)+"\n").encode(),mtime=0))
