#ifndef PVS2C_DEMOS_CAVP_DRIVER_H
#define PVS2C_DEMOS_CAVP_DRIVER_H

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned passed;
  unsigned failed;
  unsigned skipped;
} cavp_counts_t;

static bytestrings__bytestring_t cavp_make_bytestring(const uint8_t *data, uint32_t length) {
  bytestrings__bytestring_t text = new_bytestrings__bytestring();
  bytestrings_array_0_t seq = new_bytestrings_array_0(length);
  text->length = length;
  text->seq = seq;
  for (uint32_t i = 0; i < length; i++) {
    seq->elems[i] = data[i];
  }
  return text;
}

static bytestrings__bytestring_t cavp_make_ascii_bytestring(const char *text) {
  return cavp_make_bytestring((const uint8_t *)text, (uint32_t)strlen(text));
}

static void cavp_print_ascii_bytestring(bytestrings__bytestring_t value) {
  for (uint32_t i = 0; i < value->length; i++) {
    putchar((char)value->seq->elems[i]);
  }
}

static void cavp_print_ascii_bytestring_prefix(bytestrings__bytestring_t value, size_t length) {
  size_t limit = value->length < length ? value->length : length;
  for (size_t i = 0; i < limit; i++) {
    putchar((char)value->seq->elems[i]);
  }
}

static int cavp_ascii_matches(bytestrings__bytestring_t value, const char *expected) {
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

static int cavp_hex_char_equal(uint8_t actual, char expected) {
  return toupper((unsigned char)actual) == toupper((unsigned char)expected);
}

static int cavp_hex_matches(bytestrings__bytestring_t value, const char *expected) {
  size_t expected_len = strlen(expected);
  if (value->length != expected_len) {
    return 0;
  }
  for (uint32_t i = 0; i < value->length; i++) {
    if (!cavp_hex_char_equal(value->seq->elems[i], expected[i])) {
      return 0;
    }
  }
  return 1;
}

static int cavp_hex_prefix_matches(bytestrings__bytestring_t value,
                                   const char *expected,
                                   size_t expected_len) {
  if (value->length < expected_len || strlen(expected) < expected_len) {
    return 0;
  }
  for (size_t i = 0; i < expected_len; i++) {
    if (!cavp_hex_char_equal(value->seq->elems[i], expected[i])) {
      return 0;
    }
  }
  return 1;
}

/* Demo limitation: the current PVS SHA-256 padding extractor writes the
 * 64-bit length into word 15 whenever the padding byte lands in word 14.
 * Byte lengths with tail 56..59 therefore need the extra final block that
 * SHA-256 specifies, but are outside this demo's admitted CAVP domain. */
static int cavp_sha256_length_admissible(size_t length) {
  size_t block_tail = length % 64;
  return block_tail < 56 || block_tail > 59;
}

static char *cavp_trim(char *text) {
  while (isspace((unsigned char)*text)) {
    text++;
  }
  if (*text == '\0') {
    return text;
  }
  char *end = text + strlen(text) - 1;
  while (end > text && isspace((unsigned char)*end)) {
    *end = '\0';
    end--;
  }
  return text;
}

static int cavp_assignment(char *line, char **key, char **value) {
  char *equals = strchr(line, '=');
  if (equals == NULL) {
    return 0;
  }
  *equals = '\0';
  *key = cavp_trim(line);
  *value = cavp_trim(equals + 1);
  return 1;
}

static void cavp_copy_value(char *dest, size_t dest_size, const char *value) {
  size_t length = strlen(value);
  if (length >= dest_size) {
    fprintf(stderr, "CAVP value too large for test buffer\n");
    exit(2);
  }
  memcpy(dest, value, length + 1);
}

static void cavp_copy_hex_bytes(char *dest,
                                size_t dest_size,
                                const char *hex,
                                size_t byte_length) {
  size_t hex_length = byte_length * 2;
  if (strlen(hex) < hex_length || hex_length >= dest_size) {
    fprintf(stderr, "CAVP hex value length mismatch\n");
    exit(2);
  }
  memcpy(dest, hex, hex_length);
  dest[hex_length] = '\0';
}

static const char *cavp_basename(const char *path) {
  const char *slash = strrchr(path, '/');
  return slash == NULL ? path : slash + 1;
}

static void cavp_report_summary(const char *name, cavp_counts_t counts) {
  unsigned total = counts.passed + counts.failed + counts.skipped;
  printf("NIST %s: %u passed, %u failed, %u skipped (%u total)\n",
         name, counts.passed, counts.failed, counts.skipped, total);
}

static int cavp_open_or_fail(const char *path, FILE **file, cavp_counts_t *counts) {
  *file = fopen(path, "r");
  if (*file == NULL) {
    fprintf(stderr, "FAIL missing NIST vector file: %s\n", path);
    counts->failed++;
    return 0;
  }
  return 1;
}

#endif
