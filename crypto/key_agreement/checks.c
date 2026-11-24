/* NIST CAVP KAS 2016 FFC and ECC no-key-confirmation vectors; RFC 6979
 * Appendix A.2.1, DSA-1024 verification with SHA-256 and message "sample". */
#include "ff_agreement_c.h"
#include "ff_groups_c.h"
#include "ec_mqv_c.h"
#include "dsa_verify_c.h"
#include <assert.h>
#include <ctype.h>

static unsigned digit(char c) {
    if (c>='0' && c<='9') return (unsigned)(c-'0');
    c=(char)tolower((unsigned char)c);
    assert(c>='a' && c<='f');
    return (unsigned)(c-'a'+10);
}
static ff_agreement_record_1_t integer(uint16_t n,const char *s) {
    size_t length=strlen(s);
    assert(length<=8*n);
    ff_agreement_record_1_t x=new_ff_agreement_record_1();
    x->len=n; x->word=new_ff_agreement_array_0(n);
    memset(x->word->elems,0,n*sizeof(uint32_t));
    for (size_t j=0;j<length;++j) x->word->elems[j/8]|=(uint32_t)digit(s[length-1-j])<<(4*(j%8));
    return x;
}
static void matches(const uint8_t *data,size_t n,const char *s) {
    assert(n*2==strlen(s));
    for(size_t j=0;j<n;++j) assert(data[j]==(16*digit(s[2*j])+digit(s[2*j+1])));
}
static ff_agreement__domain_t domain(const char *p,const char *q,const char *g) {
    uint16_t n=(strlen(p)+7)/8;
    ff_agreement__domain_t d=new_ff_agreement__domain();
    d->p=integer(n,p); d->q=integer(n,q); d->g=integer(n,g); return d;
}
static void ffc(bool mqv,const char *p,const char *q,const char *g,const char *x,const char *r,
                const char *y,const char *t,const char *expected) {
    ff_agreement__domain_t d=domain(p,q,g);
    uint16_t n=d->p->len;
    ff_agreement__result_t z=mqv?ff_agreement__mqv(d,integer(n,x),integer(n,r),integer(n,y),integer(n,t)):
                                  ff_agreement__dh(d,integer(n,x),integer(n,y));
    assert(z->ok); matches(z->z->seq->elems,z->z->length,expected); release_ff_agreement__result(z);
}
static ec_mqv_record_2_t affine(uint16_t n,const char *x,const char *y) {
    ec_mqv_record_2_t q=new_ec_mqv_record_2();
    q->finite=true; q->x=(ec_mqv_record_1_t)integer(n,x); q->y=(ec_mqv_record_1_t)integer(n,y); return q;
}
static void ecc(uint8_t curve,uint16_t n,const char *s,const char *e,const char *sx,const char *sy,
                const char *ex,const char *ey,const char *expected) {
    assert(ec_mqv__full_public_valid(curve,affine(n,sx,sy)));
    ec_mqv_record_6_t z=ec_mqv__mqv(curve,(ec_mqv_record_1_t)integer(n,s),(ec_mqv_record_1_t)integer(n,e),
                                     affine(n,sx,sy),affine(n,ex,ey));
    assert(z->valid); matches(z->value->seq->elems,z->value->length,expected); release_ec_mqv_record_6(z);
}
static void dsa(const char *p,const char *q,const char *g,const char *y,const char *r,const char *s,const char *hash) {
    uint16_t n=(strlen(p)+7)/8;
    for (unsigned alteration=0;alteration<2;++alteration) {
        dsa_verify_record_3_t h=new_dsa_verify_record_3();
        h->length=strlen(hash)/2;
        h->seq=new_dsa_verify_array_2(h->length);
        for (uint32_t i=0;i<h->length;++i) h->seq->elems[i]=16*digit(hash[2*i])+digit(hash[2*i+1]);
        h->seq->elems[0]^=alteration;
        bool ok=dsa_verify__verify((dsa_verify_record_4_t)domain(p,q,g),(dsa_verify_record_1_t)integer(n,y),
                                   (dsa_verify_record_1_t)integer(n,r),(dsa_verify_record_1_t)integer(n,s),h);
        assert(ok == (alteration==0));
    }
}
int main(void) {
    /* KASValidityTest_FFCMQV1_KDFConcat_NOKC_init.fax, COUNT 4 */
    ffc(true,
        "a767083605e3ec0bca252ac9a2106dced20fe16eb3236cd79f8ff1d543e6969edf4aa06c432ae8504f5db67fa0f54acb8d6f36fe2d64a7ead26895a8e24606604ec0aff5f31327a2fec732c3ba4c3ddee6e50cc0318e2c7facb694f2d71a22ad97a500196e459c60d670280163bd5f11c6f80a67b56b20d87145e3b11015a7e2f090d81ca65fb97f3a2523fe3a47559651e4b03b599b363b9a78e62bf8ab67f657e545722c5372d8e22dc073abf009065032a02f3362981dbe402656856dbda4421fe5b14c9402820065f6c66d43edc97a581f5cd53748ba51c0f29779041c13b67bbe6077cb90a205cf20abd9b424cfc2e9cf788f52aa5c41206d015c321d43",
        "b1b6763b3a80ff88d040211ffb88ff738fca5c695afab6d81256f633",
        "0c4799e69534512c79b1f8655883e3ad8d7cf19b607ba04a33ee68327e910d669df3c83b54ac08050ea5d4dfcc4b8caa4974730a39506f4056765123a992c65ba384be9ba2d661a9b5f05d518d7071f4de8267a396a144ffd71aecc94496ac5c9493cb02bd21b06deb8ecc9eb0a855a597229c5ada597e3bc74dcf53180929c0f8eea0e88790314c837ed5bf016bd0ba9543d0c2e65ea968b0df7171037e7df565192d6fd5f1f6db1da7cd7c5a79b3ef564f72629325d5ae56aa24331b77be766fb6c5921c82eec16341f67dd4e1fc1e14fe8810007e8473e2b5b43c730181871d23b5885bca77ada994c4e71e9f8f881c1c4229b0fb10577cd2b38aa4a4edbb",
        "797aac4d1dfb3412af2ae85629fc3d0c1f225f048179bfcfd7156e06",
        "04ff973d33f9c3df575e75a9f6c4e9d5fbf19e496ba5c83aa77b7afc",
        "9026a630324255b5b495716da0afd1eab4645b651fc54998b2a89b117a1af58b8080fcb5fcacbe37c1ce61df0f28bf2bbdb1b4732144b491fce0cd36cff7d15891716dbca5c97f0cde5270835d73b8a7dba5176505868ac9a060ba458abd233487cfd163925aff2fe38ea07a40c94423b09c67a2b34815b53eed045cf39d70ed6a4ae95275c2102830d9cdd464753c4490e7d680c2ef47e64c7b4124038ade17b4e76a3cb95a4901de3edc728441c6c4157d5e08a5b178f294129c6cce52f910107206d65a7d20e4e11d3184fb44d49884cc79f1290f4f086348051ec8a0180d904f2e97b6117a27fa5ac7dd3123998fe37f27cd314524375780e334c22a409e",
        "9026a630324255b5b495716da0afd1eab4645b651fc54998b2a89b117a1af58b8080fcb5fcacbe37c1ce61df0f28bf2bbdb1b4732144b491fce0cd36cff7d15891716dbca5c97f0cde5270835d73b8a7dba5176505868ac9a060ba458abd233487cfd163925aff2fe38ea07a40c94423b09c67a2b34815b53eed045cf39d70ed6a4ae95275c2102830d9cdd464753c4490e7d680c2ef47e64c7b4124038ade17b4e76a3cb95a4901de3edc728441c6c4157d5e08a5b178f294129c6cce52f910107206d65a7d20e4e11d3184fb44d49884cc79f1290f4f086348051ec8a0180d904f2e97b6117a27fa5ac7dd3123998fe37f27cd314524375780e334c22a409e",
        "7c0afe78a0767607d3574f4d7c2fb4ce926c5c0fa444b5bdfa81aa54797f59f2e88fc1406e3745ebb5908fb1940db1346d135307aaee4a37e915b6c144a780650778479acef6dda2b57a125f9031c02eb050283654dcd6ac3d4256acdf22244d5e97d096b9d584d15588a0ff1f50ef8bcbb1c61caa0d8814e7c946598755ea2e3c635af371bbc336cb9a672677c7490068428cd7589584d1fa62968a73b431eae9f12ac3fd9e877017b8b132e2b88c733972720eaa9368e90e8d455b75ecad474ae289b5ce542ca7cf1b779141bce7969b44abedb1a4c403eb1f2a3c73d14e095c3c04b9456ce2b2536918a9c0e46b9b0b921a0dd3fef91e4d3fe76a1f564d62");
    /* KASValidityTest_FFCMQV2_KDFConcat_NOKC_init.fax, COUNT 1 */
    ffc(true,
        "f127aed13b8097516103ce4d724828fd7703a83f02088d2fed33b1ecba84d0fba96717633211b63e1cff928721416365bc0e114fbaef0ef7e441efab7ecb7b7b31ecb2a665514ef1e4a8baa3c6c5309fef5ee361efba7ef498c50520394ce9868d7d54550993208e0a84c2e946b92f556200ac68865473a686360e8b887a85518112d6ef94176849737a67c4b6a060f7446960ad74350ad2325e05bf0168a79169280121c2f2b57b8ad40480b862c03696574123fc22e5a21fbec5b1a84a3b095997ae2dc1f5870b5a5f37ce4f7653d94268524ea693b0aed3a99e651c39be70785a2afe6766ae08f0bf0377cfbea3eb36601f66272c2637b1a48f6e02a93663",
        "a7a8890f303a3f93ddc50239339c8d878840414ab94a305da2f6c0f5",
        "18c18042ae82b1c5e4db0ef668921803d68257becc73989137d52956d0a35f9e31e4c9ce41b5a7537d6ad63124b2b21e0b4121e4e786f78692df64eee81f38f7b1f1fc7ddd69bee960f91a46c8bc5b0d8595cb9a2e4ee1dc22242c813b4ad0d5581fdac0126f233a246e6cdb65a31a3b04c49dae8687e44b2a4a2e1800182a1d7a46f15b6ddd0d949d79f869649578b249d726689cd1494e13f612b9a98389381f9141cb1fe0dd528277ceaafc5254e799d0a65e74d976a8f609621e736062ae5e209cd239ec128e9481ad439b18a78b9913c6df8d1600ebd3c5ec9fda3047d377b4dd2f0097a2175a49ccc45b7d2541dc334dde3447d3617f4e3a1db5947dc8",
        "58ed320e81f45569f31b1db4fa521cbec8756a278658ed10d90a2099",
        "192ffe21ff0c413d98863b978d70b21724033f22326d78c6480be4c4",
        "6abf4e24a7a756ea478b3978629be7b6fa3a3954ef199a2fbe605dcc3c5418bcfa0ac3d4151feaed820d98332b53f3932cf4518f7ad48c8eab7dfdc0328a3b35b00f39936a1968e9081700e03d17ec9982005ac7fa87fd0a54fd941516cdc5bc5a003919433ae7d1b7db9865986a47e4091304ceea95d689958c20d46939ee96157f81485bb419c129f249049bd9372aeeb5bf7a9a942b1dc6c2d28cb35d6ec0e82b96d4734dc7d77bbc06336844f234f44034f17f3d3c1a6f54a079ff2b9847b886f9139c462d79a2142f78ebfcdc25f979fce78b5dd90dbe3397ecca5429eb063b3637cc4e8f2aa792b208935542795b0b8873a2dce56208d740092c1189a1",
        "3e893b0d86053c10b2f2e261cf937cd6f92a4862670594064a50d64c4bd32f33f112e683b05e507200faf91b0889fb5036aefbed9cfdf3c114bdabe2a327c171b087f0f8028d5d306c64e7cb7e432d6a83347a4efec30d823a2bd0fc7430b667da61e45535e3b01755b7300341c238350b7789348f478cf1c3e0250ebfe63e1879b482faaeffd167a4fd8db464bbca22754d4236228f81bbd2c727b9b85a6682cbf4453a1219af169491b12c5ceba8001ed28e5e623757ac4fbfa116d70a3322ed4435859d060091aa5f1f265f2cd107a82f298dc9733f08c7a5ec694418cede121262f6640e1a9bfd87bb9847b071687e19aacc7319204129e3522a4d86856e",
        "093a7ecfb40d809a7725cad627270872634e7e2e77acb7283372ed79704c85bf280e7e156066da78622b1f787b45d41efcfb35892925b204e5c201b27c0e38054db763477dd9beae965afe5620e815390ca2b9cbda7635f71ba61bdc66bdd1a6a56c85c0751245d403bd37511b4b1b6afe878cf41cbbff4dc8e8b9ddcdf66f32fe436365f909191fa5c30637f322a03b8110f0d807c4619a5478ab8bfa98c3aaa197971abf1d3e25d9a608ae568295b38226bfd301b207ae0ee78e3aa14f0adf598a9f7fbd8c83a4fc0362e0ee0f577915023a111f783b6b7cb7f5edbe6115d29958e34cf710410e8e17f715d59c973ff357d2007147a0120eb7eae067f808a0");
    /* KASValidityTest_FFCStatic_KDFConcat_NOKC_init.fax, COUNT 1 */
    ffc(false,
        "81f15dff1873890c3fdc70ec6615c2c19c1c95cf7f5731669c7a6b42ca6c2bae4369518538c07cb4aa3601eb628161549be2dfe4f69add71c9f1c6340cc514cda1f906883c3a3e55a2840e4bdf2cf81b040fb9bfe4cd597f85ebae1f0b4114532e43fbc5b0e4e958d8ddddf29de886157d85dc401ae96cf9538d5adc53e0d603aa127fa030712fe5e779d31c39bfa892030cddcc50988fbeb8d02ebb904d4401e234d5f3bc50c8dff1e445995edc3417b253f942498e481125f60e48f4eb226774f1b6d666423eaceb066c9edf9284fa0469c1709017f20c8f50df14c5b0b2d8a763f73d7dfcd2dc9da7688aa2fdef3cd9c31b0f6b0c21daf4ceaef28789bfeb",
        "cc2c1d163a3e0aea348825e0689af896133dc401a823f59c121e7af3",
        "5941d1178d593f2f404f8f1b1b162cebbaa787d55666edecbd5071dece793d4de1197a19c993ff98d10a5f1c99976077cde0739953db74d50b6fbd6c864d1917085c81f89e0c2a0fa7186992da10fa0bd52494a97a6b36ad6291872a9d1663cf710426f858b23cb510a2494e6fa17ca18ac735890e44a7c579861e3ad778071b15bb2ab8b75e1ca0507e22775ae38290dfed0fcf5d4f0df5fe40ab10967a4dbcdc118aad51dfaf675a274ff4c54652b5ca6da913c141cb158242203f48fae4d78cfd5b94b180e84585d45c7e692d83369c8dae07fb6308a05164ac1854743bc7764e74aca434a40f7f063a04d0f95b501e02045341234658d9c657048b200c3b",
        "4e0f5416ee270385fc2244bdf3405902b505362df56d39378f74b326",
        "",
        "3b071528d852ee6cc08ea58d22e84f0bd416104be2c1278f0ad9139dafcce67c372ee52da9103aeb7dc53c433b9d86a5b10aafe186fa2de8efd444d30b850f310ffb3cdbbe2cb5e7944370c7b02dd962d88521519982dcf49e7921e0f766ad9b2eacfe6ecde37060d0cefed7462be640effa88bf1ad45e2874e22142cae052d7aff505e77d47a178c84893fe92361fcdb73aee9700206c65179fde46de15bcaf56a1b7c5348d0f7880578a15372ebb8c335d82f022e86412b979a137acb69ccd1f42dae383c7e8326b3609b236e7c976a74f56a7d8e1a542734fdb83c733c6fbbf66d3ce44a5ec773624088b4895f0a648aaac37b897f67af894855c8f1240c6",
        "",
        "05aae6798a2bcb6985e5c774765b4265d23c1415a5569f56ff1ac8c659afbbdf1041f636c0c7c244ccd45ea46f9ceae79e3474514911cc836addb3a8196bf76eee20f8b70229c8fcc5dd20629898e8dca24209908a647efb892d2f056dd7906d2f1c34b673968121918b86b3a8111a61f43e09979231b6bc7f482cd262a5d379e0099f3836fca48395effe7b1cca62a770bbdab52cc91bdddcdba95fdb539ab3104276c2eb6ae6d366af969e447643ddf66ed7376b6aea618a65b9c7aaf7985e7ed690c4bce1fd3fd72dbd5d99d524c7cd575fd80e80b683259f9931c3cf064a67ff3cbda2e8cb1461d4fcd0a2377251d773a6f3521ca1e5b65cee71f4c67b92");
    /* KASValidityTest_ECCFullMQV_KDFConcat_NOKC_init.fax, P-256 COUNT 9 */
    ecc(2,
        8,
        "4472b2c51176de5ec63390e7ee11cfd0d4a01e0bf1f2168caa1c9de6ad51f48f",
        "361ffd0194ef12a0d41174963d1bf2985ad3d58831a1c6963a8e715f783b8952",
        "ceec572058f7702f0cd96119457dd02abc53b95a419c1754fc442c6f2215b758",
        "413b59688b99f747f69787a514cd2222a2bb1d21e0d87570f7cffbf57e1ca79b",
        "9b9b5d9acb74cf5d08d603f2c69729d72f959a118470c2573e320f3c954fb1bf",
        "693cd48bb44e45efb96f072036d9b8b83849630b864756eb58a9aad8f9cdd47f",
        "c507fc3238852bf8144621fcaaf5928169ea230d0cd1673fdbc152c3514481f8");
    /* KASValidityTest_ECCOnePassMQV_KDFConcat_NOKC_init.fax, P-256 COUNT 3 */
    ecc(2,
        8,
        "c22439872b3733ba68c779091c4fd9938a5d65a7d19e44487defb7e510fc6459",
        "586c67e7d4045bb541288d7ead6ee86aebec4bc64fd02e411450cd41f3274c70",
        "f7e73cd1dfeb1d5784fa85f506c0c408493bdf80ad78964386285c0abb9d260f",
        "d2fbddb2eb2143528c06ab7b9c094d0eb8f006a76cb0056cdbe398f139456c30",
        "f7e73cd1dfeb1d5784fa85f506c0c408493bdf80ad78964386285c0abb9d260f",
        "d2fbddb2eb2143528c06ab7b9c094d0eb8f006a76cb0056cdbe398f139456c30",
        "b54073b4377ba9a40329457434f670b708fd52c2147f039446c52ba118a323db");
    /* RFC 6979 Appendix A.2.1 */
    dsa("86F5CA03DCFEB225063FF830A0C769B9DD9D6153AD91D7CE27F787C43278B447E6533B86B18BED6E8A48B784A14C252C5BE0DBF60B86D6385BD2F12FB763ED8873ABFD3F5BA2E0A8C0A59082EAC056935E529DAF7C610467899C77ADEDFC846C881870B7B19B2B58F9BE0521A17002E3BDD6B86685EE90B3D9A1B02B782B1779",
        "996F967F6C8E388D9E28D01E205FBA957A5698B1",
        "07B0F92546150B62514BB771E2A0C0CE387F03BDA6C56B505209FF25FD3C133D89BBCD97E904E09114D9A7DEFDEADFC9078EA544D2E401AEECC40BB9FBBF78FD87995A10A1C27CB7789B594BA7EFB5C4326A9FE59A070E136DB77175464ADCA417BE5DCE2F40D10A46A3A3943F26AB7FD9C0398FF8C76EE0A56826A8A88F1DBD",
        "5DF5E01DED31D0297E274E1691C192FE5868FEF9E19A84776454B100CF16F65392195A38B90523E2542EE61871C0440CB87C322FC4B4D2EC5E1E7EC766E1BE8D4CE935437DC11C3C8FD426338933EBFE739CB3465F4D3668C5E473508253B1E682F65CBDC4FAE93C2EA212390E54905A86E2223170B44EAA7DA5DD9FFCFB7F3B",
        "81F2F5850BE5BC123C43F71A3033E9384611C545",
        "4CDD914B65EB6C66A8AAAD27299BEE6B035F5E89",
        "af2bdbe1aa9b6ec1e2ade1d694f41fc71a831d0268e9891562113d8a62add1bf");
    for (uint8_t i=0;i<10;++i) {
        ff_groups_record_2_t d=ff_groups__named(i);
        /* Compare every modulus byte in RFC big-endian order. The reference
         * fingerprints are from OpenSSL's independent named parameters. */
        static const uint64_t modulus_fingerprint[10]={
            UINT64_C(0x21c4cbb4f90c4900),UINT64_C(0xba273df6551e5977),
            UINT64_C(0xddcf17b371acbee2),UINT64_C(0xda4b93b5facc19cf),
            UINT64_C(0xfcb5a9b4be6d4540),UINT64_C(0x5a35be665eda29ec),
            UINT64_C(0x0edbb29ece01f4f7),UINT64_C(0xb9173e0df6116867),
            UINT64_C(0x525f317e1f681155),UINT64_C(0x448c986290e207fd)
        };
        uint64_t hash=UINT64_C(0xcbf29ce484222325);
        for (size_t j=d->p->len;j>0;--j) {
            uint32_t word=d->p->word->elems[j-1];
            for (unsigned k=0;k<4;++k)
                hash=(hash^(uint8_t)(word>>(24-8*k)))*UINT64_C(0x100000001b3);
            uint32_t q=word>>1;
            if (j<d->p->len) q|=d->p->word->elems[j]<<31;
            assert(d->q->word->elems[j-1]==q);
        }
        assert(hash==modulus_fingerprint[i]);
        assert(d->p->word->elems[0]==0xffffffff && d->p->word->elems[d->p->len-1]==0xffffffff);
        assert(d->g->word->elems[0]==2 && d->q->word->elems[d->q->len-1]==0x7fffffff);
        assert(!ff_agreement__public_valid((ff_agreement__domain_t)d,integer(d->p->len,"1")));
    }
    puts("SP 800-56A DH, MQV and legacy DSA verification examples passed.");
    return 0;
}
