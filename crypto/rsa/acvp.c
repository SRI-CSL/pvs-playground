#include "rsa_encoding_c.h"
#include <assert.h>
typedef rsa_encoding_record_1_t octets_t;
static uint32_t u32(void) {
    uint8_t a[4];
    assert(fread(a,1,4,stdin)==4);
    return (uint32_t)a[0]<<24 | (uint32_t)a[1]<<16 | (uint32_t)a[2]<<8 | a[3];
}
static octets_t field(void) {
    uint32_t n=u32();
    assert(n<(1u<<28));
    octets_t v=new_rsa_encoding_record_1();
    v->length=n;
    v->seq=new_rsa_encoding_array_0(n);
    assert(fread(v->seq->elems,1,n,stdin)==n);
    return v;
}
int main(void) {
    unsigned total=0,passed=0;
    int pss;
    while ((pss=getchar())!=EOF) {
        int h=getchar(),mask=getchar();
        uint32_t id=u32();
        octets_t n=field(),e=field(),m=field(),s=field(),salt=field();
        assert((pss==0 || pss==1) && h>=1 && h<=12 && mask>=0 && mask<=2);
        ++total;
        bool_t good;
        if (pss) {
            /* Recover the encoded representative independently of the PSS
             * verifier; the supplied salt checks every byte of EMSA-PSS. */
            ++n->count; ++e->count; ++s->count; ++m->count;
            rsa_primitive__rsa_result_t rep=rsa_primitive__rsa_public(
                (rsa_primitive__modulus_t)n,(rsa_primitive__modulus_t)e,(rsa_primitive__modulus_t)s);
            octets_t em=rsa_encoding__pss(h,mask,n->length,m,salt);
            good=rep->valid && equal_rsa_encoding_record_1((octets_t)rep->data,em);
            release_rsa_primitive__rsa_result(rep);
            release_rsa_encoding_record_1(em);
            bool_t verified=rsa_encoding__verify_pss(h,mask,n,e,m,s);
            good=good && verified;
        } else {
            release_rsa_encoding_record_1(salt);
            good=rsa_encoding__verify_v15(h,n,e,m,s);
        }
        if (good) ++passed;
        else fprintf(stderr,"RSA ACVP signature mismatch at case %u\n",id);
    }
    printf("RSA ACVP signatures: %u of %u cases passed.\n",passed,total);
    return total && total==passed ? 0 : 1;
}
