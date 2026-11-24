/* SP 800-38A Appendix F, first two blocks for AES-128; SP 800-38B AES-CMAC examples. */
#include "aes_modes_c.h"
#include <assert.h>

static aes_modes_array_1_t octets(const char *hex) {
    size_t n = strlen(hex)/2;
    aes_modes_array_1_t a = new_aes_modes_array_1(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned b;
        assert(sscanf(hex+2*i, "%2x", &b) == 1);
        a->elems[i] = (uint8_t)b;
    }
    return a;
}
static aes_modes__mode_key_adt_t key(void) {
    return con_aes_modes__mk128(octets("2b7e151628aed2a6abf7158809cf4f3c"));
}
static void matches(aes_modes_array_1_t actual, const char *hex) {
    aes_modes_array_1_t expected = octets(hex);
    assert(actual->size == expected->size);
    assert(memcmp(actual->elems,expected->elems,expected->size) == 0);
    release_aes_modes_array_1(expected);
}
#define IV "000102030405060708090a0b0c0d0e0f"
#define P1 "6bc1bee22e409f96e93d7e117393172a"
#define P2 "ae2d8a571e03ac9c9eb76fac45af8e51"
#define ZERO "00000000000000000000000000000000"

int main(void) {
    aes_modes_array_1_t b = aes_modes__ecb_encrypt(key(), octets(P1));
    matches(b, "3ad77bb40d7a3660a89ecaf32466ef97");
    b = aes_modes__ecb_decrypt(key(), b);
    matches(b, P1);
    release_aes_modes_array_1(b);
    b = aes_modes__cbc_encrypt(key(), octets(IV), octets(P1));
    matches(b, "7649abac8119b246cee98e9b12e9197d");
    b = aes_modes__cbc_encrypt(key(), b, octets(P2));
    matches(b, "5086cb9b507219ee95db113a917678b2");
    b = aes_modes__cbc_decrypt(key(), octets("7649abac8119b246cee98e9b12e9197d"), b);
    matches(b, P2);
    release_aes_modes_array_1(b);

    aes_modes__feedback_t f = aes_modes__cfb(key(), octets(IV), octets(P1), 128, false);
    matches(f->data, "3b3fd92eb72dad20333449f8e83cfb4a");
    f->next_reg->count++;
    aes_modes__feedback_t g = aes_modes__cfb(key(), f->next_reg, octets(P2), 128, false);
    matches(g->data, "c8a64537a0b3a93fcde3cdad9f1ce58b");
    release_aes_modes__feedback(g);
    f->data->count++;
    g = aes_modes__cfb(key(), octets(IV), f->data, 128, true);
    matches(g->data, P1);
    matches(g->next_reg, "3b3fd92eb72dad20333449f8e83cfb4a");
    release_aes_modes__feedback(f);
    release_aes_modes__feedback(g);
    f = aes_modes__cfb(key(), octets(IV), octets(P1), 8, false);
    matches(f->data, "3b000000000000000000000000000000");
    matches(f->next_reg, "0102030405060708090a0b0c0d0e0f3b");
    release_aes_modes__feedback(f);
    f = aes_modes__ofb(key(), octets(IV), octets(P1), 128);
    matches(f->data, "3b3fd92eb72dad20333449f8e83cfb4a");
    f->next_reg->count++;
    g = aes_modes__ofb(key(), f->next_reg, octets(P2), 128);
    matches(g->data, "7789508d16918f03f53c52dac54ed825");
    release_aes_modes__feedback(f);
    release_aes_modes__feedback(g);
    f = aes_modes__ctr(key(), octets("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"), octets(P1), 128);
    matches(f->data, "874d6191b620e3261bef6864990db6ce");
    matches(f->next_reg, "f0f1f2f3f4f5f6f7f8f9fafbfcfdff00");
    f->next_reg->count++;
    g = aes_modes__ctr(key(), f->next_reg, octets(P2), 128);
    matches(g->data, "9806f66b7970fdff8617187bb9fffdff");
    release_aes_modes__feedback(f);
    release_aes_modes__feedback(g);

    b = aes_modes__cmac_finish(key(),octets(ZERO),octets(ZERO),0,128);
    matches(b, "bb1d6929e95937287fa37d129b756746");
    release_aes_modes_array_1(b);
    b = aes_modes__cmac_finish(key(),octets(ZERO),octets(P1),128,128);
    matches(b, "070a16b46b4d4144f79bdd9dd04a287c");
    release_aes_modes_array_1(b);
    puts("SP 800-38A and AES-CMAC vectors passed.");
    return 0;
}
