#include "rsa_auxiliary_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef rsa_auxiliary_record_5_t bytes;
static bytes starts;
static uint32_t start_offset;
/* Stream 1 contains NIST candidate starts. Stream 2 provides deterministic
 * Miller-Rabin bases for this test only. */
uint16_t crypto_prng_lookup(uint64_t s, uint32_t i) {
    if (s == 1 && i < starts->length) {
        assert(i == start_offset++);
        return starts->seq->elems[i];
    }
    if (s == 2) {
        uint32_t x = i + UINT32_C(0x9e3779b9);
        x ^= x >> 16;
        x *= UINT32_C(0x85ebca6b);
        x ^= x >> 13;
        return (uint8_t)x;
    }
    return 256;
}
uint16_t crypto_entropy_lookup(uint64_t s, uint32_t i) { (void)s; (void)i; return 256; }
static bytes field(const char *v) {
    size_t n = strlen(v) / 2;
    bytes b = new_rsa_auxiliary_record_5();
    b->length = n;
    b->seq = new_rsa_auxiliary_array_4(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        assert(sscanf(v + 2*i, "%2x", &x) == 1);
        b->seq->elems[i] = x;
    }
    return b;
}
static int same(bytes a, bytes b) {
    return a->length == b->length && memcmp(a->seq->elems, b->seq->elems, b->length) == 0;
}
int main(void) {
    unsigned id, profile, seeded, pm, qm, a, b, c, d, passed = 0, count = 0;
    char e[65], seed[8193], stream[8193], p[513], q[513];
    while (scanf("%u%u%u%u%u%u%u%u%u%64s%8192s%8192s%512s%512s",
                 &id,&profile,&seeded,&pm,&qm,&a,&b,&c,&d,e,seed,stream,p,q) == 14) {
        rsa_auxiliary_record_15_t sizes = new_rsa_auxiliary_record_15();
        sizes->a = a; sizes->b = b; sizes->c = c; sizes->d = d;
        rsa_auxiliary__sources_t src = new_rsa_auxiliary__sources();
        src->starts = 1; src->tests = 2;
        bytes expected_p = field(p), expected_q = field(q);
        starts = field(stream);
        start_offset = 0;
        rsa_auxiliary_record_14_t k = rsa_auxiliary__auxiliary_key(profile,7,seeded,field(seed),field(e),
                                                                  sizes,pm,qm,src,true);
        bool ok = k->ok && same(k->p,expected_p) && same(k->q,expected_q) && start_offset == starts->length;
        passed += ok;
        ++count;
        if (!ok) fprintf(stderr,"RSA auxiliary generation failed for ACVP case %u\n",id);
        release_rsa_auxiliary_record_14(k);
        release_rsa_auxiliary_record_5(expected_p);
        release_rsa_auxiliary_record_5(expected_q);
        release_rsa_auxiliary_record_5(starts);
    }
    printf("RSA auxiliary generation: %u of %u cases passed\n",passed,count);
    return count && count == passed ? 0 : 1;
}
