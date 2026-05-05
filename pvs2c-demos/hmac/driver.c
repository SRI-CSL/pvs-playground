#include "HMAC_c.h"
#include "../cavp_driver.h"

#define CAVP_LINE_BUFFER 131072
#define CAVP_HEX_BUFFER 131072

static bytestrings__bytestring_t sha_hex_literal_to_bytestring(const char *hex) {
  return SHA256__hex2bytestring(cavp_make_ascii_bytestring(hex));
}

static int expect_hex_result(const char *name,
                             bytestrings__bytestring_t actual_hex,
                             const char *expected_hex) {
  int ok = cavp_hex_matches(actual_hex, expected_hex);
  printf("%s %s\n", ok ? "PASS" : "FAIL", name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_hex);
    cavp_print_ascii_bytestring(actual_hex);
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

static void run_nist_hmac_case(cavp_counts_t *counts,
                               const char *path,
                               unsigned count,
                               unsigned klen,
                               unsigned tlen,
                               const char *key,
                               const char *message,
                               const char *mac) {
  size_t message_len = strlen(message) / 2;
  int key_hash_outside_domain = klen > 64 && !cavp_sha256_length_admissible(klen);
  size_t inner_sha_len = 64 + message_len;
  int inner_sha_outside_domain = !cavp_sha256_length_admissible(inner_sha_len);
  if (key_hash_outside_domain || inner_sha_outside_domain) {
    counts->skipped++;
    printf("SKIP NIST HMAC %s COUNT=%u Klen=%u MsgBytes=%zu: %s SHA-256 input outside demo padding domain\n",
           cavp_basename(path),
           count,
           klen,
           message_len,
           key_hash_outside_domain ? "key-hash" : "inner");
    return;
  }

  char key_bytes[CAVP_HEX_BUFFER];
  cavp_copy_hex_bytes(key_bytes, sizeof(key_bytes), key, klen);

  bytestrings__bytestring_t actual_hex =
      SHA256__bytestring2hexstring(HMAC__hmac256(64,
                                                 sha_hex_literal_to_bytestring(key_bytes),
                                                 sha_hex_literal_to_bytestring(message)));
  size_t expected_hex_len = (size_t)tlen * 2;
  int ok = strlen(mac) == expected_hex_len &&
           cavp_hex_prefix_matches(actual_hex, mac, expected_hex_len);
  if (ok) {
    counts->passed++;
  } else {
    counts->failed++;
    printf("FAIL NIST HMAC %s COUNT=%u Klen=%u Tlen=%u\n",
           cavp_basename(path), count, klen, tlen);
    printf("  expected %s\n  actual   ", mac);
    cavp_print_ascii_bytestring_prefix(actual_hex, expected_hex_len);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
}

static void run_nist_hmac_file(cavp_counts_t *counts, const char *path) {
  FILE *file = NULL;
  if (!cavp_open_or_fail(path, &file, counts)) {
    return;
  }

  char line[CAVP_LINE_BUFFER];
  char key[CAVP_HEX_BUFFER] = "";
  char message[CAVP_HEX_BUFFER] = "";
  char mac[129] = "";
  unsigned section_l = 0;
  unsigned count = 0;
  unsigned klen = 0;
  unsigned tlen = 0;
  int have_klen = 0;
  int have_tlen = 0;
  int have_key = 0;
  int have_message = 0;
  int have_mac = 0;
  unsigned before = counts->passed + counts->failed + counts->skipped;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *text = cavp_trim(line);
    if (*text == '\0' || *text == '#') {
      continue;
    }
    if (*text == '[') {
      sscanf(text, "[L=%u]", &section_l);
      key[0] = message[0] = mac[0] = '\0';
      have_klen = have_tlen = 0;
      have_key = have_message = have_mac = 0;
      continue;
    }

    char *field = NULL;
    char *value = NULL;
    if (!cavp_assignment(text, &field, &value)) {
      continue;
    }
    if (strcmp(field, "Count") == 0) {
      count = (unsigned)strtoul(value, NULL, 10);
      key[0] = message[0] = mac[0] = '\0';
      have_klen = have_tlen = 0;
      have_key = have_message = have_mac = 0;
    } else if (section_l == 32 && strcmp(field, "Klen") == 0) {
      klen = (unsigned)strtoul(value, NULL, 10);
      have_klen = 1;
    } else if (section_l == 32 && strcmp(field, "Tlen") == 0) {
      tlen = (unsigned)strtoul(value, NULL, 10);
      have_tlen = 1;
    } else if (section_l == 32 && strcmp(field, "Key") == 0) {
      cavp_copy_value(key, sizeof(key), value);
      have_key = 1;
    } else if (section_l == 32 && strcmp(field, "Msg") == 0) {
      cavp_copy_value(message, sizeof(message), value);
      have_message = 1;
    } else if (section_l == 32 && strcmp(field, "Mac") == 0) {
      cavp_copy_value(mac, sizeof(mac), value);
      have_mac = 1;
    }

    if (section_l == 32 && have_klen && have_tlen &&
        have_key && have_message && have_mac) {
      run_nist_hmac_case(counts, path, count, klen, tlen, key, message, mac);
      key[0] = message[0] = mac[0] = '\0';
      have_klen = have_tlen = 0;
      have_key = have_message = have_mac = 0;
    }
  }
  fclose(file);

  if (before == counts->passed + counts->failed + counts->skipped) {
    printf("FAIL NIST HMAC %s: no SHA-256 cases parsed\n", cavp_basename(path));
    counts->failed++;
  }
}

static int run_nist_hmac_suite(void) {
  cavp_counts_t counts = {0, 0, 0};
  run_nist_hmac_file(&counts, "test-vectors/nist/HMAC.rsp");
  cavp_report_summary("HMAC SHA-256", counts);
  return counts.failed == 0 ? 0 : 1;
}

int main(void) {
  int failures = 0;
  uint8_t rfc_key[20];
  memset(rfc_key, 0x0b, sizeof(rfc_key));

  failures += expect_static_test1();
  failures += expect_hmac("quick-brown-fox",
                          cavp_make_ascii_bytestring("key"),
                          cavp_make_ascii_bytestring("The quick brown fox jumps over the lazy dog"),
                          "F7BC83F430538424B13298E6AA6FB143"
                          "EF4D59A14946175997479DBC2D1A3CD8");
  failures += expect_hmac("rfc4231-case-1",
                          cavp_make_bytestring(rfc_key, sizeof(rfc_key)),
                          cavp_make_ascii_bytestring("Hi There"),
                          "B0344C61D8DB38535CA8AFCEAF0BF12B"
                          "881DC200C9833DA726E9376C2E32CFF7");
  failures += run_nist_hmac_suite();
  return failures == 0 ? 0 : 1;
}
