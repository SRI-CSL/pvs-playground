#include "composite_kem_c.h"
#include "kem_confirmation_c.h"
#include <assert.h>
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s<10 && i<64 ? (s*73+i)&255 : 256; }
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
typedef composite_kem_record_1_t octets_t;
static octets_t lit(const char *s) {
    octets_t b=new_composite_kem_record_1(); b->length=strlen(s);
    b->seq=new_composite_kem_array_0(b->length); memcpy(b->seq->elems,s,b->length); return b;
}
static composite_kem__pair_t pair(const char *a,const char *b) {
    composite_kem__pair_t p=new_composite_kem__pair();p->first=lit(a);p->second=lit(b);return p;
}
static composite_kem__ranks_t ranks(void) {
    composite_kem__ranks_t p=new_composite_kem__ranks();p->first=2;p->second=4;return p;
}
static void expect(octets_t x,const char *s) {
    assert(x->length*2==strlen(s));
    for(unsigned i=0;i<x->length;++i){unsigned v;assert(sscanf(s+2*i,"%2x",&v)==1 && v==x->seq->elems[i]);}
}
static kem_confirmation_record_2_t party(const char *id,const char *e) {
    kem_confirmation_record_2_t p=new_kem_confirmation_record_2();
    p->identity=(kem_confirmation_record_1_t)lit(id);p->ephemeral=(kem_confirmation_record_1_t)lit(e);return p;
}
#define FIELD(s) ((kem_confirmation_record_1_t)lit(s))
int main(void) {
    octets_t x=composite_kem__combine(pair("a","b"),pair("c","d"),pair("e","f"),ranks(),lit("pair"));
    expect(x,"ace99876790901f55b22d33937720d59b0f111b020462433bb66a33106802578");
    release_composite_kem_record_1(x);
    composite_kem__pair_key_t k=composite_kem__pair_gen(ranks(),1,2);
    assert(k->ok); ++k->ek->count; k->dk->count+=2;
    composite_kem__sealed_pair_t c=composite_kem__pair_encaps(ranks(),k->ek,3,4,lit("pair"));
    assert(c->ok); c->ct->count+=2;
    composite_kem_record_11_t d=composite_kem__pair_decaps(ranks(),k->dk,c->ct,lit("pair"));
    assert(d->ok && equal_composite_kem_record_1(d->value,c->secret));
    release_composite_kem_record_11(d);
    d=composite_kem__pair_decaps(ranks(),k->dk,c->ct,lit("other domain"));
    assert(d->ok && !equal_composite_kem_record_1(d->value,c->secret));release_composite_kem_record_11(d);
    release_composite_kem__sealed_pair(c); release_composite_kem__pair_key(k);
    k=composite_kem__pair_gen(ranks(),1,1);assert(!k->ok);release_composite_kem__pair_key(k);
    kem_confirmation_record_1_t key=FIELD("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");key->count+=2;
    kem_confirmation_record_1_t tag=kem_confirmation__kem_tag(key,party("Bob","Cipher"),party("Alice","Public"),
                                                                true,false,FIELD("X"),FIELD("Y"));
    expect((octets_t)tag,"db56dfa1c6c32402e3c07c0ea441d8e7"); ++tag->count;
    kem_confirmation_record_3_t res=kem_confirmation__release_key(key,party("Bob","Cipher"),party("Alice","Public"),
                                                    true,false,FIELD("X"),FIELD("Y"),tag,FIELD("data"));
    assert(res->ok && res->data->length==4);release_kem_confirmation_record_3(res);
    res=kem_confirmation__release_key(key,party("Bob","Cipher"),party("Alice","Public"),true,true,
                                      FIELD("X"),FIELD("Y"),tag,FIELD("data"));
    assert(!res->ok && !res->data->length);release_kem_confirmation_record_3(res);
    puts("SP 800-227 combiner, composite KEM and key confirmation passed.");
}
