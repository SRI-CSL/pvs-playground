/* SP 800-90C profiles. Known answers use independent HMAC and hash computations. */
#include "rbg_profiles_c.h"
#include "rbg_instances_c.h"
#include "rbg_mechanisms_c.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s==99 ? 256 : (s+i+3)&255; }
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return s==99 ? 256 : (s+i)&255; }
static void *msg(const char *s) {
    rbg_instances_record_2_t m=new_rbg_instances_record_2();
    m->length=strlen(s);
    m->seq=new_rbg_instances_array_1(m->length);
    memcpy(m->seq->elems,s,m->length);
    return m;
}
static void hex(const uint8_t *p,unsigned n,const char *s) {
    assert(n==strlen(s)/2);
    for (unsigned i=0;i<n;++i) {
        unsigned v;
        assert(sscanf(s+2*i,"%2x",&v)==1 && p[i]==v);
    }
}
static rbg_instances__instance_t hmac_instance(unsigned role,unsigned alg,unsigned strength) {
    return rbg_instances__init(role,con_rbg_mechanisms__hmac_engine(alg),strength,msg("P"),
                               11,role!=rbg_instances__rbg2_np(),role==rbg_instances__rbg1());
}
static void known(rbg_instances__returned_t r,const char *s) {
    assert(r->ok); hex(r->data->seq->elems,r->data->length,s);
    release_rbg_instances__returned(r);
}
static void failed(rbg_instances__returned_t r) {
    assert(!r->ok && !r->data->length);
    release_rbg_instances__returned(r);
}
static rbg_profiles__transcript_t transcript(unsigned n,unsigned size) {
    rbg_profiles__transcript_t t=new_rbg_profiles__transcript();
    t->length=n; t->samples=new_rbg_profiles_array_1(n);
    for (unsigned i=0;i<n;++i) {
        rbg_profiles__source_chunk_t c=new_rbg_profiles__source_chunk();
        c->id=11+i; c->offset=0; c->physical=true; c->healthy=true; c->validated=true;
        c->octets=size; c->credit=2048*size; t->samples->elems[i]=c;
    }
    return t;
}
static rbg_profiles__selection_t selection(bool physical) {
    rbg_profiles__selection_t s=new_rbg_profiles__selection();
    s->physical_only=physical; s->targeted=false; s->target=0; return s;
}
static rbg_profiles__conditioner_adt_t sha(void) {
    return con_rbg_profiles__hashed(2,0,msg(""));
}
int main(void) {
    unsigned rs=rbg_instances__rbg3_r(), xr=rbg_instances__rbg3_x(), two=rbg_instances__rbg2_p();
    for (unsigned b=0;b<2;++b) {
        rbg_instances__instance_t a=hmac_instance(rs,2,128);
        assert(a->level==256);
        rbg_instances__returned_t r=rbg_instances__full_generate(a,259,msg("X"),22,23,b);
        assert(r->current->after_rs);
        ++r->current->count;
        failed(rbg_instances__direct_generate(r->current,8,128,msg(""),99,false,b));
        known(r,b ? "0cd0c04fed2807968470ea12ee55d48ab97fc53a32795ca317568f003729fd1560"
                  : "1723c76dde1c14997a13b74061121721923adea7e7e164daaf0126b736ce2aa9c0");
    }
    known(rbg_instances__full_generate(hmac_instance(xr,2,256),13,msg("X"),22,23,false),"0718");
    known(rbg_instances__direct_generate(hmac_instance(two,8,128),128,128,msg("X"),11,false,false),
          "8eb437bdfb82ef25e098f0e5bef0b8d1");
    failed(rbg_instances__direct_generate(hmac_instance(two,8,128),8,192,msg(""),11,false,false));
    failed(rbg_instances__full_generate(hmac_instance(rs,7,192),8,msg(""),12,11,false));
    for (unsigned t=0;t<3;++t) {
        for (unsigned df=0;df<2;++df) {
            rbg_instances__instance_t a=rbg_instances__init(rs,con_rbg_mechanisms__ctr_engine(t,df),
                                                           128,msg(""),11,true,false);
            assert(a->level==128+64*t);
            rbg_instances__returned_t r=rbg_instances__full_generate(a,513,msg("a"),22,23,true);
            assert(r->ok && r->data->length==65 && (r->data->seq->elems[64]&127)==0);
            release_rbg_instances__returned(r);
        }
    }
    for (unsigned hash=0;hash<11;++hash) {
        rbg_instances__instance_t a=rbg_instances__init(two,con_rbg_mechanisms__hash_engine(hash),
                                                       128,msg(""),11,true,false);
        rbg_instances__returned_t r=rbg_instances__direct_generate(a,17,128,msg("X"),22,true,false);
        assert(r->ok && r->data->length==3 && (r->data->seq->elems[2]&127)==0);
        release_rbg_instances__returned(r);
    }
    rbg_instances__branch_t f=rbg_instances__child(hmac_instance(rbg_instances__rbgc(),2,256),
                                                  con_rbg_mechanisms__hash_engine(8),192,msg("p"),msg("a"));
    assert(f->ok && f->child->kind==rbg_instances__rbgc_child());
    ++f->child->count; ++f->parent->count;
    rbg_instances__branch_t f2=rbg_instances__refresh_child(f->parent,f->child,msg("c"),msg("p"));
    assert(f2->ok);
    release_rbg_instances__branch(f); release_rbg_instances__branch(f2);
    puts("RBG3 Methods A/B, direct-access barrier, mechanisms and RBGC passed"); fflush(stdout);

    rbg_profiles__collection_t c=rbg_profiles__get_conditioned_input(transcript(1,40),selection(true),sha(),13,true,0);
    assert(c->ok && c->next==1); hex(c->value->seq->elems,c->value->length,"a668");
    release_rbg_profiles__collection(c);
    c=rbg_profiles__get_conditioned_input(transcript(1,40),selection(true),sha(),13,false,0);
    assert(c->ok && c->next==1); hex(c->value->seq->elems,c->value->length,
        "a66dfbfbe97786e2bbd9639fc537a7744d53ac009e7abb05d55720d9413f2c13");
    release_rbg_profiles__collection(c);
    rbg_profiles__transcript_t t=transcript(3,8);
    t->samples->elems[0]->validated=false; t->samples->elems[1]->physical=false;
    ++t->count;
    c=rbg_profiles__get_entropy_bitstring(t,selection(true),64,0);
    assert(c->ok && c->next==3 && c->value->length==16); release_rbg_profiles__collection(c);
    t->samples->elems[2]->healthy=false;
    c=rbg_profiles__get_entropy_bitstring(t,selection(true),64,0);
    assert(!c->ok && c->error_source==13 && !c->value->length);
    release_rbg_profiles__collection(c);
    const char *want[]={"47928a75addbb1873430f94089d7bae14c90cfca0a8947d96faa333958e07e5340",
                        "138dfdbdf43e9befa9db88cc14b17e720e37e287db7eb09c959451fea2e0e813a0"};
    for (unsigned b=0;b<2;++b) {
        rbg_profiles__delivery_t d=rbg_profiles__conditioned_full_generate((void*)hmac_instance(rs,2,256),
            259,msg("X"),transcript(4,40),selection(true),sha(),0,b);
        assert(d->answer->ok && d->next==4);
        hex(d->answer->data->seq->elems,d->answer->data->length,want[b]);
        release_rbg_profiles__delivery(d);
    }
    rbg_profiles__delivery_t d=rbg_profiles__conditioned_full_generate((void*)hmac_instance(xr,2,256),
        13,msg("X"),transcript(1,40),selection(true),sha(),0,false);
    assert(d->answer->ok && d->next==1);
    hex(d->answer->data->seq->elems,d->answer->data->length,"b760");
    release_rbg_profiles__delivery(d);
    d=rbg_profiles__conditioned_full_generate((void*)hmac_instance(rs,2,256),
        259,msg("X"),transcript(3,40),selection(true),sha(),0,true);
    assert(!d->answer->ok && d->next==3 && d->answer->data->length==0);
    release_rbg_profiles__delivery(d);
    t=transcript(1,40); t->samples->elems[0]->credit=8192;
    ++t->count;
    c=rbg_profiles__source_material(t,selection(true),con_rbg_profiles__raw_source(),32,false,0);
    assert(c->ok && c->value->length==40); release_rbg_profiles__collection(c);
    c=rbg_profiles__source_material(t,selection(true),con_rbg_profiles__raw_source(),32,true,0);
    assert(!c->ok && !c->value->length); release_rbg_profiles__collection(c);
    f=rbg_instances__seed_from_rbg(rbg_instances__rbg1(),hmac_instance(two,2,128),
        con_rbg_mechanisms__hmac_engine(2),192,msg(""),msg(""),11,22,false,true,false);
    assert(!f->ok); release_rbg_instances__branch(f);
    f=rbg_instances__seed_from_rbg(rbg_instances__rbg1(),hmac_instance(two,2,128),
        con_rbg_mechanisms__hmac_engine(2),128,msg(""),msg(""),11,22,false,true,false);
    assert(f->ok); release_rbg_instances__branch(f);
    puts("SP 800-90C collection and conditioning passed");
}
