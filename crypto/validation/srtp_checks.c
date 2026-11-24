/* NIST SP 800-135r1 ASKDFVS srtp.rsp. Each case tests all six RFC 3711
 * labels, including the SRTCP index and multi-block authentication key. */
#include "srtp_kdf_c.h"
#include <assert.h>

static srtp_kdf__salt112_t octets(const char *s) {
    size_t n=strlen(s)/2;
    srtp_kdf__salt112_t a=new_srtp_kdf__salt112(n);
    for (size_t i=0;i<n;++i) {
        unsigned b;
        assert(sscanf(s+2*i,"%2x",&b)==1);
        a->elems[i]=b;
    }
    return a;
}
static aes_modes__mode_key_adt_t key(const char *s) {
    aes_modes_array_1_t a=(aes_modes_array_1_t)octets(s);
    if (a->size==16) return con_aes_modes__mk128(a);
    if (a->size==24) return con_aes_modes__mk192(a);
    assert(a->size==32); return con_aes_modes__mk256(a);
}
static void check(const char *k,const char *s,uint64_t i,uint64_t j,bool fixed,uint8_t log_rate,
                  const char *expected[6]) {
    for (uint8_t label=0;label<6;label++) {
        srtp_kdf__salt112_t e=octets(expected[label]);
        srtp_kdf_record_1_t actual=srtp_kdf__derive(key(k),octets(s),label,label<3?i:j,fixed,log_rate,e->size);
        if (actual->length!=e->size || memcmp(e->elems,actual->seq->elems,e->size)) {
            fprintf(stderr,"SRTP mismatch for label %u, AES-%zu, kdr exponent %u, static %u\n",label,4*strlen(k),log_rate,fixed);
            abort();
        }
        release_srtp_kdf__salt112(e); release_srtp_kdf_record_1(actual);
    }
}
int main(void) {
    check("c4809f6d369888728e26adb532129890","0e23006c6c044f5662400e9d1bd6",0x487165649ccaULL,0x56f3f197ULL,true,0,
          (const char *[]){"dc382192ab65108a86b259b61b3af46f",
                           "b83937fb321792ee87b788193be5a4e3bd326ee4",
                           "f1c035c00b5a54a61692c016276c",
                           "ab5be0b456235dcf77d5086929bafb38",
                           "c52fde0b80b0f0bad8d15645cb86e7c7c3d8770e",
                           "deb5f85f81336a965ed32bb7ede8"});
    check("ed7a0c0ccff1d84a824e91b01fa457a4","c62625901085724166e934a0a998",0x638bc149df0bULL,0x63bda774ULL,false,0,
          (const char *[]){"f2dedeb13382ab3869d27f16ee75c2cb",
                           "77b63e42c98e552cf687e86fbdbe1b293eddf289",
                           "109be6ef148b7739694622aafd0c",
                           "20e5f1dfc13620704e44e06ec8ff4f19",
                           "dcb3bc06d10e31dcb4c9085f3f12fd37d3bf6b79",
                           "77ac07862fc1469b9cb3cabd2953"});
    check("821887f549224516b43a5143b44c0c313d3b875bb424fb9f","dc55558b17a5f686b3b61457eaf1",0xae8cdcdefcbdULL,0x6c27d06aULL,true,0,
          (const char *[]){"76c8ef187a7e35b02e5f4b7936d5f966f1f9b55b59c3796f",
                           "cdfc18b63cb691937db756b761282e9d35c4b371",
                           "4ef784fb0a1a828161fd9cd966d2",
                           "bddd5f1db61ec6f44c972acab90d45e719dea0d81c488c4f",
                           "df529f45b9b9b5c292a6370ad9bb2ca32e0c7125",
                           "59ba69e85aebf54bed880701bb73"});
    check("bb045b1f53c6932c2ba688f5e3f22470e17d7dec8a934df2","e722ab92fc7c89b6538af93cb952",0xd7878f33b176ULL,0x40bfd4a9ULL,false,0,
          (const char *[]){"2cc83e54b23389b371650f516165e493074eb347ba2d6060",
                           "2e80e48255a2be6de046ccc175786e78d1d14708",
                           "e0c1e6af1e8d8cfee56070b5e6ea",
                           "940f55ce58d81665f0fa46400cdab1119e69a0934ed7f284",
                           "f5416fc265c5b3efbb22c8fc6b0014b2f33b8e29",
                           "35b74243f00101b468a1288037f0"});
    check("a263d11aa2dcb2d59b52d6cc77bddb82798179cda98ad2ff70e83d184e9ef4a0","883778c508eb03c45b29e8c0cbfe",0xa31b4054eff2ULL,0x134c512aULL,true,0,
          (const char *[]){"df4bf89f2669868b2ac482f7e25867a0f814437ac29a0e6cfce53dde8306e022",
                           "1cd6b9e242c63bee044aa64ad3f8fbde84772218",
                           "7fbf73784dc9237bd3f3d3316279",
                           "432f07576604aceb727c0bb9841f55d90373947b3ba947432a44e6baad8490a6",
                           "0b3467e5302099ab3e8eb1444204107318975f88",
                           "6c931c470e15144708855e777219"});
    check("0a63c14fce7739192b6f163137efa5bf10e6e29e2cdf9773b1e317555bb9046c","fe072b1035be7abb71d60b83f30d",0xb64c6d6fe260ULL,0x078dda65ULL,false,0,
          (const char *[]){"d53cd2802d3141a3545b1568420bc7b83d9cb44df0accfb09356fc34774418fb",
                           "d3eb2c4272966e98f586dfc405960430726b7490",
                           "50e52e5e8938420d40b5b1917428",
                           "88f8622ec62fb38f45cf5bf1722227614ceaf9aac45ccd0fcf7bee5e8c8a9693",
                           "e5fc7089b7600bfade47cb87523d7507bbb7b911",
                           "b2f46398c2247e6decde309bd624"});
    puts("SP 800-135 SRTP and SRTCP vectors passed.");
    return 0;
}
