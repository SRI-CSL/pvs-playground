#include "slh_wots_c.h"
#include <assert.h>

/* Input octets and independently computed SHAKE256 fixtures for FIPS 205,
 * Algorithms 5–8. The location exercises the high 32 bits of the tree index. */
static slh_wots_record_3_t octets(uint8_t n, uint8_t start) {
    slh_wots_record_3_t x = new_slh_wots_record_3();
    x->length = n;
    x->seq = new_slh_wots_array_2(n);
    for (uint8_t i=0; i<n; ++i) x->seq->elems[i] = start+i;
    return x;
}
static slh_wots__posn_t location(void) {
    slh_wots__posn_t p=new_slh_wots__posn();
    p->use_sha2=false;
    p->layer=3;
    p->tree=UINT64_C(0x123456789abcdef0);
    p->leaf=5;
    return p;
}
static void matches(const uint8_t *actual, const char *expected, size_t n) {
    assert(strlen(expected)==2*n);
    for (size_t i=0; i<n; ++i) {
        unsigned value;
        assert(sscanf(expected+2*i,"%2x",&value)==1 && actual[i]==value);
    }
}
static void test(uint8_t n,const char *pk,const char *first,const char *last) {
    slh_wots_record_3_t a=slh_wots__wots_pk(n,octets(n,0),octets(n,64),location());
    assert(a->length==n);
    matches(a->seq->elems,pk,n);
    slh_wots_record_3_t sig=slh_wots__wots_sign(n,octets(n,0),octets(n,64),octets(n,128),location());
    assert(sig->length==(2*n+3)*n);
    matches(sig->seq->elems,first,n);
    matches(sig->seq->elems+sig->length-n,last,n);
    ++sig->count;
    slh_wots_record_3_t b=slh_wots__wots_recover(n,octets(n,64),octets(n,128),location(),sig);
    assert(equal_slh_wots_record_3(a,b));
    release_slh_wots_record_3(b);
    b=slh_wots__wots_recover(n,octets(n,64),octets(n,129),location(),sig);
    assert(!equal_slh_wots_record_3(a,b));
    release_slh_wots_record_3(a);
    release_slh_wots_record_3(b);
}
int main(void) {
    test(16,"a9f4779362dea26a0ba96355bdbf49ce",
         "de2f2bb08106778ee55b85a226ceee20",
         "945b511f9634f3dd2eca88c0bd1403f0");
    test(24,"60fd93be8cf89ab09696e9243105cecf0b3e2fa24097d614",
         "11c9765f9213e8ec3714cb2d6b2b9dbeaee86b7ded13bc07",
         "6900b2f85be0cbd5db7567745933da49159e55fb0ed38ebc");
    test(32,"a81537674adf76a3c59d02b67e01247a080010a5cace09b9b72e9b4a78ce5f11",
         "83ab0eedc4b5f8b6e77a7404f5a80cee1aa8076428ebc9e9aaa5cb59dc62dd4b",
         "a54efc9ead21fdb567dfa8d487486cec42c6910c04da6e4f731fc940c6db8f3b");
    puts("FIPS 205 SHAKE WOTS+ key generation, signing and recovery passed at n=16/24/32.");
    return 0;
}
