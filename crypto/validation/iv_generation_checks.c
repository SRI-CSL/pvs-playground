#include "iv_generation_c.h"
#include <assert.h>
uint16_t crypto_prng_lookup(uint64_t stream,uint32_t i) { return stream==1 ? i : 256; }
uint16_t crypto_entropy_lookup(uint64_t stream,uint32_t i) { return 256; }
int main(void) {
    iv_generation__serial_t s=new_iv_generation__serial();
    s->fixed=0x01020304; s->counter=UINT64_MAX-1; s->exhausted=false;
    iv_generation__reservation_t first=iv_generation__reserve(s);
    assert(first->ok && !first->next->exhausted);
    for(unsigned i=0;i<4;++i) assert(first->iv->seq->elems[i]==i+1);
    for(unsigned i=4;i<11;++i) assert(first->iv->seq->elems[i]==255);
    assert(first->iv->seq->elems[11]==254);
    ++first->next->count;
    iv_generation__reservation_t last=iv_generation__reserve(first->next);
    assert(last->ok && last->next->exhausted && last->iv->seq->elems[11]==255);
    ++last->next->count;
    iv_generation__reservation_t fail=iv_generation__reserve(last->next);
    assert(!fail->ok && fail->next->exhausted);
    release_iv_generation__reservation(first); release_iv_generation__reservation(last);
    release_iv_generation__reservation(fail);
    iv_generation__random_reservation_t v=iv_generation__random_iv(1,1);
    assert(v->ok && v->remaining==0 && v->iv->seq->elems[11]==11);
    release_iv_generation__random_reservation(v);
    v=iv_generation__random_iv(1,0); assert(!v->ok && v->remaining==0);
    release_iv_generation__random_reservation(v);
    v=iv_generation__random_iv(0,1); assert(!v->ok && v->remaining==1);
    release_iv_generation__random_reservation(v);
    iv_generation_record_5_t b=iv_generation__random_block_iv(1);
    assert(b->ok && b->value->seq->elems[15]==15);
    release_iv_generation_record_5(b);
    puts("Deterministic IV exhaustion, random invocation budget and block IV checks passed.");
}
