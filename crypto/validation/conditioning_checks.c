#include "hash_conditioning_c.h"
#include <assert.h>
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) {
    return (stream==1 || (stream==2 && i<40)) ? (uint8_t)i : 256;
}
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) { return 256; }
static hash_conditioning_record_1_t buffer(unsigned n, bool sequence) {
    hash_conditioning_record_1_t b=new_hash_conditioning_record_1();
    b->length=n; b->seq=new_hash_conditioning_array_0(n);
    for(unsigned i=0;i<n;++i) b->seq->elems[i]=sequence?i:0;
    return b;
}
static void expect(hash_conditioning_record_1_t b,const char *hex) {
    assert(strlen(hex)==2*b->length);
    for(unsigned i=0;i<b->length;++i) {
        unsigned v;
        assert(sscanf(hex+2*i,"%2x",&v)==1 && b->seq->elems[i]==v);
    }
}
static void check(uint8_t hash,uint8_t method,unsigned len,const char *hex) {
    hash_conditioning_record_1_t b=hash_conditioning__condition(hash,method,buffer(len,false),buffer(12,true));
    expect(b,hex); release_hash_conditioning_record_1(b);
}
int main(void) {
    check(2,0,32,"fff3a9bcdd37363d703c1c4f9512533686157868f0d4f16a0f02d0f1da24f9a2");
    check(2,1,32,"1d7512271a3d615678a9e6b44b3b6151cc3a3195d789811a3b124477d70dbfcd");
    check(2,2,32,"22968ecbc29b0574db2629cd01c216ea5c3484ec24dcf0b752b862555ff5b705");
    check(3,0,48,"b635441a3721cf190b39d23703c5b77018ff1a56c94f8252ee95c217e3477f093e8ec65c6ae767179a7872c8db9b2141");
    check(3,1,48,"f46337d7e0776d3c68ce823dffdd84eddfee4dc2004638557b5230552a4e4bf01416684ead1b2b337acd2e7ccc3e8181");
    check(3,2,48,"5b74751862cf2a31ca9c861ee06d9f23258cf3b4777d6ec32c97d0fd983513d98d13d670b858146c86f98e4913d7feeb");
    check(4,0,64,"ba51b2a9da2f26fe81fc3ee11524255937ec6bec48835eb437c598c55674e15aa50f88922de7584332a5e4d24787090cb14dfc3abdb39c55aedf6ee108f95354");
    check(4,1,64,"4ae03c7dd08e2a3dde113e700073d84e0182c8179ac422ab69f3b3b5e4f63d1c2c648043d96acb13c3483da7b2a02988d914e9fef3eeb2719621a33c906a7dbc");
    check(4,2,64,"e6b5653ce083b171535812de190b538474368a9210358448443cc2a67a5b91af5edb1277e599a834e5e1cfc27ff971936f11f3da95c396ef4670e23cbea3a7a1");
    check(6,0,32,"0a850ef082abecf9899a6e6c5701649c7a4c41584105315c1bc0628a0f736be6");
    check(6,1,32,"726d6237a31b9729b3d6a1fc1d4604fb1a0cdc3b01957357067e8cba2db7250a");
    check(6,2,32,"e2fceadf84822d574bdd50dcceb2837289c9806f31a52a38b449d63b76b35b41");
    check(8,0,32,"4acbd92d310fc38697084c1bc7a79516a9be20701dae8eb36c643f07f45edbd6");
    check(8,1,32,"c5fd0ea3c17148fcdc0e4f27f06ab3163e7525e09e6fdba6da09a21c806ff2d6");
    check(8,2,32,"e0e18caa4060ce4c3c2ad774eca99710ed2fb083ecdb601fcf1e3fd19cea4998");
    check(9,0,48,"f35855f43ea37f0c41c156ed3b56c8ee337bc2ff343f571952dd26b67019261397eb840a2ffd540aec2623e2d4ab3781");
    check(9,1,48,"8c343619b10d0ae4cafea41180380e12da2cae3786c48f8df95609f8bea76cbd56b1be04b3217d22612cb65d1c1b1978");
    check(9,2,48,"15284e18ef212753f74d006dcacb32864df358380785883b0cb358b2414617d0e27d61fb6a1b164e896c6b7e1299829b");
    check(10,0,64,"06e9c5bde5128b27926b475874b371f7d8352fedd18bf29f9c7c1f7bc1ad267e93fb5562d3e0feb47ce10089ada5b67d6bbb225a5181be3789d539d2368ddcb2");
    check(10,1,64,"a4f5f4dce1e39e8815d992f891df64eae12c15f3e41d5609805d4114afa342f205d17e1a2444bd834399084c166d6124c22f66ca409fc228e9779456039e4236");
    check(10,2,64,"1bb42f6f430dbc2221c012c7f07cf91366b894896a89ed105e0c78ee384fedd69a8c67cd10adb4c7d07540db9dc148c7437f75e2b6e3c7a6c3738a5070a88071");
    hash_conditioning__conditioned_t r=hash_conditioning__full_entropy(2,0,buffer(32,false),1,257);
    assert(r->success);
    expect(r->data,"5faa4eec3611556812c2d74b437c8c49add3f910f10063d801441f7d75cd5e3b00");
    release_hash_conditioning__conditioned(r);
    r=hash_conditioning__full_entropy(2,0,buffer(32,false),2,257);
    assert(!r->success && r->data->length==0);
    release_hash_conditioning__conditioned(r);
    puts("All 21 hash conditioning cases, partial-bit collection and failure checks passed.");
}
