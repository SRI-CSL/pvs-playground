/* RFC 3962 Appendix B, 17-, 31-, and 32-octet AES CBC-CTS examples.
 * RFC 3962 uses CS3. SP 800-38A Addendum sections 2--4 specify the
 * permutations needed for the other two variants. */
#include "cbc_cs_c.h"
#include <assert.h>

static cbc_cs_array_0_t block(const char *s) {
    cbc_cs_array_0_t a = new_cbc_cs_array_0(16);
    for (unsigned i=0; i<16; ++i) {
        unsigned v;
        assert(sscanf(s+2*i,"%2x",&v)==1);
        a->elems[i]=(uint8_t)v;
    }
    return a;
}
static aes_modes__mode_key_adt_t key(void) {
    return con_aes_modes__mk128((aes_modes_array_1_t)block("636869636b656e207465726979616b69"));
}
static void matches(cbc_cs_array_0_t a, const char *hex) {
    cbc_cs_array_0_t e=block(hex);
    assert(memcmp(a->elems,e->elems,16)==0);
    release_cbc_cs_array_0(e);
}
#define ZERO "00000000000000000000000000000000"
#define HEAD "4920776f756c64206c696b6520746865"
static void check(unsigned n,const char *p,const char *full,const char *short_part) {
    for (uint8_t variant=0; variant<3; ++variant) {
        bool swapped=variant==enum_cbc_cs__cs3() || (variant==enum_cbc_cs__cs2() && n<128);
        cbc_cs__tail_t c=cbc_cs__encrypt_tail(key(),block(ZERO),block(HEAD),block(p),n,variant);
        matches(c->first,swapped?full:short_part);
        matches(c->second,swapped?short_part:full);
        assert(c->first_bits==(swapped?128:n) && c->second_bits==(swapped?n:128));
        c->first->count++;
        c->second->count++;
        cbc_cs__tail_t a=cbc_cs__decrypt_tail(key(),block(ZERO),c->first,c->second,n,variant);
        matches(a->first,HEAD);
        matches(a->second,p);
        assert(a->first_bits==128 && a->second_bits==n);
        release_cbc_cs__tail(c);
        release_cbc_cs__tail(a);
    }
}
int main(void) {
    check(8,"20000000000000000000000000000000","c6353568f2bf8cb4d8a580362da7ff7f","97000000000000000000000000000000");
    check(120,"2047656e6572616c2047617527732000","fc00783e0efdb2c1d445d4c8eff7ed22","97687268d6ecccc0c07b25e25ecfe500");
    check(128,"2047656e6572616c2047617527732043","39312523a78662d5be7fcbcc98ebf5a8","97687268d6ecccc0c07b25e25ecfe584");
    puts("SP 800-38A Addendum CBC-CS1, CBC-CS2 and CBC-CS3 vectors passed.");
    return 0;
}
