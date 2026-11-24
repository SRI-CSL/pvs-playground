/* SP 800-135r1 ASKDFVS response files, COUNT=0 for the selected algorithms.
 * Tests call generated C at the public protocol interfaces. */
#include "protocol_kdf_c.h"
#include "tls_legacy_prf_c.h"
#include <assert.h>

static void decode_hex(uint8_t *out,const char *s,size_t n) {
    for (size_t i=0;i<n;++i) {
        unsigned b;
        assert(sscanf(s+2*i,"%2x",&b)==1);
        out[i]=(uint8_t)b;
    }
}
static protocol_kdf__field_t bytes(const char *s) {
    size_t n=strlen(s)/2;
    protocol_kdf__field_t x=new_protocol_kdf__field();
    x->length=n;
    x->seq=new_protocol_kdf_array_0(n);
    decode_hex(x->seq->elems,s,n);
    return x;
}
static void expect(protocol_kdf__field_t x,const char *s) {
    protocol_kdf__field_t y=bytes(s);
    assert(x->length==y->length && memcmp(x->seq->elems,y->seq->elems,y->length)==0);
    release_protocol_kdf__field(x);
    release_protocol_kdf__field(y);
}
static tls_legacy_prf_record_2_t legacy_bytes(const char *s) {
    size_t n=strlen(s)/2;
    tls_legacy_prf_record_2_t x=new_tls_legacy_prf_record_2();
    x->length=n;
    x->seq=new_tls_legacy_prf_array_1(n);
    decode_hex(x->seq->elems,s,n);
    return x;
}
static void tls10(const char *secret,const char *label,const char *seed,uint32_t n,const char *expected) {
    tls_legacy_prf_record_2_t x=tls_legacy_prf__tls10(legacy_bytes(secret),legacy_bytes(label),legacy_bytes(seed),n);
    tls_legacy_prf_record_2_t y=legacy_bytes(expected);
    assert(x->length==y->length && memcmp(x->seq->elems,y->seq->elems,y->length)==0);
    release_tls_legacy_prf_record_2(x);
    release_tls_legacy_prf_record_2(y);
}
static protocol_kdf__session_fields_t sa(const char *ni,const char *nr,const char *ci,const char *cr) {
    protocol_kdf__session_fields_t s=new_protocol_kdf__session_fields();
    s->ni=bytes(ni); s->nr=bytes(nr); s->ci=bytes(ci); s->cr=bytes(cr);
    return s;
}
static void ike1(unsigned auth,const char *ni,const char *nr,const char *ci,const char *cr,
                 const char *z,const char *psk,const char *id,const char *d,const char *a,const char *e) {
    protocol_kdf__session_fields_t s=sa(ni,nr,ci,cr);
    protocol_kdf__field_t x=auth==0?protocol_kdf__ike1_signature(0,s,bytes(z)):
                            auth==1?protocol_kdf__ike1_public_key(0,s):
                                    protocol_kdf__ike1_preshared(0,s,bytes(psk));
    expect(x,id);
    protocol_kdf__ike1_keys_t ks=protocol_kdf__ike1_sa(0,sa(ni,nr,ci,cr),bytes(z),bytes(id));
    ks->derivation->count++; expect(ks->derivation,d);
    ks->authentication->count++; expect(ks->authentication,a);
    ks->encryption->count++; expect(ks->encryption,e);
    release_protocol_kdf__ike1_keys(ks);
}

