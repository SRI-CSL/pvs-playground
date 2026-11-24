/* Compare generated ML-KEM C with prepared NIST ACVP answers.
 * Each line contains rank, operation, tcId, then hex strings. */
#include "mlkem_random_c.h"
#include <ctype.h>

static int nibble(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    ch = (char)tolower((unsigned char)ch);
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    fputs("invalid vector hex\n", stderr);
    exit(2);
}
static mlkem_record_1_t bytes(const char *hex) {
    size_t len = strlen(hex);
    if (len % 2 || len > 8192) exit(2);
    mlkem_record_1_t b = new_mlkem_record_1();
    b->length = (uint32_t)(len / 2);
    b->seq = new_mlkem_array_0(b->length);
    for (uint32_t i = 0; i < b->length; i++)
        b->seq->elems[i] = (uint8_t)(16 * nibble(hex[2*i]) + nibble(hex[2*i+1]));
    return b;
}
static bool matches(mlkem_record_1_t b, const char *hex) {
    if (strlen(hex) != 2 * b->length) return false;
    for (uint32_t i = 0; i < b->length; i++)
        if (b->seq->elems[i] != 16*nibble(hex[2*i]) + nibble(hex[2*i+1])) return false;
    return true;
}
/* Only ACVP's explicit seed bytes are exposed to the checked PRNG attachment. */
static uint8_t test_draw[64];
uint16_t crypto_entropy_lookup(uint64_t stream, uint32_t i) { return 256; }
uint16_t crypto_prng_lookup(uint64_t stream, uint32_t i) {
    return stream==1 && i<64 ? test_draw[i] : 256;
}
static void seed_at(const char *hex, unsigned off) {
    if (strlen(hex)!=64 || off>32) exit(2);
    for (unsigned j=0;j<32;j++) test_draw[off+j]=(uint8_t)(16*nibble(hex[2*j])+nibble(hex[2*j+1]));
}
int main(void) {
    unsigned rank, id, total = 0, failed = 0;
    char op[24], a[8193], b[8193], c[8193], d[8193];
    while (scanf("%u %23s %u", &rank, op, &id) == 3) {
        bool ok;
        if (rank < 2 || rank > 4) return 2;
        if (!strcmp(op, "keygen")) {
            if (scanf("%8192s %8192s %8192s %8192s", a, b, c, d) != 4) return 2;
            seed_at(a,0); seed_at(b,32);
            mlkem_random_record_2_t k = mlkem_random__keygen(rank,1);
            ok = k->ok && matches((mlkem_record_1_t)k->ek,c) && matches((mlkem_record_1_t)k->dk,d);
            release_mlkem_random_record_2(k);
        } else if (!strcmp(op, "encapsulation")) {
            if (scanf("%8192s %8192s %8192s %8192s", a,b,c,d) != 4) return 2;
            seed_at(b,0);
            mlkem_random_record_4_t e = mlkem_random__encaps(rank,(mlkem_random_record_1_t)bytes(a),1);
            ok = e->ok && matches((mlkem_record_1_t)e->ct,c) && matches((mlkem_record_1_t)e->secret,d);
            release_mlkem_random_record_4(e);
        } else if (!strcmp(op, "decapsulation")) {
            if (scanf("%8192s %8192s %8192s", a,b,c) != 3) return 2;
            mlkem__sized_result_t s = mlkem__decaps(rank,bytes(a),bytes(b));
            ok = s->ok && matches(s->value,c);
            release_mlkem__sized_result(s);
        } else {
            unsigned expected;
            if (scanf("%8192s %u", a, &expected) != 2) return 2;
            if (!strcmp(op,"decapsulationKeyCheck"))
                ok = mlkem__valid_dk(rank,bytes(a)) == expected;
            else if (!strcmp(op,"encapsulationKeyCheck"))
                ok = mlkem__valid_ek(rank,bytes(a)) == expected;
            else return 2;
        }
        total++;
        if (!ok) {
            fprintf(stderr,"ML-KEM-%u %s tcId %u failed\n",rank*256,op,id);
            failed++;
        }
    }
    printf("ML-KEM ACVP: %u of %u cases passed\n",total-failed,total);
    return total && !failed && feof(stdin) ? 0 : 1;
}
