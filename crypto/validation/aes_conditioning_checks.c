#include "aes_conditioning_c.h"
#include <assert.h>
static aes_conditioning__aligned_entropy_t input(void) {
    aes_conditioning__aligned_entropy_t x=new_aes_conditioning__aligned_entropy();
    x->length=32; x->seq=new_aes_conditioning_array_0(32);
    for(unsigned i=0;i<32;++i)x->seq->elems[i]=i;
    return x;
}
static aes_modes__mode_key_adt_t zero_key(void) {
    aes_modes_array_1_t k=new_aes_modes_array_1(16);
    memset(k->elems,0,16);
    return con_aes_modes__mk128(k);
}
static void expect(aes_conditioning__aligned_entropy_t x,const char *hex) {
    assert(x->length*2==strlen(hex));
    for(unsigned i=0;i<x->length;++i) {
        unsigned v;
        assert(sscanf(hex+2*i,"%2x",&v)==1 && v==x->seq->elems[i]);
    }
    release_aes_conditioning__aligned_entropy(x);
}
/* Known answers calculated from independent AES-ECB calls on the input
   sequence 00,01,...,1f using the 90A derivation and 90B/C output lengths. */
int main(void) {
    expect(aes_conditioning__external_df(0,input()),"7dc7788bc064c1d339cb1bccc2ece4e3");
    expect(aes_conditioning__internal_df(0,input()),"7dc7788bc064c1d339cb1bccc2ece4e3");
    expect(aes_conditioning__external_df(1,input()),"17715dc48573a8f7f2f7e9fb5a5a2a17");
    expect(aes_conditioning__internal_df(1,input()),"fd438be261b1daa5454d1943cad79a8351ffb3f74c2cdccd");
    expect(aes_conditioning__external_df(2,input()),"e135bd0a4b68ca33048c5312981607e6");
    expect(aes_conditioning__internal_df(2,input()),"e4e8e7b35cb4044c4985c7d435be7b80b8943d7d6017f4ae9495350fd8aa0ab7");
    expect(aes_conditioning__cbc_condition(zero_key(),input()),"ecc9b00fdb4e6b30e0a7fcf1c08a892c");
    expect(aes_conditioning__cmac_condition(zero_key(),input()),"66431204b3e9ed378019a8f644dd9cab");
    puts("Eight AES conditioning cases passed.");
}
