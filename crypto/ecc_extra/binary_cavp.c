#include "binary_ecdsa_c.h"
#include "binary_parameters_c.h"
#include "secure_hash_c.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint8_t digit(char c) {
    if (c >= '0' && c <= '9') return (uint8_t)(c - '0');
    assert(c >= 'a' && c <= 'f');
    return (uint8_t)(10 + c - 'a');
}
static uint8_t octet(const char *s) {
    return (uint8_t)((digit(s[0]) << 4) | digit(s[1]));
}
static binary_ecdsa_record_1_t integer(const char *s, uint16_t words) {
    binary_ecdsa_record_1_t a = new_binary_ecdsa_record_1();
    a->len = words;
    a->word = new_binary_ecdsa_array_0(words);
    memset(a->word->elems, 0, 4 * words);
    size_t n = strlen(s) / 2;
    assert(n * 2 == strlen(s) && n <= 4u * words);
    for (size_t i=0; i<n; ++i)
        a->word->elems[i/4] |= (uint32_t)octet(s+2*(n-1-i)) << (8*(i%4));
    return a;
}
static binary_ecdsa_record_3_t sha256(const char *s) {
    size_t n = strlen(s) / 2;
    assert(n * 2 == strlen(s));
    secure_hash_record_1_t msg = new_secure_hash_record_1();
    msg->length = (uint32_t)n;
    msg->seq = new_secure_hash_array_0((uint32_t)n);
    for (size_t i=0; i<n; ++i) msg->seq->elems[i]=octet(s+2*i);
    secure_hash_record_1_t digest = secure_hash__sha256(msg);
    binary_ecdsa_record_3_t converted = new_binary_ecdsa_record_3();
    converted->length=32;
    converted->seq=new_binary_ecdsa_array_2(32);
    memcpy(converted->seq->elems,digest->seq->elems,32);
    release_secure_hash_record_1(digest);
    return converted;
}
int main(void) {
    unsigned c,expected,total=0,passed=0;
    char msg[1025],x[145],y[145],r[145],s[145];
    while (scanf("%u %u %1024s %144s %144s %144s %144s",&c,&expected,msg,x,y,r,s)==7) {
        assert(c<10 && expected<2);
        uint16_t n=binary_parameters__words((uint8_t)c);
        binary_ecdsa_record_4_t q=new_binary_ecdsa_record_4();
        q->infinity=false;
        q->x=integer(x,n);
        q->y=integer(y,n);
        bool_t ok=binary_ecdsa__verify_digest((uint8_t)c,q,sha256(msg),integer(r,n),integer(s,n));
        ++total;
        if (ok==expected) ++passed;
        else fprintf(stderr,"Binary ECDSA profile %u case %u expected %u, got %d\n",c,total,expected,ok);
    }
    printf("Binary ECDSA CAVP: %u of %u cases passed\n",passed,total);
    return total>0 && passed==total ? 0 : 1;
}
