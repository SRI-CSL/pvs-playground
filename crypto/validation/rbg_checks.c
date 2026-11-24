#include "rbg_constructions_c.h"
#include "rbg_tree_c.h"
#include "crypto_random_buffers_c.h"
#include <assert.h>

uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) {
    return s==99 ? 256 : (s+i+3)&255;
}
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) {
    return (s==99 || (s==98 && i==55)) ? 256 : (s+i)&255;
}
static rbg_constructions__personal_t message(const char *s) {
    rbg_constructions__personal_t m=new_rbg_constructions__personal();
    m->length=strlen(s);
    m->seq=new_rbg_constructions_array_0(m->length);
    memcpy(m->seq->elems,s,m->length);
    return m;
}
static void check(rbg_constructions_record_5_t r,const char *hex) {
    assert(r->success==(hex!=NULL));
    assert(r->data->length==(hex ? strlen(hex)/2 : 0));
    for (unsigned i=0; i<r->data->length; ++i) {
        unsigned x;
        assert(sscanf(hex+2*i,"%2x",&x)==1 && x==r->data->seq->elems[i]);
    }
    release_rbg_constructions_record_5(r);
}
int main(void) {
    rbg_constructions__activated_t a=rbg_constructions__instantiate_rbg1(11,message("P"));
    assert(a->ready);
    check(rbg_constructions__pseudorandom(a,259,message("X")),
          "a9f505b251c3166603ee4c32ebc285eec18fc937f967a99dcd8f8627f48f0aede0");
    a=rbg_constructions__instantiate_rbg2(11,message("P"));
    a->count+=3;
    check(rbg_constructions__prediction_resistant(a,259,message("X"),22),
          "044b3389ded95089e5f97008df1a1b740fd7eb722d2dc4e153ab1a2042b17295c0");
    check(rbg_constructions__rbg3_xor(a,13,message("X"),22),"0718");
    check(rbg_constructions__rbg3_rs(a,259,message("X"),22),
          "1723c76dde1c14997a13b74061121721923adea7e7e164daaf0126b736ce2aa9c0");
    check(rbg_constructions__rbg3_rs(a,259,message("X"),98),NULL);
    a=rbg_constructions__instantiate_rbg1(99,message(""));
    assert(!a->ready);
    check(rbg_constructions__pseudorandom(a,8,message("")),NULL);
    crypto_random_buffers__acquisition_t bad=crypto_random_buffers__entropy_bytes(2,1,UINT32_MAX);
    assert(!bad->ok && !bad->value->seq->elems[0] && !bad->value->seq->elems[1]);
    release_crypto_random_buffers__acquisition(bad);
    rbg_tree_record_3_t root=rbg_tree__root_from_entropy(11,(rbg_tree_record_1_t)message("P"));
    rbg_tree__family_t f=rbg_tree__add_child(root,(rbg_tree_record_1_t)message("child"),
                                               (rbg_tree_record_1_t)message("parent"));
    assert(f->ok);
    f->child->count+=2;
    ++f->parent->count;
    check(rbg_constructions__pseudorandom((rbg_constructions__activated_t)f->child,29,message("")),"6a25ce80");
    rbg_tree__family_t next=rbg_tree__reseed_child(f->parent,f->child,(rbg_tree_record_1_t)message("child"),
                                                    (rbg_tree_record_1_t)message("parent"));
    assert(next->ok);
    ++next->child->count;
    check(rbg_constructions__pseudorandom((rbg_constructions__activated_t)next->child,29,message("")),"d5a14548");
    release_rbg_tree__family(f); release_rbg_tree__family(next);
    puts("RBG1, RBG2, RBG3(XOR), RBG3(RS), RBGC and source failure checks passed.");
}
