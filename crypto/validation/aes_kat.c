/* Feed AESAVS ECB vectors to the generated entry points. Each PVS function
 * consumes the references passed to it and returns an owned block. */
#include <stdio.h>
#include <string.h>
#include "aes_fips197_c.h"

static int nibble(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    if ('A' <= ch && ch <= 'F') return ch - 'A' + 10;
    if ('a' <= ch && ch <= 'f') return ch - 'a' + 10;
    return -1;
}

static aes_fips197__block_t octets(const char *hex) {
    size_t n = strlen(hex) / 2;
    aes_fips197__block_t x = new_aes_fips197__block(n);
    for (size_t i = 0; i < n; i++) {
        int high = nibble(hex[2 * i]), low = nibble(hex[2 * i + 1]);
        if (high < 0 || low < 0) exit(2);
        x->elems[i] = (uint8_t)((high << 4) | low);
    }
    return x;
}

int main(void) {
    char direction, key[65], input[33], want[33];
    unsigned count = 0;
    int fields;
    while ((fields = scanf(" %c %64s %32s %32s", &direction, key, input, want)) == 4) {
        bool enc = direction == 'E';
        if ((!enc && direction != 'D') || strlen(input) != 32 || strlen(want) != 32) return 2;
        aes_fips197__block_t k = octets(key), a = octets(input), expected = octets(want), out;
        switch (strlen(key)) {
        case 32: out = enc ? aes_fips197__aes128_encrypt(a, k) : aes_fips197__aes128_decrypt(a, k); break;
        case 48: out = enc ? aes_fips197__aes192_encrypt(a, k) : aes_fips197__aes192_decrypt(a, k); break;
        case 64: out = enc ? aes_fips197__aes256_encrypt(a, k) : aes_fips197__aes256_decrypt(a, k); break;
        default: return 2;
        }
        if (out->size != 16 || memcmp(out->elems, expected->elems, 16)) {
            fprintf(stderr, "AESAVS mismatch at case %u\n", count);
            return 1;
        }
        release_aes_fips197__block(expected);
        release_aes_fips197__block(out);
        count++;
    }
    return fields == EOF && count != 0 ? 0 : 2;
}
