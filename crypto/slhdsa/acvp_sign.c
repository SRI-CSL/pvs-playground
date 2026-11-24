#include "slh_sign_c.h"
#include <assert.h>

typedef slh_sign_record_2_t octets_t;
#define new_octets new_slh_sign_record_2
#define new_octet_array new_slh_sign_array_1
#include "acvp_read.h"

/* The valid sigVer cases also carry the three seeds, signing key and coins.
 * Recompute both the key pair and every signature octet. */
static slh_sign_record_2_t seed_from(slh_sign_record_2_t key, unsigned offset) {
    slh_sign_record_2_t v=new_slh_sign_record_2();
    v->length=16;
    v->seq=new_slh_sign_array_1(16);
    memcpy(v->seq->elems,key->seq->elems+offset,16);
    return v;
}
int main(void) {
    int p=getchar();
    assert(p==1 || p==7);
    slh_sign_record_2_t sk=field(),pk=field(),coins=field(),context=field(),message=field(),signature=field();
    assert(getchar()==EOF && sk->length==64 && pk->length==32 && coins->length==16 && context->length<=255);
    slh_sign__keys_t derived=slh_sign__keygen_internal(p,seed_from(sk,0),seed_from(sk,16),seed_from(sk,32));
    assert(equal_slh_sign_record_2(derived->pk,pk) && equal_slh_sign_record_2(derived->sk,sk));
    release_slh_sign__keys(derived);
    release_slh_sign_record_2(pk);
    slh_sign_record_2_t actual=slh_sign__sign_message(p,sk,coins,context,message,true);
    assert(equal_slh_sign_record_2(actual,signature));
    release_slh_sign_record_2(actual);
    release_slh_sign_record_2(signature);
    printf("SLH-DSA %s-128f ACVP key generation and signing passed.\n",p==7 ? "SHA2" : "SHAKE");
    return 0;
}
