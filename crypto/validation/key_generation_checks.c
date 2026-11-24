#include "key_generation_c.h"
#include <assert.h>
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s==1 ? i&255 : 256; }
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
static key_generation_record_1_t octets(const char *s) {
    key_generation_record_1_t b=new_key_generation_record_1();
    b->length=strlen(s);
    b->seq=new_key_generation_array_0(b->length);
    memcpy(b->seq->elems,s,b->length);
    return b;
}
static key_generation__parts_t parts(unsigned keys,const char *first,const char *last) {
    key_generation__parts_t p=new_key_generation__parts();
    p->keys=keys; p->size=2; p->item=new_key_generation_array_3(2);
    p->item->elems[0]=octets(first); p->item->elems[1]=octets(last);
    return p;
}
static void check(key_generation__key_result_t r,const void *want,unsigned n) {
    assert(r->ok==(want!=NULL) && r->data->length==n);
    if (want) assert(!memcmp(r->data->seq->elems,want,n));
    release_key_generation__key_result(r);
}
int main(void) {
    check(key_generation__direct(1,octets("ABC")),"ACA",3);
    check(key_generation__direct(2,octets("ABC")),NULL,0);
    check(key_generation__concatenate(parts(2,"abc","def")),"abcdef",6);
    check(key_generation__concatenate(parts(1,"abc","def")),NULL,0);
    check(key_generation__xor_components(parts(2,"abc","def")),"\x05\x07\x05",3);
    check(key_generation__xor_components(parts(1,"a","ab")),NULL,0);
    key_generation__parts_t p=parts(1,"a","b"); p->item->elems[1]->seq->elems[0]=0;
    check(key_generation__xor_components(p),NULL,0);
    check(key_generation__extract(2,octets("salt"),parts(1,"abc","def"),13),"\x32\x78",2);
    puts("SP 800-133 direct generation, component combinations and truncated extraction passed.");
}
