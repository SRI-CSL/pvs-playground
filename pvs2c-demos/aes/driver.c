#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Rijndael_c.h"

static bytestrings__bytestring_t make_bytestring(const uint8_t *data, uint32_t length) {
  bytestrings__bytestring_t text = new_bytestrings__bytestring();
  bytestrings_array_0_t seq = new_bytestrings_array_0(length);
  text->length = length;
  text->seq = seq;
  for (uint32_t i = 0; i < length; i++) {
    seq->elems[i] = data[i];
  }
  return text;
}

static bytestrings__bytestring_t make_ascii_bytestring(const char *text) {
  return make_bytestring((const uint8_t *)text, (uint32_t)strlen(text));
}

static bytestrings__bytestring_t hex_literal_to_bytestring(const char *hex) {
  return hex__hex2bytestring(make_ascii_bytestring(hex));
}

static void print_ascii_bytestring(bytestrings__bytestring_t value) {
  for (uint32_t i = 0; i < value->length; i++) {
    putchar((char)value->seq->elems[i]);
  }
}

static int bytestring_matches_ascii(bytestrings__bytestring_t value, const char *expected) {
  size_t expected_len = strlen(expected);
  if (value->length != expected_len) {
    return 0;
  }
  for (uint32_t i = 0; i < value->length; i++) {
    if (value->seq->elems[i] != (uint8_t)expected[i]) {
      return 0;
    }
  }
  return 1;
}

static int expect_encrypt_decrypt(const char *name,
                                  const char *plain_hex,
                                  const char *key_hex,
                                  const char *expected_cipher_hex) {
  bytestrings__bytestring_t cipher_hex =
      hex__bytestring2hexstring(Rijndael__RijndaelB(hex_literal_to_bytestring(plain_hex),
                                                    hex_literal_to_bytestring(key_hex)));
  bytestrings__bytestring_t plain_hex_actual =
      hex__bytestring2hexstring(Rijndael__invRijndaelB(hex_literal_to_bytestring(expected_cipher_hex),
                                                       hex_literal_to_bytestring(key_hex)));

  int cipher_ok = bytestring_matches_ascii(cipher_hex, expected_cipher_hex);
  int inverse_ok = bytestring_matches_ascii(plain_hex_actual, plain_hex);
  int ok = cipher_ok && inverse_ok;
  printf("%s aes128(%s)\n", ok ? "PASS" : "FAIL", name);
  if (!cipher_ok) {
    printf("  expected cipher %s\n  actual cipher   ", expected_cipher_hex);
    print_ascii_bytestring(cipher_hex);
    putchar('\n');
  }
  if (!inverse_ok) {
    printf("  expected inverse %s\n  actual inverse   ", plain_hex);
    print_ascii_bytestring(plain_hex_actual);
    putchar('\n');
  }
  release_bytestrings__bytestring(cipher_hex);
  release_bytestrings__bytestring(plain_hex_actual);
  return ok ? 0 : 1;
}

static int expect_theory_constant(const char *name,
                                  bytestrings__bytestring_t value,
                                  const char *expected_ascii) {
  int ok = bytestring_matches_ascii(value, expected_ascii);
  printf("%s %s\n", ok ? "PASS" : "FAIL", name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_ascii);
    print_ascii_bytestring(value);
    putchar('\n');
  }
  return ok ? 0 : 1;
}

int main(void) {
  int failures = 0;
  failures += expect_theory_constant("Rijndael__testRijndael1",
                                     Rijndael__testRijndael1(),
                                     "3925841D02DC09FBDC118597196A0B32");
  failures += expect_theory_constant("Rijndael__testInvRijndael1",
                                     Rijndael__testInvRijndael1(),
                                     "3243F6A8885A308D313198A2E0370734");
  failures += expect_encrypt_decrypt("aes-spec-vector",
                                     "3243F6A8885A308D313198A2E0370734",
                                     "2B7E151628AED2A6ABF7158809CF4F3C",
                                     "3925841D02DC09FBDC118597196A0B32");
  failures += expect_encrypt_decrypt("fips-197-vector",
                                     "00112233445566778899AABBCCDDEEFF",
                                     "000102030405060708090A0B0C0D0E0F",
                                     "69C4E0D86A7B0430D8CDB78070B4C55A");
  return failures == 0 ? 0 : 1;
}
