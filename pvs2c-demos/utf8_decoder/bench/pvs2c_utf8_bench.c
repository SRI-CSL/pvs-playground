#include "utf8_decoder_c.h"
#include "../../cavp_driver.h"
#include "utf8bench_cases.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef bytestrings__bytestring_t (*sanitize_fn_t)(bytestrings__bytestring_t);

static volatile uint64_t bench_sink = 0;

static uint64_t now_ns(void) {
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    perror("clock_gettime");
    exit(2);
  }
  return ((uint64_t)ts.tv_sec * 1000000000ull) + (uint64_t)ts.tv_nsec;
}

static int bytestring_equal(bytestrings__bytestring_t value,
                            const uint8_t *expected,
                            size_t expected_len) {
  if (value->length != expected_len) {
    return 0;
  }
  return expected_len == 0 ||
         memcmp(value->seq->elems, expected, expected_len) == 0;
}

static void sort_doubles(double *values, size_t length) {
  for (size_t i = 1; i < length; i++) {
    double value = values[i];
    size_t j = i;
    while (j > 0 && values[j - 1] > value) {
      values[j] = values[j - 1];
      j--;
    }
    values[j] = value;
  }
}

static double median_sample(double *samples, size_t trials) {
  sort_doubles(samples, trials);
  return samples[trials / 2];
}

static void warmup_case(const bench_case_t *tc,
                        sanitize_fn_t sanitize,
                        bytestrings__bytestring_t input,
                        uint32_t iterations) {
  uint32_t warmups = iterations < 64 ? iterations : 64;
  for (uint32_t i = 0; i < warmups; i++) {
    input->count++;
    bytestrings__bytestring_t out = sanitize(input);
    bench_sink += out->length;
    release_bytestrings__bytestring(out);
  }
  bench_sink += tc->input_len;
}

static double time_case(const bench_case_t *tc,
                        sanitize_fn_t sanitize,
                        bytestrings__bytestring_t input,
                        uint32_t iterations,
                        uint32_t trials) {
  double *samples = calloc(trials, sizeof(double));
  if (samples == NULL) {
    fprintf(stderr, "failed to allocate timing samples\n");
    exit(2);
  }

  for (uint32_t trial = 0; trial < trials; trial++) {
    uint64_t start = now_ns();
    for (uint32_t i = 0; i < iterations; i++) {
      input->count++;
      bytestrings__bytestring_t out = sanitize(input);
      bench_sink += out->length;
      release_bytestrings__bytestring(out);
    }
    uint64_t end = now_ns();
    samples[trial] = (double)(end - start) / (double)iterations;
  }

  double median = median_sample(samples, trials);
  free(samples);
  return median;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s replace|skip iterations trials\n", argv[0]);
    return 2;
  }

  const char *mode = argv[1];
  uint32_t iterations = (uint32_t)strtoul(argv[2], NULL, 10);
  uint32_t trials = (uint32_t)strtoul(argv[3], NULL, 10);
  if (iterations == 0 || trials == 0) {
    fprintf(stderr, "iterations and trials must be positive\n");
    return 2;
  }

  sanitize_fn_t sanitize = NULL;
  if (strcmp(mode, "replace") == 0) {
    sanitize = utf8_decoder__sanitize_replace;
  } else if (strcmp(mode, "skip") == 0) {
    sanitize = utf8_decoder__sanitize_skip;
  } else {
    fprintf(stderr, "unknown mode: %s\n", mode);
    return 2;
  }

  printf("implementation,mode,case,valid,input_bytes,expected_bytes,ns_per_op,ok\n");
  for (size_t i = 0; i < bench_case_count; i++) {
    const bench_case_t *tc = &bench_cases[i];
    const uint8_t *expected =
        strcmp(mode, "replace") == 0 ? tc->replace : tc->skip;
    size_t expected_len =
        strcmp(mode, "replace") == 0 ? tc->replace_len : tc->skip_len;

    bytestrings__bytestring_t input =
        cavp_make_bytestring(tc->input, (uint32_t)tc->input_len);

    input->count++;
    bytestrings__bytestring_t verify = sanitize(input);
    int ok = bytestring_equal(verify, expected, expected_len);
    release_bytestrings__bytestring(verify);

    warmup_case(tc, sanitize, input, iterations);
    double ns_per_op = time_case(tc, sanitize, input, iterations, trials);

    release_bytestrings__bytestring(input);

    printf("PVS2C,%s,%s,%u,%zu,%zu,%.2f,%s\n",
           mode,
           tc->number,
           tc->valid ? 1u : 0u,
           tc->input_len,
           expected_len,
           ns_per_op,
           ok ? "yes" : "no");
  }

  if (bench_sink == UINT64_MAX) {
    fprintf(stderr, "unreachable sink value: %" PRIu64 "\n", bench_sink);
  }
  return 0;
}
