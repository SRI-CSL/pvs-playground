/* Compare generated XMSS and XMSSMT with the RFC authors’ reference implementation. */
#include "xmss_sign_c.h"
#include <ctype.h>

static int nibble(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    ch = (char)tolower((unsigned char)ch);
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    fputs("invalid vector hex\n", stderr);
    exit(2);
}
static xmss_sign_record_1_t bytes(const char *hex) {
    size_t len = strlen(hex);
    if (len % 2 || len > 60000) exit(2);
    xmss_sign_record_1_t b = new_xmss_sign_record_1();
    b->length = (uint32_t)(len / 2);
    b->seq = new_xmss_sign_array_0(b->length);
    for (uint32_t i = 0; i < b->length; i++)
        b->seq->elems[i] = (uint8_t)(16 * nibble(hex[2*i]) + nibble(hex[2*i+1]));
    return b;
}
static bool matches(xmss_sign_record_1_t b, const char *hex) {
    if (strlen(hex) != 2 * b->length) return false;
    for (uint32_t i = 0; i < b->length; i++)
        if (b->seq->elems[i] != 16*nibble(hex[2*i]) + nibble(hex[2*i+1])) return false;
    return true;
}
/* The RFC authors' vectors use 00, 01, ... 3n-1 as S_XMSS || SK_PRF || SEED. */
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s==1 && i<96 ? i : 256; }
int main(void) {
    unsigned mt,oid,idx,total=0,failed=0;
    char pk[145],sig[60001],msg[129];
    while (scanf("%u %u %u %144s %60000s %128s",&mt,&oid,&idx,pk,sig,msg)==6) {
        bool valid=xmss__verify_xmss(mt,(xmss_record_2_t)bytes(pk),(xmss_record_2_t)bytes(sig),
                                     (xmss_record_2_t)bytes(msg));
        if (!valid) { fprintf(stderr,"XMSS verify %u/%u failed\n",mt,oid); failed++; }
        total++;
        char changed[129]; strcpy(changed,msg); changed[0]=(msg[0]=='1'?'2':'1');
        if (xmss__verify_xmss(mt,(xmss_record_2_t)bytes(pk),(xmss_record_2_t)bytes(sig),
                              (xmss_record_2_t)bytes(changed))) failed++;
        total++;
        if (mt && oid==34) {
            xmss_sign__material_t keys=xmss_sign__gen_material(1,1);
            if (!keys->ok) return 2;
            keys->secret->count++; keys->seed->count++;
            xmss_sign_record_1_t computed_pk=xmss_sign__vk(mt,oid,keys->secret,keys->seed);
            if (!matches(computed_pk,pk)) { fputs("XMSS public root failed\n",stderr); failed++; }
            total++; release_xmss_sign_record_1(computed_pk);
            keys->secret->count++; keys->skprf->count++; keys->seed->count++;
            xmss_sign__signature_t result=xmss_sign__sign_xmss(mt,oid,keys->secret,keys->skprf,
                keys->seed,bytes(pk),idx,bytes(msg));
            if (!result->ok || !matches(result->value,sig)) { fputs("XMSS signing failed\n",stderr); failed++; }
            total++; release_xmss_sign__signature(result); release_xmss_sign__material(keys);
        }
    }
    printf("XMSS reference: %u of %u checks passed\n",total-failed,total);
    return total && !failed && feof(stdin) ? 0 : 1;
}
