#include "appendix_h_ecc_c.h"
#include "appendix_h_c.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef appendix_h_ecc_record_1_t limbs_t;
typedef appendix_h_ecc_record_5_t octets_t;
static uint8_t digit(char c) {
    if (c>='0' && c<='9') return (uint8_t)(c-'0');
    assert(c>='a' && c<='f');
    return (uint8_t)(c-'a'+10);
}
static uint8_t octet(const char *s) { return (uint8_t)((digit(s[0])<<4)|digit(s[1])); }
static octets_t bytes(const char *s) {
    uint32_t n=(uint32_t)(strlen(s)/2);
    assert(2*n==strlen(s));
    octets_t v=new_appendix_h_ecc_record_5();
    v->length=n;
    v->seq=new_appendix_h_ecc_array_4(n);
    for (uint32_t i=0;i<n;++i) v->seq->elems[i]=octet(s+2*i);
    return v;
}
static limbs_t number(unsigned n,const char *s) {
    limbs_t v=new_appendix_h_ecc_record_1();
    v->len=(uint16_t)n;
    v->word=new_appendix_h_ecc_array_0(n);
    memset(v->word->elems,0,4*n);
    size_t length=strlen(s)/2;
    assert(2*length==strlen(s) && length<=4*n);
    for (size_t i=0;i<length;++i)
        v->word->elems[i/4]|=(uint32_t)octet(s+2*(length-1-i))<<(8*(i%4));
    return v;
}
static bool matches(limbs_t v,const char *s) {
    limbs_t expected=number(v->len,s);
    bool ok=equal_appendix_h_ecc_record_1(v,expected);
    release_appendix_h_ecc_record_1(expected);
    return ok;
}
static appendix_h_ecc__affine_t point(unsigned n,const char *x,const char *y) {
    appendix_h_ecc__affine_t q=new_appendix_h_ecc__affine();
    q->finite=true;
    q->x=number(n,x);
    q->y=number(n,y);
    return q;
}
int main(void) {
    unsigned c,total=0;
    char hash[65],qx[129],qy[129],kx[129],ky[129],dh[129],r[129],s[129],vr[129],vs[129];
    while (scanf("%u %64s %128s %128s %128s %128s %128s %128s %128s %128s %128s",
                 &c,hash,qx,qy,kx,ky,dh,r,s,vr,vs)==11) {
        assert(c<11);
        unsigned n=appendix_h__width(c);
        appendix_h_ecc__affine_t q=appendix_h_ecc__multiply(c,appendix_h_ecc__generator(c),number(n,"03"));
        assert(q->finite && matches(q->x,qx) && matches(q->y,qy));
        release_appendix_h_ecc__affine(q);
        appendix_h_ecc__result_t secret=appendix_h_ecc__cdh(c,number(n,"03"),point(n,kx,ky));
        octets_t expected=bytes(dh);
        assert(secret->ok && equal_appendix_h_ecc_record_5(secret->value,expected));
        release_appendix_h_ecc_record_5(expected);
        release_appendix_h_ecc__result(secret);
        appendix_h_ecc__signature_t sig=appendix_h_ecc__sign(c,number(n,"03"),number(n,"07"),bytes(hash));
        if (!sig->ok || !matches(sig->value->r,r) || !matches(sig->value->s,s)) {
            fprintf(stderr,"appendix-h profile %u fixed-nonce signature mismatch (r=%d s=%d)\n",c,matches(sig->value->r,r),matches(sig->value->s,s));
            return 1;
        }
        release_appendix_h_ecc__signature(sig);
        assert(appendix_h_ecc__verify(c,point(n,qx,qy),bytes(hash),number(n,vr),number(n,vs)));
        hash[0]=hash[0]=='0'?'1':'0';
        assert(!appendix_h_ecc__verify(c,point(n,qx,qy),bytes(hash),number(n,vr),number(n,vs)));
        ++total;
    }
    printf("Appendix H: %u domain, CDH and ECDSA cases passed\n",total);
    return total==11?0:1;
}
