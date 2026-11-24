#include "ecdsa_c.h"
#include <assert.h>
#if __has_include("ecdsa_extra_bits_c.h")
#include "ecdsa_extra_bits_c.h"
#endif
#if __has_include("ecdsa_signing_c.h")
#include "ecdsa_signing_c.h"
static uint8_t sample[66];
static unsigned sample_length;
uint16_t crypto_entropy_lookup(uint64_t stream,uint32_t index) { return 256; }
uint16_t crypto_prng_lookup(uint64_t stream,uint32_t index) {
    if (stream==2) return (uint8_t)(index+1);
    return stream==1 && index<sample_length ? sample[index] : 256;
}
#endif

static ecdsa_record_3_t octets(const char *hex) {
    size_t len=strlen(hex);
    assert(len%2==0);
    ecdsa_record_3_t b=new_ecdsa_record_3();
    b->length=len/2;
    b->seq=new_ecdsa_array_2(b->length);
    for (unsigned i=0;i<b->length;++i) {
        unsigned v;
        assert(sscanf(hex+2*i,"%2x",&v)==1);
        b->seq->elems[i]=v;
    }
    return b;
}
static ecdsa_record_1_t scalar(uint8_t c,const char *hex) {
    return (ecdsa_record_1_t)crypto_limbs__from_bytes(nist_prime_curves__width(c),
           (crypto_limbs_record_4_t)octets(hex),true);
}
static void test(uint8_t c,const char *d,const char *x,const char *y,const char *k,
                 const char *r,const char *s,const char *z) {
    const char *hash="af2bdbe1aa9b6ec1e2ade1d694f41fc71a831d0268e9891562113d8a62add1bf";
    prime_curve__affine_t q=prime_curve__public_key(c,(prime_curve_record_1_t)scalar(c,d));
    ecdsa_record_1_t qx=scalar(c,x),qy=scalar(c,y);
    assert(q->finite && equal_ecdsa_record_1((ecdsa_record_1_t)q->x,qx)
                     && equal_ecdsa_record_1((ecdsa_record_1_t)q->y,qy));
    release_ecdsa_record_1(qx);
    release_ecdsa_record_1(qy);
    ecdsa__sig_result_t result=ecdsa__sign_digest(c,scalar(c,d),scalar(c,k),octets(hash));
    ecdsa_record_1_t rr=scalar(c,r),ss=scalar(c,s);
    assert(result->ok && equal_ecdsa_record_1(result->r,rr) && equal_ecdsa_record_1(result->s,ss));
    release_ecdsa__sig_result(result);
#if __has_include("ecdsa_signing_c.h")
    if (c!=0) {
        const char *m="73616d706c65"; /* RFC 6979, SHA-256("sample") */
        ecdsa_signing_record_6_t a=ecdsa_signing__deterministic(c,2,
            (ecdsa_signing_record_3_t)scalar(c,d),(ecdsa_signing_record_1_t)octets(m),16);
        assert(a->ok && equal_ecdsa_record_1((ecdsa_record_1_t)a->r,rr)
                     && equal_ecdsa_record_1((ecdsa_record_1_t)a->s,ss));
        release_ecdsa_signing_record_6(a);
        ecdsa_record_3_t source=octets(k);
        /* FIPS 186-5 Appendix A.4.2 maps the draw k-1 to the scalar k. */
        for (unsigned i=source->length; i>0; --i) {
            if (source->seq->elems[i-1]--!=0) break;
        }
        sample_length=source->length;
        for (unsigned i=0; i<sample_length; ++i) {
            unsigned next=i+1<sample_length ? source->seq->elems[i+1] : 0;
            sample[i]=c==4 ? (source->seq->elems[i]<<7)|(next>>1) : source->seq->elems[i];
        }
        release_ecdsa_record_3(source);
        a=ecdsa_signing__sign_random(c,2,(ecdsa_signing_record_3_t)scalar(c,d),
                                      (ecdsa_signing_record_1_t)octets(m),1);
        assert(a->ok && equal_ecdsa_record_1((ecdsa_record_1_t)a->r,rr)
                     && equal_ecdsa_record_1((ecdsa_record_1_t)a->s,ss));
        release_ecdsa_signing_record_6(a);
        ecdsa_signing__key_handle_t key=ecdsa_signing__keygen(c,0);
        assert(!key->ok);
        release_ecdsa_signing__key_handle(key);
#if __has_include("ecdsa_extra_bits_c.h")
        /* Integer reductions of the big-endian byte sequence 01,02,... . */
        const char *extra_k[] = {
            "", "090a0b0c0d0e0ffb43ab5a1899058cbdae119396093e9b828fb12d45",
            "0e101214070605041155b315cb1c6f28abec21cff529b6e3d4e248eb668b4769",
            "090a0b0c0d0e0f101112131415161718195329b2b9cca856229b3c6f14f87a37e5c4e18fa9f368115f29da0e383ecda9",
            "00121416181a1c1e20222426282a2c2e30323436383a3c3e40424a002fd7fc61973636c2b12dc703e9f748802fc1205d9d1c0fdfc65f083255b7f95bd036f7df3853"
        };
        ecdsa_record_1_t extra=(ecdsa_record_1_t)ecdsa_extra_bits__sample_extra(c,2);
        ecdsa_record_1_t want=scalar(c,extra_k[c]);
        assert(equal_ecdsa_record_1(extra,want));
        release_ecdsa_record_1(want); release_ecdsa_record_1(extra);
        ecdsa_extra_bits_record_8_t signed_msg=ecdsa_extra_bits__sign_message(c,8,
            (ecdsa_extra_bits_record_2_t)scalar(c,d),(ecdsa_extra_bits_record_3_t)octets(m),2,true);
        assert(signed_msg->ok);
        ++q->count; ++signed_msg->r->count; ++signed_msg->s->count;
        assert(ecdsa_extra_bits__verify_message(c,8,(ecdsa_extra_bits_record_5_t)q,
            (ecdsa_extra_bits_record_3_t)octets(m),signed_msg->r,signed_msg->s));
        release_ecdsa_extra_bits_record_8(signed_msg);
#endif
        printf("P-%u deterministic and sampled signing passed.\n",nist_prime_curves__bits(c));
    }
#endif
    ++q->count;
    assert(ecdsa__verify_digest(c,(ecdsa_record_5_t)q,octets(hash),rr,ss));
    ++q->count;
    assert(!ecdsa__verify_digest(c,(ecdsa_record_5_t)q,octets("01"),scalar(c,r),scalar(c,s)));
    prime_curve__secret_result_t shared=prime_curve__cdh(c,(prime_curve_record_1_t)scalar(c,k),q);
    ecdsa_record_3_t expected=octets(z);
    assert(shared->valid && equal_ecdsa_record_3((ecdsa_record_3_t)shared->value,expected));
    release_ecdsa_record_3(expected);
    release_prime_curve__secret_result(shared);
    printf("P-%u ECDSA key generation, signing, verification and ECDH passed.\n",nist_prime_curves__bits(c));
    fflush(stdout);
}
int main(void) {
    test(0,
         "6fab034934e4c0fc9ae67f5b5659a9d7d1fefd187ee09fd4",
         "ac2c77f529f91689fea0ea5efec7f210d8eea0b9e047ed56",
         "3bc723e57670bd4887ebc732c523063d0a7c957bc97c1c43",
         "32b1b6d7d42a05cb449065727a84804fb1a3e34d8f261496",
         "4b0b8ce98a92866a2820e20aa6b75b56382e0f9bfd5ecb55",
         "ccdb006926ea9565cbadc840829d8c384e06de1f1e381b85",
         "b059f76eb66b5485e3f1d3d3c4bd8feebb8971d1ea015ef4");
    test(1,
         "f220266e1105bfe3083e03ec7a3a654651f45e37167e88600bf257c1",
         "00cf08da5ad719e42707fa431292dea11244d64fc51610d94b130d6c",
         "eeab6f3debe455e3dbf85416f7030cbd94f34f2d6f232c69f3c1385a",
         "ad3029e0278f80643de33917ce6908c70a8ff50a411f06e41dedfcdc",
         "61aa3da010e8e8406c656bc477a7a7189895e7e840cdfe8ff42307ba",
         "bc814050dab5d23770879494f9e0a680dc1af7161991bde692b10101",
         "ca1564b665408ebe550c348d1ea25bd01193feb57e708cbad83955c1");
    test(2,
         "c9afa9d845ba75166b5c215767b1d6934e50c3db36e89b127b8a622b120f6721",
         "60fed4ba255a9d31c961eb74c6356d68c049b8923b61fa6ce669622e60f29fb6",
         "7903fe1008b8bc99a41ae9e95628bc64f2f1b20c2d7e9f5177a3c294d4462299",
         "a6e3c57dd01abe90086538398355dd4c3b17aa873382b0f24d6129493d8aad60",
         "efd48b2aacb6a8fd1140dd9cd45e81d69d2c877b56aaf991c34d0ea84eaf3716",
         "f7cb1c942d657c41d436c7a1b6e29f65f3e900dbb9aff4064dc4ab2f843acda8",
         "3ffbbd4fe496a30ea456822f31c21e76482462fca119bece403abf00bed50fbb");
    test(3,
         "6b9d3dad2e1b8c1c05b19875b6659f4de23c3b667bf297ba9aa47740787137d896d5724e4c70a825f872c9ea60d2edf5",
         "ec3a4e415b4e19a4568618029f427fa5da9a8bc4ae92e02e06aae5286b300c64def8f0ea9055866064a254515480bc13",
         "8015d9b72d7d57244ea8ef9ac0c621896708a59367f9dfb9f54ca84b3f1c9db1288b231c3ae0d4fe7344fd2533264720",
         "180ae9f9aec5438a44bc159a1fcb277c7be54fa20e7cf404b490650a8acc414e375572342863c899f9f2edf9747a9b60",
         "21b13d1e013c7fa1392d03c5f99af8b30c570c6f98d4ea8e354b63a21d3daa33bde1e888e63355d92fa2b3c36d8fb2cd",
         "f3aa443fb107745bf4bd77cb3891674632068a10ca67e3d45db2266fa7d1feebefdc63eccd1ac42ec0cb8668a4fa0ab0",
         "32b0764f10ada6e54defd9ede57be1f30d5395460fc4a62533e352a6e8d890ff5441006efd53ec4e2a622444672843dc");
    test(4,
         "00fad06daa62ba3b25d2fb40133da757205de67f5bb0018fee8c86e1b68c7e75caa896eb32f1f47c70855836a6d16fcc1466f6d8fbec67db89ec0c08b0e996b83538",
         "01894550d0785932e00eaa23b694f213f8c3121f86dc97a04e5a7167db4e5bcd371123d46e45db6b5d5370a7f20fb633155d38ffa16d2bd761dcac474b9a2f5023a4",
         "00493101c962cd4d2fddf782285e64584139c2f91b47f87ff82354d6630f746a28a0db25741b5b34a828008b22acc23f924faafbd4d33f81ea66956dfeaa2bfdfcf5",
         "00edf38afcaaecab4383358b34d67c9f2216c8382aaea44a3dad5fdc9c32575761793fef24eb0fc276dfc4f6e3ec476752f043cf01415387470bcbd8678ed2c7e1a0",
         "01511bb4d675114fe266fc4372b87682baecc01d3cc62cf2303c92b3526012659d16876e25c7c1e57648f23b73564d67f61c6f14d527d54972810421e7d87589e1a7",
         "004a171143a83163d6df460aaf61522695f207a58b95c0644d87e52aa1a347916e4f7a72930b1bc06dbe22ce3f58264afd23704cbb63b29b931f7de6c9d949a7ecfc",
         "0041b37f9abc347014336352e57fdcb2fe6bf67b7b453c5b7b15e81ee9b42b78b35bcc2735a62ac4c569d34179bf1c932be15d922d12b7d608026e4b9e795f362104");
    return 0;
}
