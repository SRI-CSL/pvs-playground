#include "wasm_i32_c.h"
#include "../../cavp_driver.h"

#include <errno.h>

typedef struct {
  const char *name;
  const char *path;
  unsigned arity;
  uint32_t args[2];
  uint32_t fuel;
  uint32_t expected;
} wasm_case_t;

static int hex_value(int ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  }
  if (ch >= 'a' && ch <= 'f') {
    return ch - 'a' + 10;
  }
  if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  }
  return -1;
}

static uint8_t *read_hex_body(const char *path, uint32_t *length) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "FAIL open %s: %s\n", path, strerror(errno));
    exit(2);
  }

  size_t capacity = 64;
  size_t used = 0;
  uint8_t *bytes = malloc(capacity);
  if (bytes == NULL) {
    fprintf(stderr, "FAIL allocate hex buffer\n");
    exit(2);
  }

  int high = -1;
  int in_comment = 0;
  for (;;) {
    int ch = fgetc(file);
    if (ch == EOF) {
      break;
    }
    if (in_comment) {
      if (ch == '\n') {
        in_comment = 0;
      }
      continue;
    }
    if (ch == '#') {
      in_comment = 1;
      continue;
    }
    if (isspace((unsigned char)ch)) {
      continue;
    }

    int nibble = hex_value(ch);
    if (nibble < 0) {
      fprintf(stderr, "FAIL invalid hex character %c in %s\n", ch, path);
      exit(2);
    }
    if (high < 0) {
      high = nibble;
      continue;
    }
    if (used == capacity) {
      capacity *= 2;
      uint8_t *grown = realloc(bytes, capacity);
      if (grown == NULL) {
        fprintf(stderr, "FAIL grow hex buffer\n");
        exit(2);
      }
      bytes = grown;
    }
    bytes[used++] = (uint8_t)((high << 4) | nibble);
    high = -1;
  }
  fclose(file);

  if (high >= 0) {
    fprintf(stderr, "FAIL odd number of hex digits in %s\n", path);
    exit(2);
  }
  if (used > UINT32_MAX) {
    fprintf(stderr, "FAIL %s too large for PVS bytestring\n", path);
    exit(2);
  }
  *length = (uint32_t)used;
  return bytes;
}

static wasm_i32__exec_result_t run_case_body(const wasm_case_t *test,
                                             const uint8_t *body,
                                             uint32_t length) {
  bytestrings__bytestring_t pvs_body = cavp_make_bytestring(body, length);
  if (test->arity == 1) {
    return wasm_i32__invoke1(pvs_body, test->fuel, test->args[0]);
  }
  if (test->arity == 2) {
    return wasm_i32__invoke2(pvs_body, test->fuel, test->args[0], test->args[1]);
  }
  return wasm_i32__invoke0(pvs_body, test->fuel);
}

static int run_case(const wasm_case_t *test) {
  uint32_t length = 0;
  uint8_t *body = read_hex_body(test->path, &length);
  wasm_i32__exec_result_t result = run_case_body(test, body, length);
  free(body);

  uint8_t halt = wasm_i32__halt_status();
  int ok = result->status == halt && result->value == test->expected;
  printf("%s wasm %s", ok ? "PASS" : "FAIL", test->name);
  if (test->arity == 1) {
    printf("(%u)", test->args[0]);
  } else if (test->arity == 2) {
    printf("(%u, %u)", test->args[0], test->args[1]);
  } else {
    printf("()");
  }
  printf(" => %u\n", result->value);
  if (!ok) {
    printf("  expected status=%u value=%u\n", halt, test->expected);
    printf("  actual   status=%u value=%u pc=%u stack=%u\n",
           result->status,
           result->value,
           result->final_pc,
           result->final_stack_height);
  }
  release_wasm_i32__exec_result(result);
  return ok ? 0 : 1;
}

int main(void) {
  static const wasm_case_t cases[] = {
      {"add", "examples/add.body.hex", 2, {40, 2}, 32, 42},
      {"affine", "examples/affine.body.hex", 2, {5, 9}, 64, 73},
      {"factorial", "examples/factorial.body.hex", 1, {0, 0}, 128, 1},
      {"factorial", "examples/factorial.body.hex", 1, {5, 0}, 512, 120},
  };

  int failures = 0;
  for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
    failures += run_case(&cases[i]);
  }
  return failures == 0 ? 0 : 1;
}
