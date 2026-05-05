#include "SHA256_c.h"
#include "../cavp_driver.h"

#define CAVP_LINE_BUFFER 131072
#define CAVP_HEX_BUFFER 131072

static bytestrings__bytestring_t sha_hex_literal_to_bytestring(const char *hex) {
  return SHA256__hex2bytestring(cavp_make_ascii_bytestring(hex));
}

static int expect_hex_result(const char *name,
                             const char *call,
                             bytestrings__bytestring_t actual_hex,
                             const char *expected_hex) {
  int ok = cavp_hex_matches(actual_hex, expected_hex);
  printf("%s %s(%s)\n", ok ? "PASS" : "FAIL", call, name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_hex);
    cavp_print_ascii_bytestring(actual_hex);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
  return ok ? 0 : 1;
}

static int expect_sha256(const char *name, const char *message, const char *expected_hex) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(SHA256__sha256message(cavp_make_ascii_bytestring(message)));
  return expect_hex_result(name, "sha256", actual_hex, expected_hex);
}

static int expect_hexsha256(const char *name, const char *hex_message, const char *expected_hex) {
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(SHA256__hexsha256message(cavp_make_ascii_bytestring(hex_message)));
  return expect_hex_result(name, "hexsha256", actual_hex, expected_hex);
}

static void run_nist_sha256_case(cavp_counts_t *counts,
                                 const char *path,
                                 unsigned len_bits,
                                 const char *message,
                                 const char *expected_md) {
  if (len_bits % 8 != 0) {
    counts->skipped++;
    printf("SKIP NIST SHA-256 %s Len=%u: not byte-oriented\n", cavp_basename(path), len_bits);
    return;
  }
  size_t byte_len = len_bits / 8;
  if (!cavp_sha256_length_admissible(byte_len)) {
    counts->skipped++;
    printf("SKIP NIST SHA-256 %s Len=%u bytes=%zu bytes_mod64=%zu: outside demo padding domain\n",
           cavp_basename(path), len_bits, byte_len, byte_len % 64);
    return;
  }

  char message_bytes[CAVP_HEX_BUFFER];
  cavp_copy_hex_bytes(message_bytes, sizeof(message_bytes), message, byte_len);
  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(SHA256__sha256message(sha_hex_literal_to_bytestring(message_bytes)));
  int ok = cavp_hex_matches(actual_hex, expected_md);
  if (ok) {
    counts->passed++;
  } else {
    counts->failed++;
    printf("FAIL NIST SHA-256 %s Len=%u\n", cavp_basename(path), len_bits);
    printf("  expected %s\n  actual   ", expected_md);
    cavp_print_ascii_bytestring(actual_hex);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
}

static void run_nist_sha256_file(cavp_counts_t *counts, const char *path) {
  FILE *file = NULL;
  if (!cavp_open_or_fail(path, &file, counts)) {
    return;
  }

  char line[CAVP_LINE_BUFFER];
  char message[CAVP_HEX_BUFFER] = "";
  unsigned len_bits = 0;
  int have_len = 0;
  int have_message = 0;
  unsigned before = counts->passed + counts->failed + counts->skipped;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *text = cavp_trim(line);
    if (*text == '\0' || *text == '#' || *text == '[') {
      continue;
    }

    char *field = NULL;
    char *value = NULL;
    if (!cavp_assignment(text, &field, &value)) {
      continue;
    }
    if (strcmp(field, "Len") == 0) {
      len_bits = (unsigned)strtoul(value, NULL, 10);
      message[0] = '\0';
      have_len = 1;
      have_message = 0;
    } else if (strcmp(field, "Msg") == 0) {
      cavp_copy_value(message, sizeof(message), value);
      have_message = 1;
    } else if (strcmp(field, "MD") == 0 && have_len && have_message) {
      run_nist_sha256_case(counts, path, len_bits, message, value);
      have_len = 0;
      have_message = 0;
      message[0] = '\0';
    }
  }
  fclose(file);

  if (before == counts->passed + counts->failed + counts->skipped) {
    printf("FAIL NIST SHA-256 %s: no cases parsed\n", cavp_basename(path));
    counts->failed++;
  }
}

static int run_nist_sha256_suite(void) {
  static const char *files[] = {
      "test-vectors/nist/SHA256ShortMsg.rsp",
      "test-vectors/nist/SHA256LongMsg.rsp",
  };
  cavp_counts_t counts = {0, 0, 0};
  for (size_t i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
    run_nist_sha256_file(&counts, files[i]);
  }
  cavp_report_summary("SHA-256 ShortMsg/LongMsg", counts);
  return counts.failed == 0 ? 0 : 1;
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
  failures += run_nist_sha256_suite();
  return failures == 0 ? 0 : 1;
}
