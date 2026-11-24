#include "rsa_provable_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef rsa_provable_record_4_t bytes;
uint16_t crypto_prng_lookup(uint64_t s, uint32_t i) { (void)s; (void)i; return 256; }
uint16_t crypto_entropy_lookup(uint64_t s, uint32_t i) { (void)s; (void)i; return 256; }
static bytes field(const char *v) {
    size_t n = strlen(v) / 2;
    bytes b = new_rsa_provable_record_4();
    b->length = n;
    b->seq = new_rsa_provable_array_3(n);
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
    unsigned id, profile, h, a, b, c, d, passed = 0, count = 0;
    char e[65], s[8193], p[513], q[513];
    while (scanf("%u%u%u%u%u%u%u%64s%8192s%512s%512s", &id, &profile, &h, &a,&b,&c,&d,e,s,p,q)==11) {
        rsa_provable__lengths_t sizes = new_rsa_provable__lengths();
        sizes->a = a; sizes->b = b; sizes->c = c; sizes->d = d;
        bytes expected_p = field(p), expected_q = field(q);
        rsa_provable_record_7_t k = rsa_provable__from_provable_seed(profile,h,field(e),field(s),sizes);
        bool ok = k->ok && same(k->p,expected_p) && same(k->q,expected_q);
        passed += ok;
        ++count;
        if (!ok) fprintf(stderr,"RSA provable generation failed for ACVP case %u\n",id);
        release_rsa_provable_record_7(k);
        release_rsa_provable_record_4(expected_p);
        release_rsa_provable_record_4(expected_q);
    }
    printf("RSA provable generation: %u of %u cases passed\n",passed,count);
    return count && count == passed ? 0 : 1;
}
