/* FIPS 186-5 key derivation from published ACVP factors and A.1.3 random draws. */
#include "rsa_keygen_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef rsa_keygen_record_1_t bytes;
static bytes samples;
static uint32_t consumed;
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t index) {
    if (stream != 1 || !samples || index >= samples->length) return 256;
    assert(index == consumed++);
    return samples->seq->elems[index];
}
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t index) {
    (void)stream;
    (void)index;
    return 256;
}
static bytes field(void) {
    int a = getchar(), b = getchar();
    assert(a >= 0 && b >= 0);
    unsigned n = (unsigned)a * 256 + (unsigned)b;
    bytes out = new_rsa_keygen_record_1();
    out->length = n;
    out->seq = new_rsa_keygen_array_0(n);
    assert(fread(out->seq->elems, 1, n, stdin) == n);
    return out;
}
static bool same(bytes a, bytes b) {
    return a->length == b->length && memcmp(a->seq->elems, b->seq->elems, b->length) == 0;
}
static bytes keep(bytes b) { ++b->count; return b; }
static rsa_keygen_record_4_t words(bytes b) {
    return (rsa_keygen_record_4_t)crypto_limbs__from_bytes(b->length / 4,
            (crypto_limbs_record_4_t)keep(b), true);
}
static rsa_primes_record_3_t small(uint32_t value) {
    rsa_primes_record_3_t n = (rsa_primes_record_3_t)crypto_limbs__zero_words(1);
    n->word->elems[0] = value;
    return n;
}
static bool check(rsa_keygen__key_t k, bytes fields[]) {
    bool ok = k->ok && same(k->e, fields[0]) && same(k->p, fields[1]) && same(k->q, fields[2])
        && same(k->n, fields[3]) && same(k->d, fields[4]) && same(k->dp, fields[5])
        && same(k->dq, fields[6]) && same(k->qinv, fields[7]);
    release_rsa_keygen__key(k);
    return ok;
}
int main(void) {
    /* 2047 is a base-2 strong pseudoprime, and base 3 detects it. */
    unsigned total = 4, good = 0;
    good += rsa_primes__miller_rabin_pass(small(2047), small(2));
    good += !rsa_primes__miller_rabin_pass(small(2047), small(3));
    good += !rsa_primes__miller_rabin_pass(small(17), small(1));
    good += !rsa_primes__trial_div(small(2047), 0);
    int id;
    while ((id = getchar()) != EOF) {
        int profile = getchar(), run = getchar(), strong = getchar(), pr = getchar(), qr = getchar();
        bytes f[9];
        for (int j = 0; j < 9; ++j) f[j] = field();
        bool ok = check(rsa_keygen__derive_from_factors(profile, keep(f[0]), words(f[1]), words(f[2])), f);
        ++total; good += ok;
        if (!ok) fprintf(stderr, "RSA derivation failed for ACVP case %d\n", id);
        if (run) {
            samples = f[8];
            consumed = 0;
            ok = check(rsa_keygen__generate(profile, keep(f[0]), pr, qr, strong, 1), f)
                 && consumed == samples->length;
            ++total; good += ok;
            if (!ok) fprintf(stderr, "RSA probable-prime generation failed for case %d\n", id);
        }
        if (id == 1) {
            rsa_keygen__key_t missing = rsa_keygen__generate(profile, keep(f[0]), pr, qr, strong, 0);
            rsa_keygen__key_t overflow = rsa_keygen__generate_at(profile, keep(f[0]), pr, qr, strong, 1, UINT32_MAX);
            rsa_keygen__key_t equal = rsa_keygen__derive_from_factors(profile, keep(f[0]), words(f[1]), words(f[1]));
            good += !missing->ok && missing->n->length == 0;
            good += !overflow->ok && overflow->p->length == 0;
            good += !equal->ok && equal->d->length == 0;
            total += 3;
            release_rsa_keygen__key(missing);
            release_rsa_keygen__key(overflow);
            release_rsa_keygen__key(equal);
        }
        samples = NULL;
        for (int j = 0; j < 9; ++j) release_rsa_keygen_record_1(f[j]);
    }
    printf("RSA key generation: %u of %u checks passed\n", good, total);
    return good == total && total ? 0 : 1;
}
