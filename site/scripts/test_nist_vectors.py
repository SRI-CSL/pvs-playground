"""Parser checks for response-file structure that affects NIST coverage."""
import unittest
from nist_vectors import records, value, request


class ResponseFiles(unittest.TestCase):
    def test_repeated_inputs_and_section_changes(self):
        rows = list(records("""[SHA-256]
[ReturnedBitsLen = 1024]
COUNT = 0
AdditionalInput =
EntropyInputPR = aa
AdditionalInput = bb
EntropyInputPR = cc
ReturnedBits = dd

[SHA-512]
[ReturnedBitsLen = 2048]
COUNT = 0
ReturnedBits = ee
"""))
        self.assertEqual(len(rows), 2)
        options, fields = rows[0]
        self.assertEqual(options["section"], "SHA-256")
        self.assertEqual(value(fields, "additionalinput", index=0), "")
        self.assertEqual(value(fields, "additionalinput", index=1), "bb")
        self.assertEqual(value(fields, "entropyinputpr", index=1), "cc")
        self.assertEqual(rows[1][0]["ReturnedBitsLen"], "2048")
        self.assertEqual(request("hmac", 0, "", "ABCD"), "hmac 0 - abcd")


if __name__ == "__main__":
    unittest.main()
