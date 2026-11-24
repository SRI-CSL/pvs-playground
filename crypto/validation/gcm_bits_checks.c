#define main check_octet_examples
#include "gcm_checks.c"
#undef main
#include "gcm_bits_c.h"

static gcm_bits__packed_t packed(const char *s,unsigned tail) {
    gcm_bits__packed_t p=new_gcm_bits__packed();
    p->value=(gcm_bits_record_1_t)bytes(s); p->used=tail; return p;
}
int main(void) {
    check_octet_examples();
    const char *k="00000000000000000000000000000000";
    gcm_bits__packet_t v=gcm_bits__seal_bits(key(k),packed("c0ffef",7),packed("dead",5),
                                 packed("000102030405060708090a0b0c0d0e0f88",1),16);
    matches((gcm__nonce_t)v->ciphertext->value,"b526d26ab75982af042cec31ac77c61e00");
    assert(v->ciphertext->used==1);
    matches((gcm__nonce_t)v->auth,"1ad408d97f9fdacfb26446e98c23740f");
    ++v->count;
    gcm_bits__open_result_t r=gcm_bits__open_bits(key(k),packed("c0ffee",7),packed("dea8",5),v,16);
    assert(r->valid && r->plaintext->used==1);
    matches((gcm__nonce_t)r->plaintext->value,"000102030405060708090a0b0c0d0e0f80");
    release_gcm_bits__open_result(r);
    r=gcm_bits__open_bits(key(k),packed("c0ffee",7),packed("dea8",4),v,16);
    assert(!r->valid && !r->plaintext->value->length);
    release_gcm_bits__open_result(r);
    puts("GCM partial IV, AAD and plaintext lengths passed.");
}
