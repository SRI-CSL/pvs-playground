#include "slh_verify_c.h"
#include <assert.h>

typedef slh_verify_record_1_t octets_t;
#define new_octets new_slh_verify_record_1
#define new_octet_array new_slh_verify_array_0
#include "acvp_read.h"

int main(void) {
    unsigned passed=0, total=0;
    int p, sha2 = 0;
    while ((p=getchar())!=EOF) {
        int external=getchar(), expected=getchar();
        assert(p<12 && (external==0 || external==1) && (expected==0 || expected==1));
        uint32_t id=read_u32();
        slh_verify_record_1_t pk=field(), sig=field(), ctx=field(), m=field();
        bool_t ok;
        if (external) ok=slh_verify__verify(p,pk,sig,ctx,m);
        else {
            release_slh_verify_record_1(ctx);
            ok=slh_verify__verify_internal(p,pk,sig,m);
        }
        sha2 = p>=6;
        ++total;
        if (ok==expected) ++passed;
        else fprintf(stderr,"SLH-DSA sigVer case %u expected %d, got %d\n",id,expected,ok);
    }
    printf("SLH-DSA %s ACVP verification: %u of %u cases passed.\n",sha2 ? "SHA2" : "SHAKE",passed,total);
    return total && passed==total ? 0 : 1;
}
