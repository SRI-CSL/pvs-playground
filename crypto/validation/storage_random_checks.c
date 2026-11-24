#include "storage_random_c.h"
#include <assert.h>
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s==1 ? i&255 : 256; }
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
static storage_random_record_1_t literal(const char *v) {
    storage_random_record_1_t x=new_storage_random_record_1();
    x->length=strlen(v); x->seq=new_storage_random_array_0(x->length);
    memcpy(x->seq->elems,v,x->length); return x;
}
int main(void) {
    storage_random__generated_t g=storage_random__make_key(2,literal("password"),16,literal("storage"),2,16,1);
    assert(g->ok && g->salt->length==23 && !memcmp(g->salt->seq->elems,"storage",7));
    for (unsigned i=0;i<16;++i) assert(g->salt->seq->elems[7+i]==i);
    static const uint8_t expected[]={0x74,0x61,0x29,0x48,0xa4,0x33,0x89,0xbd,0x8e,0x66,0x21,0xc3,0x20,0x9e,0xea,0xa8};
    assert(g->master->length==16 && !memcmp(g->master->seq->elems,expected,16));
    release_storage_random__generated(g);
    g=storage_random__make_key(2,literal("password"),16,literal("storage"),2,16,0);
    assert(!g->ok && !g->master->length && !g->salt->length);
    release_storage_random__generated(g);
    puts("Random-salt storage-key generation and source failure passed.");
}
