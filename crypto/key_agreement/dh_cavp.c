/* SP 800-56A KASVS, valid SHA-256 no-key-confirmation cases.
 * Input is the whitespace-framed offline fixture produced by dh_vectors.py. */
#include "dh_schemes_c.h"
#include "dh_derivation_c.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef dh_schemes_record_4_t scalar_t;
typedef dh_schemes_record_7_t point_t;
typedef dh_schemes_record_5_t domain_t;
typedef dh_schemes_record_2_t secret_t;
typedef dh_derivation_record_2_t result_t;
typedef dh_derivation_record_1_t octets_t;
static uint8_t nibble(char c) {
    if (c>='0' && c<='9') return (uint8_t)(c-'0');
    c=(char)tolower((unsigned char)c);
    assert(c>='a' && c<='f');
    return (uint8_t)(c-'a'+10);
}
static scalar_t integer(uint16_t n,const char *s) {
    size_t len=strlen(s);
    scalar_t x=new_dh_schemes_record_4();
    x->len=n;
    x->word=new_dh_schemes_array_3(n);
    memset(x->word->elems,0,n*sizeof(uint32_t));
    assert(len<=8*n);
    for (size_t i=0;i<len;++i)
        x->word->elems[i/8]|=(uint32_t)nibble(s[len-1-i])<<(4*(i%8));
    return x;
}
static octets_t bytes(const char *s) {
    uint32_t n=(uint32_t)strlen(s)/2;
    assert(strlen(s)==2*n);
    octets_t x=new_dh_derivation_record_1();
    x->length=n;
    x->seq=new_dh_derivation_array_0(n);
    for (uint32_t i=0;i<n;++i) x->seq->elems[i]=(uint8_t)((nibble(s[2*i])<<4)|nibble(s[2*i+1]));
    return x;
}
static bool matches(const uint8_t *v,uint32_t n,const char *s) {
    if (strlen(s)!=2*n) return false;
    for (uint32_t i=0;i<n;++i)
        if (v[i]!=(uint8_t)((nibble(s[2*i])<<4)|nibble(s[2*i+1]))) return false;
    return true;
}
static point_t point(const char *x,const char *y) {
    point_t q=new_dh_schemes_record_7();
    q->finite=true;
    q->x=integer(8,x);
    q->y=integer(8,y);
    return q;
}
static result_t accepted(const char *x) {
    result_t r=new_dh_derivation_record_2();
    r->ok=true;
    r->z=bytes(x);
    return r;
}
int main(void) {
    char family[4];
    unsigned total=0,passed=0,scheme,u;
    static char f[10][4097];
    while (scanf("%3s %u %u",family,&scheme,&u)==3) {
        assert(scheme<7 && u<2);
        bool ff=strcmp(family,"FFC")==0;
        assert(ff || strcmp(family,"ECC")==0);
        unsigned fields=ff?10:9;
        for (unsigned i=0;i<fields;++i) assert(scanf("%4096s",f[i])==1);
        secret_t z;
        if (ff) {
            uint16_t n=(uint16_t)((strlen(f[0])+7)/8);
            domain_t d=new_dh_schemes_record_5();
            d->p=integer(n,f[0]);d->q=integer(n,f[1]);d->g=integer(n,f[2]);
            z=dh_schemes__ff_participant(scheme,u,d,integer(n,f[3]),integer(n,f[4]),
                                          integer(n,f[5]),integer(n,f[6]));
        } else {
            z=dh_schemes__ec_participant(scheme,u,2,integer(8,f[0]),integer(8,f[1]),
                                          point(f[2],f[3]),point(f[4],f[5]));
        }
        const char *expected_z=f[fields-3],*oi=f[fields-2],*dkm=f[fields-1];
        bool ok=z->ok && matches(z->z->seq->elems,z->z->length,expected_z);
        /* An independent copy at the ABI boundary also verifies the two modules
         * agree on the fixed-width Z encoding. Derive from the computed value. */
        result_t input=new_dh_derivation_record_2();
        input->ok=z->ok;
        input->z=new_dh_derivation_record_1();
        input->z->length=z->z->length;
        input->z->seq=new_dh_derivation_array_0(z->z->length);
        memcpy(input->z->seq->elems,z->z->seq->elems,z->z->length);
        release_dh_schemes_record_2(z);
        result_t key=dh_derivation__derive(input,accepted(oi),2,false,bytes(""),strlen(dkm)/2);
        ok=ok && key->ok && matches(key->z->seq->elems,key->z->length,dkm);
        release_dh_derivation_record_2(key);
        ++total;
        if (ok) ++passed;
        else fprintf(stderr,"%s scheme %u role %u differs from KASVS\n",family,scheme,u);
    }
    result_t rejected=dh_derivation__pack_info(4,bytes("01"),bytes("02"),bytes(""),bytes("03"),bytes(""));
    assert(!rejected->ok && rejected->z->length==0);
    release_dh_derivation_record_2(rejected);
    result_t packed=dh_derivation__pack_info(4,bytes("01"),bytes("02"),bytes("abcd"),bytes("03"),bytes(""));
    assert(packed->ok && matches(packed->z->seq->elems,packed->z->length,
           "0000000101000000010200000002abcd000000010300000000"));
    release_dh_derivation_record_2(packed);
    printf("SP 800-56A participant and KDF vectors: %u of %u passed\n",passed,total);
    return total && total==passed?0:1;
}
