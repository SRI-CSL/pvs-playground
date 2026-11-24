/* NIST SP 800-22 Rev. 1a, Appendix B example 1, MSB first. */
#include "sts_counts_c.h"
#include "sts_suite_c.h"
#include "sts_spectral_c.h"
#include "sts_complexity_c.h"
#include "sts_walk_c.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static void check(const char *name, void *p, double want, double tolerance) {
    crypto_statistics__observation_t r = p;
    double got = crypto_double(r->pvalue);
    printf("%-26s %.10f\n", name, got);
    fflush(stdout);
    if (!r->applicable || !isfinite(got) || fabs(got - want) > tolerance) {
        fprintf(stderr, "%s expected %.10f, got %.10f\n", name, want, got);
        exit(1);
    }
    release_crypto_statistics__observation(r);
}
static sts_counts__bitstream_t retain(sts_counts__bitstream_t x) {
    x->count++;
    return x;
}
int main(void) {
    const unsigned n = 1000000;
    sts_counts__bitstream_t x = new_sts_counts__bitstream();
    x->n = n;
    x->bits = new_sts_counts_array_0(n);
    for (unsigned i = 0; i < n; i += 8) {
        int byte = getchar();
        assert(byte != EOF);
        for (unsigned j = 0; j < 8; ++j)
            x->bits->elems[i + j] = (byte >> (7-j)) & 1;
    }
    assert(sts_suite__template_count(9,512,0,0)==148);
    sts_suite__tally_t summary=sts_suite__start();
    for (unsigned i=0;i<100;++i) {
        crypto_statistics__observation_t v=new_crypto_statistics__observation();
        v->applicable=true; v->pvalue=crypto_fp((i+.5)/100.);
        summary=sts_suite__accumulate(summary,(void*)v,crypto_fp(.01));
    }
    assert(summary->eligible==100 && summary->passed==99);
    summary->count++;
    assert(sts_suite__within_interval(summary,crypto_fp(.01)));
    check("Uniformity",sts_suite__uniformity(summary),1,1e-12);
    /* Independent overlapping counts for the literal §2.8.4 bitstring. */
    check("Overlapping worked example",sts_counts__overlapping_parameters((void*)sts_suite__overlap_example(),2,10,5),
          .40963462458,1e-9);
    check("Frequency", sts_counts__frequency(retain(x)), .578211, 1e-6);
    check("Block frequency", sts_counts__block_frequency(retain(x),128), .380615, 1e-6);
    check("Runs", sts_counts__runs(retain(x)), .419268, 1e-6);
    check("Longest run", sts_counts__longest_run(retain(x)), .024390, 1e-6);
    check("Rank", sts_counts__rank_test(retain(x)), .083553, 1e-6);
    check("Nonoverlapping template", sts_counts__nonoverlapping(retain(x),1,9), .165757, 1e-6);
    /* Recomputed from the updated §2.8 probabilities and bins 348,158,136,96,73,157. */
    check("Overlapping template", sts_counts__overlapping(retain(x)), .2607037020, 1e-9);
    check("Approximate entropy", sts_counts__approximate_entropy(retain(x),10), .361595, 1e-6);
    check("Serial", sts_counts__serial(retain(x),16,false), .143005, 1e-6);
    check("Serial second", sts_counts__serial(retain(x),16,true), .03435359198, 1e-9);
    check("Cusum forward", sts_walk__cumulative_sums((void*)retain(x),false), .628308, 1e-6);
    check("Cusum reverse", sts_walk__cumulative_sums((void*)retain(x),true), .663369, 1e-6);
    check("Excursions", sts_walk__excursion((void*)retain(x),1,false), .844143, 1e-6);
    check("Excursions variant", sts_walk__excursion((void*)retain(x),-1,true), .760966, 1e-6);
    check("Universal", sts_complexity__universal((void*)retain(x),7), .669012, 1e-6);
    /* Section 2.10 probabilities; independent category counts 30,64,254,955,529,127,41. */
    check("Linear complexity", sts_complexity__linear_complexity((void*)retain(x),500), .24685656617502524, 1e-9);
    check("DFT (1,000,000)", sts_spectral__spectral((void*)retain(x)), .01018582615, 1e-9);
    /* Prime and power-of-two prefixes, independently evaluated by a complex DFT. */
    x->n = 997;
    check("DFT (997)", sts_spectral__spectral((void*)retain(x)), .45424067494814047, 1e-10);
    x->n = 1024;
    check("DFT (1024)", sts_spectral__spectral((void*)retain(x)), .20702560815693738, 1e-10);
    release_sts_counts__bitstream(x);
    puts("SP 800-22: all fifteen families passed");
}
