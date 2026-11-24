#include "bit_derivation_c.h"
#include "hash_truncation_c.h"
#include <assert.h>
static bit_derivation_record_1_t bytes(const char *s) {
    bit_derivation_record_1_t b=new_bit_derivation_record_1();
    b->length=strlen(s); b->seq=new_bit_derivation_array_0(b->length);
    memcpy(b->seq->elems,s,b->length);return b;
}
static bit_derivation_record_3_t packed(const char *s) {
    bit_derivation_record_3_t p=new_bit_derivation_record_3();
    p->octets=bytes(s);p->tail=0;p->used=0;return p;
}
static void expect(bit_derivation_record_1_t b,const char *hex) {
    assert(b->length*2==strlen(hex));
    for(unsigned i=0;i<b->length;++i) {
        unsigned v; assert(sscanf(hex+2*i,"%2x",&v)==1 && v==b->seq->elems[i]);
    }
}
#define MSG(s) ((hash_truncation_record_1_t)bytes(s))
int main(void) {
    hash_truncation_record_1_t digest=hash_truncation__truncated(2,MSG("abc"),1,5);
    expect((bit_derivation_record_1_t)digest,"ba78");
    release_hash_truncation_record_1(digest);
    hash_truncation_record_1_t tag=hash_truncation__mac_tag(2,MSG("key"),MSG("abc"),4,3);
    expect((bit_derivation_record_1_t)tag,"9c196e32c0"); ++tag->count;
    assert(hash_truncation__check_tag(2,MSG("key"),MSG("abc"),4,3,tag));
    tag->seq->elems[4]|=1;
    assert(!hash_truncation__check_tag(2,MSG("key"),MSG("abc"),4,3,tag));
    bit_derivation_record_2_t a=bit_derivation__hmac_kdf_bits(2,bytes("key"),0,1,bytes("label"),
                                                              bytes("ctx"),bytes(""),1,5);
    assert(a->ok);expect(a->data,"4278"); release_bit_derivation_record_2(a);
    a=bit_derivation__hash_kda_bits(2,false,bytes(""),bytes("Z"),bytes("fixed"),1,5);
    assert(a->ok);expect(a->data,"2458"); release_bit_derivation_record_2(a);
    bit_derivation_record_3_t p=bit_derivation__kmac_kdf_bits(128,packed("key"),packed("ctx"),packed("label"),1,5);
    assert(p->used==5 && p->tail==16);expect(p->octets,"cc");release_bit_derivation_record_3(p);
    p=bit_derivation__kmac_kda_bits(128,bytes(""),bytes("Z"),bytes("fixed"),1,5);
    assert(p->used==5 && p->tail==3);expect(p->octets,"56");release_bit_derivation_record_3(p);
    puts("Truncated hash, HMAC and bit-length key derivation checks passed.");
}
