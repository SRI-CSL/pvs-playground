#include "ed25519_random_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* RFC 8032 section 7.1, test 1, delivered by a fixed test provider. */
static const uint8_t seed[] = {
    0x9d,0x61,0xb1,0x9d,0xef,0xfd,0x5a,0x60,0xba,0x84,0x4a,0xf4,0x92,0xec,0x2c,0xc4,
    0x44,0x49,0xc5,0x69,0x7b,0x32,0x69,0x19,0x70,0x3b,0xac,0x03,0x1c,0xae,0x7f,0x60
};
static const uint8_t public_key[] = {
    0xd7,0x5a,0x98,0x01,0x82,0xb1,0x0a,0xb7,0xd5,0x4b,0xfe,0xd3,0xc9,0x64,0x07,0x3a,
    0x0e,0xe1,0x72,0xf3,0xda,0xa6,0x23,0x25,0xaf,0x02,0x1a,0x68,0xf7,0x07,0x51,0x1a
};
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) {
    if (stream == 1 && i < sizeof(seed)) return seed[i];
    if (stream == 2 && i < 17) return seed[i];
    return 256;
}

int main(void) {
    ed25519_random__keys_t good = ed25519_random__generate_keys(1);
    assert(good->ok && !memcmp(good->private_seed->seq->elems, seed, sizeof(seed)));
    assert(!memcmp(good->verification_key->seq->elems, public_key, sizeof(public_key)));
    release_ed25519_random__keys(good);
    for (uint64_t stream = 2; stream <= 3; ++stream) {
        ed25519_random__keys_t bad = ed25519_random__generate_keys(stream);
        assert(!bad->ok);
        for (unsigned i = 0; i < 32; ++i)
            assert(!bad->private_seed->seq->elems[i] && !bad->verification_key->seq->elems[i]);
        release_ed25519_random__keys(bad);
    }
    puts("Ed25519 key acquisition, derivation and two provider-failure cases passed.");
    return 0;
}
