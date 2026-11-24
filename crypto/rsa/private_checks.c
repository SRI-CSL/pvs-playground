#include "rsa_random_c.h"
#include <assert.h>
#if __has_include("rsa_kas_c.h")
#include "rsa_kas_c.h"
#include "pairwise_confirmation_c.h"
#endif
typedef rsa_random_record_1_t octets_t;
static uint32_t k;
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) {
    if (s==1) return i&255;
    if (s==3) return i==k-1 ? 3 : 0;
    if (s==2) return i==2*k-1 ? 2 : 0; /* first candidate 0, second candidate 2 */
    return 256;
}
static octets_t read_field(void) {
    unsigned char len[4];
    assert(fread(len,1,4,stdin)==4);
    uint32_t n=(uint32_t)len[0]<<24 | (uint32_t)len[1]<<16 | (uint32_t)len[2]<<8 | len[3];
    assert(n<=2048);
    octets_t b=new_rsa_random_record_1();
    b->length=n;
    b->seq=new_rsa_random_array_0(n);
    assert(fread(b->seq->elems,1,n,stdin)==n);
    return b;
}
static octets_t keep(octets_t b) { ++b->count; return b; }
#define matches(r,e) check_result((r),(e),__LINE__)
static void check_result(rsa_random_record_6_t r,octets_t expected,int line) {
    if (r->valid!=(expected!=NULL)) fprintf(stderr,"Unexpected RSA result in check at line %d\n",line);
    assert(r->valid==(expected!=NULL));
    assert(expected ? equal_rsa_random_record_1(r->data,expected) : r->data->length==0);
    release_rsa_random_record_6(r);
}
#if __has_include("rsa_kas_c.h")
static octets_t literal(const char *s) {
    octets_t b=new_rsa_random_record_1();
    b->length=strlen(s); b->seq=new_rsa_random_array_0(b->length);
    memcpy(b->seq->elems,s,b->length);
    return b;
}
static rsa_kas__context_fields_t context(void) {
    rsa_kas__context_fields_t c=new_rsa_kas__context_fields();
    c->algorithm=(rsa_kas__field_t)literal("A256"); c->u=(rsa_kas__field_t)literal("Alice");
    c->v=(rsa_kas__field_t)literal("Bob"); return c;
}
static pairwise_confirmation__party_t party(const char *id,const char *e) {
    pairwise_confirmation__party_t p=new_pairwise_confirmation__party();
    p->identity=(pairwise_confirmation__element_t)literal(id);
    p->ephemeral=(pairwise_confirmation__element_t)literal(e); return p;
}
static void kas(octets_t n,octets_t e,octets_t d) {
    octets_t pn=read_field(),pe=read_field(),pd=read_field(),one=read_field(),two=read_field(),mac=read_field();
    rsa_random__encapsulation_t u=rsa_random__sve_generate(keep(n),keep(e),2,2);
    rsa_random__encapsulation_t v=rsa_random__sve_generate(keep(pn),pe,3,1);
    rsa_kas_record_3_t nv=rsa_kas__kas1_nonce(1);
    assert(u->ok && v->ok && nv->ok);
    u->count+=2; ++v->count; nv->value->count+=2;
    matches((rsa_random_record_6_t)rsa_kas__kas1_u((rsa_kas_record_6_t)u,context(),nv->value,48),one);
    matches((rsa_random_record_6_t)rsa_kas__kas1_v((rsa_kas__field_t)keep(n),(rsa_kas__field_t)keep(d),
              (rsa_kas__field_t)keep(u->cipher),context(),nv->value,48),one);
    release_rsa_kas_record_3(nv);
    matches((rsa_random_record_6_t)rsa_kas__kas2((rsa_kas__field_t)pn,(rsa_kas__field_t)pd,
         (rsa_kas__field_t)keep(v->cipher),(rsa_kas_record_6_t)u,context(),true,48),two);
    matches((rsa_random_record_6_t)rsa_kas__kas2((rsa_kas__field_t)keep(n),(rsa_kas__field_t)keep(d),
         (rsa_kas__field_t)keep(u->cipher),(rsa_kas_record_6_t)v,context(),false,48),two);
    pairwise_confirmation__element_t key=(pairwise_confirmation__element_t)
        rsa_encoding__part((rsa_encoding_record_1_t)keep(two),0,32);
    ++key->count;
    pairwise_confirmation__element_t tag=pairwise_confirmation__confirm(key,party("Alice","U-data"),
              party("Bob","V-data"),true,true,(pairwise_confirmation__element_t)literal("optional"));
    assert(equal_rsa_random_record_1((octets_t)tag,mac));
    tag->seq->elems[0]^=1;
    assert(!pairwise_confirmation__accept(key,party("Alice","U-data"),party("Bob","V-data"),
                      true,true,(pairwise_confirmation__element_t)literal("optional"),tag));
    release_rsa_random__encapsulation(u); release_rsa_random__encapsulation(v);
    release_rsa_random_record_1(one); release_rsa_random_record_1(two); release_rsa_random_record_1(mac);
    puts("KAS1, KAS2 and key confirmation checks passed.");
}
#endif
int main(void) {
    octets_t n=read_field(),e=read_field(),d=read_field(),ct=read_field(),pt=read_field();
    octets_t label=read_field(),msg=read_field(),wrapped=read_field(),sve=read_field();
    k=n->length;
#if __has_include("rsa_kas_c.h")
    kas(n,e,d);
#endif
    matches(rsa_random__sve_recover(keep(n),keep(d),keep(ct)),pt);
    matches(rsa_random__oaep_random(2,keep(n),keep(e),keep(label),keep(msg),1),wrapped);
    matches(rsa_random__oaep_random(2,keep(n),keep(e),keep(label),keep(msg),0),NULL);
    matches((rsa_random_record_6_t)rsa_encoding__oaep_unwrap(2,(rsa_encoding_record_1_t)keep(n),
            (rsa_encoding_record_1_t)keep(d),(rsa_encoding_record_1_t)keep(label),
            (rsa_encoding_record_1_t)keep(wrapped)),msg);
    matches((rsa_random_record_6_t)rsa_encoding__oaep_unwrap(2,(rsa_encoding_record_1_t)keep(n),
            (rsa_encoding_record_1_t)keep(d),(rsa_encoding_record_1_t)keep(msg),
            (rsa_encoding_record_1_t)keep(wrapped)),NULL);
    rsa_random__encapsulation_t enc=rsa_random__sve_generate(keep(n),keep(e),2,2);
    assert(enc->ok && equal_rsa_random_record_1(enc->cipher,sve));
    matches(rsa_random__sve_recover(keep(n),keep(d),keep(sve)),enc->secret);
    release_rsa_random__encapsulation(enc);
    enc=rsa_random__sve_generate(keep(n),keep(e),2,1);
    assert(!enc->ok && !enc->secret->length && !enc->cipher->length);
    release_rsa_random__encapsulation(enc);
    matches(rsa_random__sve_recover(keep(n),keep(d),keep(n)),NULL);
    rsa_random_record_6_t sig=rsa_random__pss_random(2,0,keep(n),keep(d),keep(msg),1,32);
    assert(sig->valid);
    assert(rsa_encoding__verify_pss(2,0,(rsa_encoding_record_1_t)keep(n),
            (rsa_encoding_record_1_t)keep(e),(rsa_encoding_record_1_t)keep(msg),
            (rsa_encoding_record_1_t)keep(sig->data)));
    assert(!rsa_encoding__verify_pss(2,0,(rsa_encoding_record_1_t)keep(n),
            (rsa_encoding_record_1_t)keep(e),(rsa_encoding_record_1_t)keep(label),
            (rsa_encoding_record_1_t)keep(sig->data)));
    release_rsa_random_record_6(sig);
    matches(rsa_random__pss_random(2,0,n,d,msg,0,32),NULL);
    release_rsa_random_record_1(e); release_rsa_random_record_1(ct); release_rsa_random_record_1(pt);
    release_rsa_random_record_1(label); release_rsa_random_record_1(wrapped); release_rsa_random_record_1(sve);
    puts("RSA private operation, OAEP, RSASVE, PSS and failure checks passed.");
}
