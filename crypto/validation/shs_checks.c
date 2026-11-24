/* CAVP SHAVS bit-oriented ShortMsg response rows, supplied on standard input. */
#include "secure_hash_c.h"
#include <stdio.h>
#include <string.h>

typedef secure_hash_record_1_t (*hash_bits)(secure_hash_record_1_t, uint8_t, uint8_t);

static int octet(const char *hex) {
    unsigned value;
    if (sscanf(hex, "%2x", &value) != 1) return -1;
    return (int)value;
}

int main(void) {
    static const hash_bits hashes[] = {
        secure_hash__sha1_bits, secure_hash__sha224_bits, secure_hash__sha256_bits,
        secure_hash__sha384_bits, secure_hash__sha512_bits,
        secure_hash__sha512_224_bits, secure_hash__sha512_256_bits
    };
    unsigned family, bits, count = 0;
    char message[259], expected[130];
    int parsed;
    while ((parsed = scanf("%u %u %258s %129s", &family, &bits, message, expected)) == 4) {
        unsigned n = bits / 8;
        if (family >= 7 || bits > 1024 ||
            strlen(message) != 2 * ((bits + 7) / 8 ? (bits + 7) / 8 : 1)) return 1;
        secure_hash_record_1_t m = new_secure_hash_record_1();
        m->length = n;
        m->seq = new_secure_hash_array_0(n);
        for (unsigned i = 0; i < n; ++i)
            m->seq->elems[i] = (uint8_t)octet(message + 2*i);
        uint8_t tail = bits % 8 ? (uint8_t)octet(message + 2*n) : 0;
        secure_hash_record_1_t out = hashes[family](m, tail, bits % 8);
        if (strlen(expected) != 2*out->length) return 1;
        for (unsigned i = 0; i < out->length; ++i) {
            if (octet(expected + 2*i) != out->seq->elems[i]) {
                fprintf(stderr, "SHA family %u, %u-bit message, digest byte %u differs\n", family, bits, i);
                return 1;
            }
        }
        release_secure_hash_record_1(out);
        ++count;
    }
    if (parsed != EOF || !count) return 1;
    printf("SHAVS: %u bit-oriented cases passed\n", count);
    return 0;
}
