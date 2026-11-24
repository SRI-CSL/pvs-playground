/* Compare generated LMS C with prepared NIST ACVP answers.
 * Each line contains rank, operation, tcId, then hex strings. */
#include "hss_sign_c.h"
#include "hss_c.h"
#include <ctype.h>

static int nibble(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    ch = (char)tolower((unsigned char)ch);
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    fputs("invalid vector hex\n", stderr);
    exit(2);
}
static lms_record_1_t bytes(const char *hex) {
    size_t len = !strcmp(hex,"-") ? 0 : strlen(hex);
    if (len % 2 || len > 40000) exit(2);
    lms_record_1_t b = new_lms_record_1();
    b->length = (uint32_t)(len / 2);
    b->seq = new_lms_array_0(b->length);
    for (uint32_t i = 0; i < b->length; i++)
        b->seq->elems[i] = (uint8_t)(16 * nibble(hex[2*i]) + nibble(hex[2*i+1]));
    return b;
}
uint16_t crypto_entropy_lookup(uint64_t s,uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t s,uint32_t i) { return s && i<64 ? (uint8_t)(19*s+i) : 256; }
static hss_sign__streams_t streams(unsigned base) {
    hss_sign__streams_t result=new_hss_sign__streams(8);
    for (unsigned i=0;i<8;i++) result->elems[i]=base+i;
    return result;
}
static bool rollover(void) {
    hss_sign__configs_t cfg=new_hss_sign__configs(8);
    for (unsigned i=0;i<8;i++) {
        cfg->elems[i]=new_hss_sign__level_config();
        cfg->elems[i]->h=0; cfg->elems[i]->w=0;
    }
    hss_sign__state_result_t initial=hss_sign__keygen_hss(1,cfg,2,streams(1),streams(9));
    if (!initial->ok) { release_hss_sign__state_result(initial); return false; }
    initial->state->count++;
    hss_sign_record_4_t pk=hss_sign__pub_hss(initial->state);
    /* In this fixture the bottom tree's 32 reservations have been committed. */
    initial->state->trees->elems[1]->next=32;
    initial->state->count++;
    hss_sign__signed_message_t signed_msg=hss_sign__sign_hss(initial->state,
        (hss_sign_record_4_t)bytes("a7"),streams(17),streams(25),33);
    bool state_ok=signed_msg->ok && signed_msg->state->trees->elems[0]->next==2
               && signed_msg->state->trees->elems[1]->next==1;
    signed_msg->value->count++;
    bool valid=hss__verify_hss((hss_record_2_t)pk,(hss_record_2_t)signed_msg->value,
                               (hss_record_2_t)bytes("a7"));
    release_hss_sign__signed_message(signed_msg);
    release_hss_sign__state_result(initial);
    return state_ok && valid;
}
int main(void) {
    unsigned id, expected, total=0, failed=0;
    char op;
    char pk[121],sig[40001],msg[40001];
    while (scanf(" %c %u %u %120s %40000s %40000s",&op,&id,&expected,pk,sig,msg)==6) {
        bool valid;
        if (op=='L') valid=lms__verify_lms(bytes(pk),bytes(sig),bytes(msg));
        else if (op=='H') valid=hss__verify_hss((hss_record_2_t)bytes(pk),(hss_record_2_t)bytes(sig),
                                                (hss_record_2_t)bytes(msg));
        else if (op=='S') {
            char randomizer[65]; memcpy(randomizer,sig+16,64); randomizer[64]=0;
            const char *seed="a1c4696e2608035a886100d05cd99945eb3370731884a8235e2fb3d4d71f2547";
            const char *ident="215f83b7ccb9acbcd08db97b0d04dc2b";
            lms_sign__sig_result_t result=lms_sign__sign_reserved(0,0,3,
                (lms_sign_record_1_t)bytes(ident),(lms_sign_record_1_t)bytes(seed),
                (lms_sign_record_1_t)bytes(randomizer),4,(lms_sign_record_1_t)bytes(msg));
            lms_record_1_t expected_sig=bytes(sig);
            valid=result->ok && equal_lms_record_1((lms_record_1_t)result->value,expected_sig);
            release_lms_record_1(expected_sig);
            release_lms_sign__sig_result(result);
        } else return 2;
        total++;
        if (valid!=expected) { fprintf(stderr,"LMS verification tcId %u failed\n",id); failed++; }
    }
    total++; if (!rollover()) { failed++; fputs("HSS rollover failed\n",stderr); }
    printf("LMS/HSS vectors: %u of %u cases passed\n",total-failed,total);
    return total && !failed && feof(stdin) ? 0 : 1;
}
