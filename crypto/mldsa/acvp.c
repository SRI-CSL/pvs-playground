/* Compare generated ML-DSA C with prepared NIST ACVP answers.
 * Each line contains rank, operation, tcId, then hex strings. */
#include "mldsa_random_c.h"
#include <ctype.h>

static int nibble(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    ch = (char)tolower((unsigned char)ch);
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    fputs("invalid vector hex\n", stderr);
    exit(2);
}
static mldsa_record_4_t bytes(const char *hex) {
    size_t len = !strcmp(hex,"-") ? 0 : strlen(hex);
    if (len % 2 || len > 16384) exit(2);
    mldsa_record_4_t b = new_mldsa_record_4();
    b->length = (uint32_t)(len / 2);
    b->seq = new_mldsa_array_3(b->length);
    for (uint32_t i = 0; i < b->length; i++)
        b->seq->elems[i] = (uint8_t)(16 * nibble(hex[2*i]) + nibble(hex[2*i+1]));
    return b;
}
static bool matches(mldsa_record_4_t b, const char *hex) {
    if (strlen(hex) != 2 * b->length) return false;
    for (uint32_t i = 0; i < b->length; i++)
        if (b->seq->elems[i] != 16*nibble(hex[2*i]) + nibble(hex[2*i+1])) return false;
    return true;
}
/* The test provider uses only the explicit ACVP randomness for this case. */
static uint8_t test_seed[32];
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) {
    return stream == 1 && i < 32 ? test_seed[i] : 256;
}
static void set_seed(const char *hex) {
    if (strlen(hex)!=64) exit(2);
    for (unsigned i=0;i<32;i++)
        test_seed[i]=(uint8_t)(16*nibble(hex[2*i])+nibble(hex[2*i+1]));
}
#define RANDOM_BYTES(s) ((mldsa_random_record_1_t)bytes(s))
#define HASH_BYTES(s) ((mldsa_prehash_record_1_t)bytes(s))
int main(void) {
    unsigned profile, id, total=0, failed=0;
    char op[24], a[10001], b[10001], c[10001], d[10001], msg[16385], ctx[511];
    while (scanf("%u %23s %u",&profile,op,&id)==3) {
        bool ok;
        if (profile>2) return 2;
        if (!strcmp(op,"keygen")) {
            if (scanf("%10000s %10000s %10000s",a,b,c)!=3) return 2;
            set_seed(a);
            mldsa_random_record_2_t k=mldsa_random__keygen(profile,1);
            ok=k->ok && matches((mldsa_record_4_t)k->pk,b)
                     && matches((mldsa_record_4_t)k->sk,c);
            release_mldsa_random_record_2(k);
        } else if (!strcmp(op,"verify")) {
            unsigned expected;
            if (scanf("%10000s %10000s %10000s %u",a,b,c,&expected)!=4) return 2;
            ok = mldsa__verify_mu(profile,bytes(a),bytes(c),bytes(b)) == expected;
        } else if (!strcmp(op,"sign")) {
            if (scanf("%10000s %10000s %10000s %10000s",a,b,c,d)!=4) return 2;
            mldsa_sign_record_9_t s=mldsa_sign__sign_mu(profile,
                (mldsa_sign_record_1_t)bytes(a),(mldsa_sign_record_1_t)bytes(b),
                (mldsa_sign_record_1_t)bytes(c));
            ok=s->ok && matches((mldsa_record_4_t)s->value,d);
            release_mldsa_sign_record_9(s);
        } else if (!strcmp(op,"verify_external")) {
            unsigned oid,expected;
            if (scanf("%u %10000s %16384s %510s %10000s %u",&oid,a,msg,ctx,c,&expected)!=6
                    || oid>12) return 2;
            bool valid = oid == 0 ? mldsa__verify(profile,bytes(a),bytes(c),bytes(msg),bytes(ctx),0,0)
                : mldsa_prehash__hash_verify(profile,HASH_BYTES(a),HASH_BYTES(c),oid,
                                             HASH_BYTES(msg),HASH_BYTES(ctx),0,0);
            ok=valid==expected;
        } else if (!strcmp(op,"sign_external")) {
            unsigned oid;
            if (scanf("%u %10000s %16384s %510s %10000s %10000s",&oid,a,msg,ctx,c,d)!=6
                    || oid>12) return 2;
            set_seed(c);
            mldsa_random_record_3_t s=oid==0
                ? mldsa_random__sign_hedged(profile,RANDOM_BYTES(a),RANDOM_BYTES(msg),
                                            RANDOM_BYTES(ctx),0,0,1)
                : mldsa_random__hash_sign_hedged(profile,RANDOM_BYTES(a),oid,RANDOM_BYTES(msg),
                                                 RANDOM_BYTES(ctx),0,0,1);
            ok=s->ok && matches((mldsa_record_4_t)s->value,d);
            release_mldsa_random_record_3(s);
        } else return 2;
        total++;
        if (!ok) {
            fprintf(stderr,"ML-DSA profile %u %s tcId %u failed\n",profile,op,id);
            failed++;
        }
    }
    printf("ML-DSA ACVP: %u of %u cases passed\n",total-failed,total);
    return total && !failed && feof(stdin) ? 0 : 1;
}
