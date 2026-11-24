#include "mcv_entropy_c.h"
#include "mcv_estimate_c.h"
#include <assert.h>
static void check(const uint8_t *src,uint32_t n,uint32_t count,uint32_t upper,uint16_t entropy) {
    mcv_estimate__samples_t b=new_mcv_estimate__samples();
    b->length=n;b->seq=new_mcv_estimate_array_0(n);
    memcpy(b->seq->elems,src,n);b->count+=2;
    assert(mcv_estimate__most_common(b)==count);
    assert(mcv_estimate__estimate(b)==upper);
    assert(mcv_entropy__min_entropy((void*)b)==entropy);
}
int main(void) {
    /* SP 800-90B section 6.3.1 example. Expected values are rounded from
       the printed formula, at 24 probability bits and eight fractional entropy bits. */
    const uint8_t sample[]={0,1,1,2,0,1,2,2,0,1,0,1,1,0,2,2,1,0,2,1};
    uint8_t values[256],constant[50]={0};
    for(unsigned i=0;i<256;++i) values[i]=(uint8_t)i;
    check(sample,20,8,11568183,137);
    check(values,256,1,234357,1577);
    check(constant,50,50,16777216,0);
    puts("Most-common-value confidence and conservative min-entropy checks passed.");
}
