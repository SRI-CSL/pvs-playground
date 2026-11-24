#include "crypto_random_c.h"
#include "health_tests_c.h"
#include <assert.h>

/* Fixtures for an immutable source snapshot and a separate PRNG snapshot. */
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) {
    static const uint16_t samples[] = {0, 255, 256, UINT16_MAX};
    return stream == UINT64_MAX && i < 4 ? samples[i] : 256;
}
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) {
    return stream == 3 && i == UINT32_MAX ? 42 : 256;
}

int main(void) {
    assert(crypto_random__entropy_sample(UINT64_MAX, 0) == 0);
    assert(crypto_random__entropy_sample(UINT64_MAX, 1) == 255);
    assert(!crypto_random__available(crypto_random__entropy_sample(UINT64_MAX, 2)));
    assert(!crypto_random__available(crypto_random__entropy_sample(UINT64_MAX, 3)));
    assert(crypto_random__sample_byte(crypto_random__prng_sample(3, UINT32_MAX)) == 42);
    assert(!crypto_random__available(crypto_random__prng_sample(4, UINT32_MAX)));

    /* SP 800-90B 4.4.1 gives C=11 for H=2 and alpha=2^-20. */
    health_tests__repetition_t r = health_tests__repetition_start(11);
    for (uint32_t i = 1; i <= 10; ++i) {
        r = health_tests__repetition_step(11, r, 7);
        assert(r->run == i);
    }
    r = health_tests__repetition_step(11, r, 8);
    assert(r->run == 1);
    for (unsigned i = 0; i < 10; ++i) r = health_tests__repetition_step(11, r, 8);
    r = health_tests__repetition_step(11, r, 9);
    assert(r->run == 11);
    release_health_tests__repetition(r);

    /* Two disjoint windows, including a new reference at the boundary. */
    for (unsigned binary = 0; binary <= 1; ++binary) {
        uint16_t w = health_tests__window_size(binary);
        assert(w == (binary ? 1024 : 512));
        health_tests__adaptive_t a = health_tests__adaptive_start(w);
        for (unsigned i = 0; i < w; ++i) a = health_tests__adaptive_step(w, 3, a, i == 0);
        assert(a->used == w && a->matches == 1 && !a->failed);
        for (unsigned i = 1; i <= 3; ++i) {
            a = health_tests__adaptive_step(w, 3, a, 0);
            assert(a->used == i && a->matches == i && a->failed == (i == 3));
        }
        a = health_tests__adaptive_step(w, 3, a, 1);
        assert(a->failed);
        release_health_tests__adaptive(a);
    }
    puts("Random source attachments and both SP 800-90B health tests passed.");
    return 0;
}
