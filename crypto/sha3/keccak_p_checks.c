#include "keccak_p_c.h"
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
int main(void) {
    unsigned shape, count, total=0, pass=0;
    while (scanf("%u%u", &shape, &count)==2) {
        keccak_p_array_0_t lanes = new_keccak_p_array_0(25);
        uint64_t expected[25];
        for (unsigned j=0;j<25;j++) assert(scanf("%" SCNx64,&lanes->elems[j])==1);
        for (unsigned j=0;j<25;j++) assert(scanf("%" SCNx64,&expected[j])==1);
        keccak_p_array_0_t out=keccak_p__permute_p(shape,count,lanes);
        bool ok=true;
        for (unsigned j=0;j<25;j++) ok=ok && out->elems[j]==expected[j];
        release_keccak_p_array_0(out);
        pass+=ok;
        ++total;
    }
    printf("Keccak-p permutations: %u of %u checks passed\n",pass,total);
    return total && pass==total ? 0 : 1;
}
