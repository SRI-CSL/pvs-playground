#include "gcm_c.h"
#include <assert.h>

static gcm__nonce_t bytes(const char *hex) {
    size_t n = strlen(hex)/2;
    gcm__nonce_t data = new_gcm__nonce();
    data->length = n;
    data->seq = new_gcm_array_0(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned byte;
        assert(sscanf(hex + 2*i, "%2x", &byte) == 1);
        data->seq->elems[i] = (uint8_t)byte;
    }
    return data;
}
static aes_modes__mode_key_adt_t key(const char *hex) {
    gcm__nonce_t buf = bytes(hex);
    assert(buf->length == 16);
    aes_modes_array_1_t k = new_aes_modes_array_1(16);
    memcpy(k->elems,buf->seq->elems,16);
    release_gcm__nonce(buf);
    return con_aes_modes__mk128(k);
}
static void matches(gcm__nonce_t x,const char *hex) {
    gcm__nonce_t y = bytes(hex);
    assert(x->length == y->length && !memcmp(x->seq->elems,y->seq->elems,x->length));
    release_gcm__nonce(y);
}
static void vector(const char *k,const char *iv,const char *aad,const char *pt,
                   const char *ct,const char *tag) {
    uint8_t n = strlen(tag)/2;
    gcm__sealed_t c = gcm__encrypt(key(k),bytes(iv),bytes(aad),bytes(pt),n);
    matches(c->ciphertext,ct);
    matches(c->auth,tag);
    ++c->count;
    gcm__opened_t o = gcm__decrypt(key(k),bytes(iv),bytes(aad),c,n);
    assert(o->valid);
    matches(o->plaintext,pt);
    release_gcm__opened(o);
    c->auth->seq->elems[0] ^= 1;
    o = gcm__decrypt(key(k),bytes(iv),bytes(aad),c,n);
    assert(!o->valid && o->plaintext->length == 0);
    release_gcm__opened(o);
}
int main(void) {
    /* McGrew/Viega GCM submission, Appendix B, test cases 1, 2 and 5. */
    const char *zero_key = "00000000000000000000000000000000";
    const char *iv = "000000000000000000000000";
    vector(zero_key,iv,"","","","58e2fccefa7e3061367f1d57a4e7455a");
    vector(zero_key,iv,"",zero_key,"0388dace60b6a392f328c2b971b2fe78",
           "ab6e47d42cec13bdf53a67b21257bddf");
    vector("feffe9928665731c6d6a8f9467308308","cafebabefacedbad",
           "feedfacedeadbeeffeedfacedeadbeefabaddad2",
           "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a72"
           "1c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39",
           "61353b4c2806934a777ff51fa22a4755699b2a714fcdc6f83766e5f97b6c7423"
           "73806900e49f24b22b097544d4896b424989b5e1ebac0f07c23f4598",
           "3612d2e79e3b0785561be14aaca2fccb");
    gcm__nonce_t truncated = gcm__gmac(key(zero_key),bytes(iv),bytes(""),12);
    matches(truncated,"58e2fccefa7e3061367f1d57");
    release_gcm__nonce(truncated);
    puts("SP 800-38D GCM/GMAC, alternate IV length, truncation and rejection passed.");
    return 0;
}
