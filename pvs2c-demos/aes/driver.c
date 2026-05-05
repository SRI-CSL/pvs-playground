#include "Rijndael_c.h"
#include "../cavp_driver.h"

#define CAVP_LINE_BUFFER 4096

static bytestrings__bytestring_t hex_literal_to_bytestring(const char *hex) {
  return hex__hex2bytestring(cavp_make_ascii_bytestring(hex));
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

  int cipher_ok = cavp_hex_matches(cipher_hex, expected_cipher_hex);
  int inverse_ok = cavp_hex_matches(plain_hex_actual, plain_hex);
  int ok = cipher_ok && inverse_ok;
  printf("%s aes128(%s)\n", ok ? "PASS" : "FAIL", name);
  if (!cipher_ok) {
    printf("  expected cipher %s\n  actual cipher   ", expected_cipher_hex);
    cavp_print_ascii_bytestring(cipher_hex);
    putchar('\n');
  }
  if (!inverse_ok) {
    printf("  expected inverse %s\n  actual inverse   ", plain_hex);
    cavp_print_ascii_bytestring(plain_hex_actual);
    putchar('\n');
  }
  release_bytestrings__bytestring(cipher_hex);
  release_bytestrings__bytestring(plain_hex_actual);
  return ok ? 0 : 1;
}

static int expect_theory_constant(const char *name,
                                  bytestrings__bytestring_t value,
                                  const char *expected_ascii) {
  int ok = cavp_ascii_matches(value, expected_ascii);
  printf("%s %s\n", ok ? "PASS" : "FAIL", name);
  if (!ok) {
    printf("  expected %s\n  actual   ", expected_ascii);
    cavp_print_ascii_bytestring(value);
    putchar('\n');
  }
  return ok ? 0 : 1;
}

static void run_nist_aes_case(cavp_counts_t *counts,
                              const char *path,
                              unsigned count,
                              int encrypt,
                              const char *key,
                              const char *plaintext,
                              const char *ciphertext) {
  bytestrings__bytestring_t actual_hex =
      encrypt ? hex__bytestring2hexstring(Rijndael__RijndaelB(hex_literal_to_bytestring(plaintext),
                                                              hex_literal_to_bytestring(key)))
              : hex__bytestring2hexstring(Rijndael__invRijndaelB(hex_literal_to_bytestring(ciphertext),
                                                                 hex_literal_to_bytestring(key)));
  const char *expected = encrypt ? ciphertext : plaintext;
  int ok = cavp_hex_matches(actual_hex, expected);
  if (ok) {
    counts->passed++;
  } else {
    counts->failed++;
    printf("FAIL NIST AES %s %s COUNT=%u\n",
           cavp_basename(path), encrypt ? "ENCRYPT" : "DECRYPT", count);
    printf("  expected %s\n  actual   ", expected);
    cavp_print_ascii_bytestring(actual_hex);
    putchar('\n');
  }
  release_bytestrings__bytestring(actual_hex);
}

static void run_nist_aes_file(cavp_counts_t *counts, const char *path) {
  FILE *file = NULL;
  if (!cavp_open_or_fail(path, &file, counts)) {
    return;
  }

  char line[CAVP_LINE_BUFFER];
  char key[65] = "";
  char plaintext[65] = "";
  char ciphertext[65] = "";
  unsigned count = 0;
  int mode = 0;
  unsigned before = counts->passed + counts->failed + counts->skipped;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *text = cavp_trim(line);
    if (*text == '\0' || *text == '#') {
      continue;
    }
    if (strcmp(text, "[ENCRYPT]") == 0) {
      mode = 1;
      key[0] = plaintext[0] = ciphertext[0] = '\0';
      continue;
    }
    if (strcmp(text, "[DECRYPT]") == 0) {
      mode = -1;
      key[0] = plaintext[0] = ciphertext[0] = '\0';
      continue;
    }

    char *field = NULL;
    char *value = NULL;
    if (!cavp_assignment(text, &field, &value)) {
      continue;
    }
    if (strcmp(field, "COUNT") == 0) {
      count = (unsigned)strtoul(value, NULL, 10);
      key[0] = plaintext[0] = ciphertext[0] = '\0';
    } else if (strcmp(field, "KEY") == 0) {
      cavp_copy_value(key, sizeof(key), value);
    } else if (strcmp(field, "PLAINTEXT") == 0) {
      cavp_copy_value(plaintext, sizeof(plaintext), value);
    } else if (strcmp(field, "CIPHERTEXT") == 0) {
      cavp_copy_value(ciphertext, sizeof(ciphertext), value);
    }

    if (mode != 0 && key[0] != '\0' && plaintext[0] != '\0' && ciphertext[0] != '\0') {
      run_nist_aes_case(counts, path, count, mode > 0, key, plaintext, ciphertext);
      key[0] = plaintext[0] = ciphertext[0] = '\0';
    }
  }
  fclose(file);

  if (before == counts->passed + counts->failed + counts->skipped) {
    printf("FAIL NIST AES %s: no cases parsed\n", cavp_basename(path));
    counts->failed++;
  }
}

static int run_nist_aes_suite(void) {
  static const char *files[] = {
      "test-vectors/nist/ECBGFSbox128.rsp",
      "test-vectors/nist/ECBKeySbox128.rsp",
      "test-vectors/nist/ECBVarKey128.rsp",
      "test-vectors/nist/ECBVarTxt128.rsp",
  };
  cavp_counts_t counts = {0, 0, 0};
  for (size_t i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
    run_nist_aes_file(&counts, files[i]);
  }
  cavp_report_summary("AES-128 ECB KAT", counts);
  return counts.failed == 0 ? 0 : 1;
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
  failures += run_nist_aes_suite();
  return failures == 0 ? 0 : 1;
}
