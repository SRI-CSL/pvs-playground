#ifndef CRYPTO_STATISTICS_MATH_H
#define CRYPTO_STATISTICS_MATH_H
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
_Static_assert(sizeof(double) == sizeof(uint64_t) && DBL_MANT_DIG == 53 &&
               DBL_MAX_EXP == 1024 && FLT_RADIX == 2, "binary64 required");
static inline double crypto_double(uint64_t x) {
    double value;
    memcpy(&value, &x, sizeof(value));
    return value;
}
static inline uint64_t crypto_fp(double value) {
    uint64_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}
extern double crypto_beta_i(double a, double b, double x);
extern double crypto_gamma_q(double a, double x);
#endif