int main(void) {
    ike1(0,
         "ced5635da6796075",
         "6244b427712fb776",
         "382e5c8b0a3fa307",
         "ba4b7616700a2413",
         "2a2e0bbe8da3657a83f3d35826e49e2d38e557e912a1b9e6c30c63577b3eab715466202862027f2c26f3090743555579611771db0b92bef93834432a3a7762fc8a0f4889fd281d6082770d10a40d7bad61e832f041e620d6787e7f62ab2861ddfbe272e0d9d3cdec5f1bbf750e24b8b32d6d714968ad69ce5086c32ad2742ebc",
         "",
         "dc37ac99de6dcfbd1ee74af7fb36f9b4b0a7829d",
         "486293ed547adb562cefdaf43d3d8457b196f2b6",
         "f4053b5ca07e59bb41b8f401037ca90b72b3917e",
         "49a1d53a80fb77e663552964fbbcb45092021473");
    ike1(1,
         "fdaa0e5dacb97021",
         "6f46779e8bfab62d",
         "890511bb8239cf37",
         "338e184c904b8439",
         "f065141de4253a27dd0e01d10d58111c04f475e845d94435d8f3d84a3af8d6d3c6e2762381eea2f0f7a4ebe63a7f33b7ef02b750e0b508572883ae8acf2f27b6f41513beb0ce11014c3939075558ed1fbda6bbcd2997076a74157b62adb87f0b1d31c6d4e439e4d346db97f39de64b533c65db9e7703cbc05d8cde49f1e80621",
         "",
         "aae05d34e6162ebd6d35b3b70f7eb0b61d4ad4b6",
         "d8d40b40ecb2c6d3b59e7b515dd92f977e87f96e",
         "fc22eabab561ece6bb789a266376812e2942211d",
         "8a1e83faaca3b671256c765f44abf92f995abae9");
    ike1(2,
         "6573fc1ec61d462c",
         "2d3bd83db404ce97",
         "b084646b3b7794ae",
         "116a5a5a11429a93",
         "34979d466c575cb49e585f7d3a5e55e84033b6399c4aabfd4622e8c3f978e960e495ee99ec850cb102123325a40dceaed2b5ca61175d8e0a508ef62c27de1da937fd8fefabe722c233f15cd68152445c307430f071e522851d0da43f3e5c659a5a5a3131795655dcfed4b55330dc7d3786154fb34cab0af19207719fcbf818cf",
         "82",
         "3eeb098da1b0472cf80aea52ac5f0370170b4583",
         "28bbade89035d8716dc7eeb6b9f278a9d2e7f804",
         "edde1bd2bce2e3a8e5615ce89a38e8cde7246d81",
         "1e4c3b07adb7710a20ab0addc5a452b0752f64c2");
    expect(protocol_kdf__ike2_seed(0,bytes("3651fef5c9c35e93"),bytes("c09a8b90a3f04d59"),bytes("d084a30166a50fb7325c3960874a839449ef9741c2f4f947d0201dd8c1269273d79509f37e3ca3eb4fa2fe2a28254e289cd3f34dad4eb4df1a07685a4b8a94fa61e2491f7598b3ce65547ff133b3f63d1ac4175eaa695033f3cedb026a6873a36455172a8540b8a5d23a0143bed0390ee49b168269d75fffee9fb62be965993c")),
           "cd2e8050137832245f1dbacc6e4f0a92f94d45d6");
    expect(protocol_kdf__ike2_sa(0,bytes("cd2e8050137832245f1dbacc6e4f0a92f94d45d6"),bytes("3651fef5c9c35e93"),bytes("c09a8b90a3f04d59"),bytes("8e5c3ae507221684"),bytes("b1f201bb155c3acd"),132),
           "6f1b12cad3cbe097b35430356d869d54cddb0198ec859174d53ceb92dddedbe2436db69f60977c58fa63bbb667f8d36920b109baae8f6c61a9ac49feda01843225d080ec5539d5881a25521ffb2a0a91874a9c0a27fcc2d717eb8963a9e3a89c7ab264757284c28cf8c3ca40576f4220b052b1fb8e9ad60ba3c80557323331a8cbb89f20");
    expect(protocol_kdf__ike2_child(0,bytes("6f1b12cad3cbe097b35430356d869d54cddb0198"),bytes(""),bytes("3651fef5c9c35e93"),bytes("c09a8b90a3f04d59"),132),
           "4727dc0ef94eb326ce131cf282fb652faa638ad0ddae3786a11bcc0309876009f8c485de011ad962c5b1ca8a41ff8145445749079c5686e26ffebbc342f06981f3da745e11ca0976424d1f8caec623d59dc7186deb20a27b411d1dcb70a365440bf7de905088b0692e8addc094e18d1939bdb67e89798ca6b239e2ccb81c2409dac0106c");
    expect(protocol_kdf__ike2_child(0,bytes("6f1b12cad3cbe097b35430356d869d54cddb0198"),bytes("52f00ab174c25d5b7139ae5ff4e8e9eddee5992d2e36adf8a559ffd90dab1442e4fbe429d320c0f33552a17d1557fa41ea70e8fb916c4fa27ed52b5f8ebd8461afa78f1159159a64055ac5f6319e29c28eae58cbc6847770f32c3fed1d04750484f854790f95e9ec01bc5bc461f24966462e359511329305038e94deb6dd42c2"),bytes("3651fef5c9c35e93"),bytes("c09a8b90a3f04d59"),132),
           "b109c21ad4c0797768c1cec9e63554681e48f224bca7f23c20c4ea7041983451e9aa1d5408656c8a975ff1b9d9a12c75ffeb64bdecb30174664cccb4e14f1c377b7f6d1525af77c7092aac3e47f917ebae8297fb5539d2008ce830823a09cc197361d4a289c72745f6ce9fefe812be5bf55b3200fbb82e41a4a40877d3fe106db909707b");
    expect(protocol_kdf__ike2_rekey(0,bytes("6f1b12cad3cbe097b35430356d869d54cddb0198"),bytes("52f00ab174c25d5b7139ae5ff4e8e9eddee5992d2e36adf8a559ffd90dab1442e4fbe429d320c0f33552a17d1557fa41ea70e8fb916c4fa27ed52b5f8ebd8461afa78f1159159a64055ac5f6319e29c28eae58cbc6847770f32c3fed1d04750484f854790f95e9ec01bc5bc461f24966462e359511329305038e94deb6dd42c2"),bytes("3651fef5c9c35e93"),bytes("c09a8b90a3f04d59")),
           "3b03bce748c96d5e8306918d2ff89b68f0648da3");
    expect(protocol_kdf__x963(0,bytes("1c7d7b5f0597b03d06a018466ed1a93e30ed4b04dc64ccdd"),bytes(""),16),
           "bf71dffd8f4d99223936beb46fee8ccc");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),65,8),
           "e2f627c0b43f1ac1");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),66,8),
           "58471445f342b181");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),67,24),
           "1ca9d310f86d51f6cb8e7007cb2b220d55c5281ce680b533");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),68,24),
           "2c60df8603d34cc1dbb03c11f725a44b44008851c73d6844");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),69,20),
           "472eb8a26166ae6aa8e06868e45c3b26e6eeed06");
    expect(protocol_kdf__ssh(0,bytes("0000008055bae931c07fd824bf10add1902b6fbc7c665347383498a686929ff5a25f8e40cb6645ea814fb1a5e0a11f852f86255641e5ed986e83a78bc8269480eac0b0dfd770cab92e7a28dd87ff452466d6ae867cead63b366b1c286e6c4811a9f14c27aea14c5171d49b78c06e3735d36e6a3be321dd5fc82308f34ee1cb17fba94a59"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),bytes("a4ebd45934f56792b5112dcd75a1075fdc889245"),70,20),
           "e3e2fdb9d7bc21165a3dbe47e1eceb7764390bab");
    tls10("bded7fa5c1699c010be23dd06ada3a48349f21e5f86263d512c0c5cc379f0e780ec55d9844b2f1db02a96453513568d0","6d617374657220736563726574","e5acaf549cd25c22d964c0d930fa4b5261d2507fad84c33715b7b9a864020693135e4d557fdf3aa6406d82975d5c606a9734c9334b42136e96990fbd5358cdb2",48,
           "2f6962dfbc744c4b2138bb6b3d33054c5ecc14f24851d9896395a44ab3964efc2090c5bf51a0891209f46c1e1e998f62");
    tls10("2f6962dfbc744c4b2138bb6b3d33054c5ecc14f24851d9896395a44ab3964efc2090c5bf51a0891209f46c1e1e998f62","6b657920657870616e73696f6e","67267e650eb32444119d222a368c191af3082888dc35afe8368e638c828874bed58a7b1cd4fedaa232159df652ce188f9d997e061b9bf48e83b62990440931f6",104,
           "3088825988e77fce68d19f756e18e43eb7fe672433504feaf99b3c503d9091b164f166db301d70c9fc0870b4a94563907bee1a61fb786cb717576890bcc51cb9ead97e01d0a2fea99c953377b195205ff07b369589178796edc963fd80fdbe518a2fc1c35c18ae8d");
    expect(protocol_kdf__tls12(2,bytes("f8938ecc9edebc5030c0c6a441e213cd24e6f770a50dda07876f8d55da062bcadb386b411fd4fe4313a604fce6c17fbc"),bytes("6d617374657220736563726574"),bytes("36c129d01a3200894b9179faac589d9835d58775f9b5ea3587cb8fd0364cae8cf6c9575ed7ddd73e1f7d16eca115415812a43c2b747daaaae043abfb50053fce"),48),
           "202c88c00f84a17a20027079604787461176455539e705be730890602c289a5001e34eeb3a043e5d52a65e66125188bf");
    expect(protocol_kdf__tls12(2,bytes("202c88c00f84a17a20027079604787461176455539e705be730890602c289a5001e34eeb3a043e5d52a65e66125188bf"),bytes("6b657920657870616e73696f6e"),bytes("ae6c806f8ad4d80784549dff28a4b58fd837681a51d928c3e30ee5ff14f3986862e1fd91f23f558a605f28478c58cf72637b89784d959df7e946d3f07bd1b616"),128),
           "d06139889fffac1e3a71865f504aa5d0d2a2e89506c6f2279b670c3e1b74f531016a2530c51a3a0f7e1d6590d0f0566b2f387f8d11fd4f731cdd572d2eae927f6f2f81410b25e6960be68985add6c38445ad9f8c64bf8068bf9a6679485d966f1ad6f68b43495b10a683755ea2b858d70ccac7ec8b053c6bd41ca299d4e51928");
    expect(protocol_kdf__tpm12(bytes("fd771b263f6be051a1d7eb0c5138fbfcafbd49de"),bytes("6b8790fd56b2b74734ea97db727ac9eb16e69831"),bytes("4fa48de2db65fa7082f4acc9f85ecc81d40d1793")),
           "c431a158b7b77d7e993515f8ebc2cd6add53b702");
    expect(protocol_kdf__snmp_sha1(bytes("4c505551444c734b"),bytes("000002b87766554433221100")),
           "629810a31adc31769dfebf9bacba06a3ffd9c49f");
    /* RFC 2631 section 2.1.6, two blocks of SHA-1 with a DER-encoded counter. */
    expect(protocol_kdf__x942(0,bytes("000102030405060708090a0b0c0d0e0f10111213"),
           bytes("301d3013060b2a864886f70d01091003060404"),bytes("a2060404000000c0"),24),
           "a09661392376f7044d9052a397883246b67f5f1ef63eb5fb");
    puts("SP 800-135 IKE, TLS, ANS X9.42/X9.63, SSH, SNMP and TPM vectors passed.");
    return 0;
}
