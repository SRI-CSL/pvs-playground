#include "utf8_decoder_c.h"
#include "../cavp_driver.h"

#include <errno.h>

static uint8_t *read_binary_file(const char *path, size_t *length) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "FAIL open %s: %s\n", path, strerror(errno));
    exit(2);
  }
  if (fseek(file, 0, SEEK_END) != 0) {
    fprintf(stderr, "FAIL seek %s\n", path);
    exit(2);
  }
  long end = ftell(file);
  if (end < 0) {
    fprintf(stderr, "FAIL tell %s\n", path);
    exit(2);
  }
  rewind(file);
  uint8_t *data = malloc((size_t)end == 0 ? 1 : (size_t)end);
  if (data == NULL) {
    fprintf(stderr, "FAIL allocate %ld bytes\n", end);
    exit(2);
  }
  size_t got = fread(data, 1, (size_t)end, file);
  fclose(file);
  if (got != (size_t)end) {
    fprintf(stderr, "FAIL read %s\n", path);
    exit(2);
  }
  *length = got;
  return data;
}

static void write_bytestring_file(const char *path, bytestrings__bytestring_t value) {
  FILE *file = fopen(path, "wb");
  if (file == NULL) {
    fprintf(stderr, "FAIL create %s: %s\n", path, strerror(errno));
    exit(2);
  }
  if (value->length > 0 &&
      fwrite(value->seq->elems, 1, value->length, file) != value->length) {
    fprintf(stderr, "FAIL write %s\n", path);
    exit(2);
  }
  fclose(file);
}

static int files_equal(const char *left, const char *right) {
  size_t left_len = 0;
  size_t right_len = 0;
  uint8_t *left_data = read_binary_file(left, &left_len);
  uint8_t *right_data = read_binary_file(right, &right_len);
  int ok = left_len == right_len && memcmp(left_data, right_data, left_len) == 0;
  free(left_data);
  free(right_data);
  return ok;
}

static int compare_artifact(const char *name, const char *actual, const char *expected) {
  int ok = files_equal(actual, expected);
  printf("%s utf8tests %s artifact\n", ok ? "PASS" : "FAIL", name);
  if (!ok) {
    printf("  expected %s\n  actual   %s\n", expected, actual);
  }
  return ok ? 0 : 1;
}

int main(void) {
  const char *input_path = "utf8tests/utf8tests.bin";
  const char *skip_path = "build/utf8.skip.pvs2c.txt";
  const char *replace_path = "build/utf8.replace.pvs2c.txt";
  const char *skip_ref_path = "utf8tests/artifacts/utf8.skip.ref.txt";
  const char *replace_ref_path = "utf8tests/artifacts/utf8.replace.ref.txt";

  size_t input_len = 0;
  uint8_t *input = read_binary_file(input_path, &input_len);
  if (input_len > UINT32_MAX) {
    fprintf(stderr, "FAIL input too large for PVS bytestring\n");
    free(input);
    return 2;
  }

  bytestrings__bytestring_t skip =
      utf8_decoder__sanitize_skip(cavp_make_bytestring(input, (uint32_t)input_len));
  bytestrings__bytestring_t replace =
      utf8_decoder__sanitize_replace(cavp_make_bytestring(input, (uint32_t)input_len));
  free(input);

  write_bytestring_file(skip_path, skip);
  write_bytestring_file(replace_path, replace);
  release_bytestrings__bytestring(skip);
  release_bytestrings__bytestring(replace);

  int failures = 0;
  failures += compare_artifact("skip", skip_path, skip_ref_path);
  failures += compare_artifact("replace", replace_path, replace_ref_path);
  return failures == 0 ? 0 : 1;
}
