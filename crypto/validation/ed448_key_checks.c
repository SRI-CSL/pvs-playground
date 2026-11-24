#include "ed448_random_c.h"
#include "ed448_examples_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) {
    if ((stream == 1 || (stream == 2 && i < 37)) && i < 57)
        return ed448_examples__pure_seed()->seq->elems[i];
    return 256;
}

int main(void) {
    ed448_random__keys_t keys = ed448_random__generate_keys(1);
    assert(keys->ok);
    assert(!memcmp(keys->private_seed->seq->elems, ed448_examples__pure_seed()->seq->elems, 57));
    assert(!memcmp(keys->verification_key->seq->elems, ed448_examples__pure_vk()->seq->elems, 57));
    release_ed448_random__keys(keys);
    keys = ed448_random__generate_keys(2);
    assert(!keys->ok);
    for (unsigned i = 0; i < 57; ++i)
        assert(!keys->private_seed->seq->elems[i] && !keys->verification_key->seq->elems[i]);
    release_ed448_random__keys(keys);
    puts("Ed448 seed acquisition, key derivation and provider failure passed.");
    return 0;
}
