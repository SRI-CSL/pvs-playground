#include "ccm_c.h"
#include <assert.h>

static ccm__ccm_nonce_t bytes(const char *hex) {
    size_t n = strlen(hex)/2;
    ccm__ccm_nonce_t data = new_ccm__ccm_nonce();
    data->length = n;
    data->seq = new_ccm_array_0(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned byte;
        assert(sscanf(hex + 2*i, "%2x", &byte) == 1);
        data->seq->elems[i] = (uint8_t)byte;
    }
    return data;
}
static aes_modes__mode_key_adt_t key(const char *hex) {
    ccm__ccm_nonce_t buf = bytes(hex);
    assert(buf->length == 16);
    aes_modes_array_1_t k = new_aes_modes_array_1(16);
    memcpy(k->elems,buf->seq->elems,16);
    release_ccm__ccm_nonce(buf);
    return con_aes_modes__mk128(k);
}
static void matches(ccm__ccm_nonce_t x,const char *hex) {
    ccm__ccm_nonce_t y = bytes(hex);
    assert(x->length == y->length && !memcmp(x->seq->elems,y->seq->elems,x->length));
    release_ccm__ccm_nonce(y);
}
static void vector(const char *k,const char *iv,const char *aad,const char *pt,
                   const char *ct,const char *tag) {
    uint8_t n = strlen(tag)/2;
    ccm__sealed_t c = ccm__encrypt(key(k),bytes(iv),bytes(aad),bytes(pt),n);
    matches(c->ciphertext,ct);
    matches(c->auth,tag);
    ++c->count;
    ccm__opened_t o = ccm__decrypt(key(k),bytes(iv),bytes(aad),c,n);
    assert(o->valid);
    matches(o->plaintext,pt);
    release_ccm__opened(o);
    c->auth->seq->elems[0] ^= 1;
    o = ccm__decrypt(key(k),bytes(iv),bytes(aad),c,n);
    assert(!o->valid && o->plaintext->length == 0);
    release_ccm__opened(o);
}
int main(void) {
    /* SP 800-38C Appendix C, examples 1 through 3. */
    const char *k = "404142434445464748494a4b4c4d4e4f";
    vector(k,"10111213141516","0001020304050607","20212223","7162015b","4dac255d");
    vector(k,"1011121314151617","000102030405060708090a0b0c0d0e0f",
           "202122232425262728292a2b2c2d2e2f","d2a1f0e051ea5f62081a7792073d593d","1fc64fbfaccd");
    vector(k,"101112131415161718191a1b","000102030405060708090a0b0c0d0e0f10111213",
           "202122232425262728292a2b2c2d2e2f3031323334353637",
           "e3b201a9f5b71a7a9b1ceaeccd97e70b6176aad9a4428aa5","484392fbc1b09951");
    /* Appendix A.2.2 length encoding boundary. */
    assert(ccm__prefix_length(65279)==2 && ccm__prefix_length(65280)==6);
    assert(!ccm__fits(bytes("101112131415161718191a1b1c"),65536));
    puts("SP 800-38C examples, length limits and authentication rejection passed.");
    return 0;
}
