#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "HMAC_c.h"

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
                             bytestrings__bytestring_t actual_hex,
                             const char *expected_hex) {
  int ok = bytestring_matches_ascii(actual_hex, expected_hex);
  printf("%s %s\n", ok ? "PASS" : "FAIL", name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_hex);
    print_ascii_bytestring(actual_hex);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
  return ok ? 0 : 1;
}

static int expect_hmac(const char *name,
                       bytestrings__bytestring_t key,
                       bytestrings__bytestring_t message,
                       const char *expected_hex) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(HMAC__hmac256(64, key, message));
  char label[96];
  snprintf(label, sizeof(label), "hmac256(%s)", name);
  return expect_hex_result(label, actual_hex, expected_hex);
}

static int expect_static_test1(void) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(copy_bytestrings__bytestring(HMAC__test1()));
  return expect_hex_result("generated HMAC__test1",
                           actual_hex,
                           "F7BC83F430538424B13298E6AA6FB143"
                           "EF4D59A14946175997479DBC2D1A3CD8");
}

int main(void) {
  int failures = 0;
  uint8_t rfc_key[20];
  memset(rfc_key, 0x0b, sizeof(rfc_key));

  failures += expect_static_test1();
  failures += expect_hmac("quick-brown-fox",
                          make_ascii_bytestring("key"),
                          make_ascii_bytestring("The quick brown fox jumps over the lazy dog"),
                          "F7BC83F430538424B13298E6AA6FB143"
                          "EF4D59A14946175997479DBC2D1A3CD8");
  failures += expect_hmac("rfc4231-case-1",
                          make_bytestring(rfc_key, sizeof(rfc_key)),
                          make_ascii_bytestring("Hi There"),
                          "B0344C61D8DB38535CA8AFCEAF0BF12B"
                          "881DC200C9833DA726E9376C2E32CFF7");
  return failures == 0 ? 0 : 1;
}
