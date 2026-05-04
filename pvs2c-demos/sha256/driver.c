#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "SHA256_c.h"

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

static int expect_hex_result(const char *name,
                             const char *call,
                             bytestrings__bytestring_t actual_hex,
                             const char *expected_hex) {
  int ok = bytestring_matches_ascii(actual_hex, expected_hex);
  printf("%s %s(%s)\n", ok ? "PASS" : "FAIL", call, name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_hex);
    print_ascii_bytestring(actual_hex);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
  return ok ? 0 : 1;
}

static int expect_sha256(const char *name, const char *message, const char *expected_hex) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(SHA256__sha256message(make_ascii_bytestring(message)));
  return expect_hex_result(name, "sha256", actual_hex, expected_hex);
}

static int expect_hexsha256(const char *name, const char *hex_message, const char *expected_hex) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(SHA256__hexsha256message(make_ascii_bytestring(hex_message)));
  return expect_hex_result(name, "hexsha256", actual_hex, expected_hex);
}

int main(void) {
  int failures = 0;
  failures += expect_sha256("empty", "",
                            "E3B0C44298FC1C149AFBF4C8996FB924"
                            "27AE41E4649B934CA495991B7852B855");
  failures += expect_sha256("abc", "abc",
                            "BA7816BF8F01CFEA414140DE5DAE2223"
                            "B00361A396177A9CB410FF61F20015AD");
  failures += expect_sha256("quick-brown-fox",
                            "The quick brown fox jumps over the lazy dog",
                            "D7A8FBB307D7809469CA9ABCB0082E4F"
                            "8D5651E46D3CDB762D02D0BF37C9E592");
  failures += expect_hexsha256("hex-abc", "616263",
                               "BA7816BF8F01CFEA414140DE5DAE2223"
                               "B00361A396177A9CB410FF61F20015AD");
  return failures == 0 ? 0 : 1;
}
