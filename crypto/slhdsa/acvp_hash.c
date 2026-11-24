#include "slh_prehash_c.h"
#include <assert.h>
typedef slh_prehash_record_1_t octets_t;
#define new_octets new_slh_prehash_record_1
#define new_octet_array new_slh_prehash_array_0
#include "acvp_read.h"

int main(void) {
    int p, sha2 = 0;
    unsigned passed=0,total=0;
    while ((p=getchar())!=EOF) {
        int hash=getchar(),expected=getchar();
        assert(p<12 && 1<=hash && hash<=12 && (expected==0 || expected==1));
        uint32_t id=read_u32();
        octets_t pk=field(),sig=field(),ctx=field(),m=field();
        bool_t ok=slh_prehash__hash_verify(p,pk,sig,ctx,m,hash,0,0);
        sha2 = p>=6;
        ++total;
        if (ok==expected) ++passed;
        else fprintf(stderr,"HashSLH-DSA case %u expected %d got %d\n",id,expected,ok);
    }
    printf("HashSLH-DSA %s ACVP verification: %u of %u cases passed.\n",sha2 ? "SHA2" : "SHAKE",passed,total);
    return total && total==passed ? 0 : 1;
}
