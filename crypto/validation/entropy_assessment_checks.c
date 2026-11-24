/* SP 800-90B §§3, 5 and 6. Provider handles are deterministic test fixtures. */
#include "entropy_assessment_c.h"
#include "entropy_binary_c.h"
#include "entropy_health_c.h"
#include "entropy_context_c.h"
#include "entropy_iid_c.h"
#include "entropy_permutations_c.h"
#include "entropy_predictors_c.h"
#include "entropy_substrings_c.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

uint16_t crypto_prng_lookup(uint64_t s, uint32_t i) {
    if (s == UINT64_MAX) return 256;
    uint64_t x = s * UINT64_C(0x9e3779b97f4a7c15) + i;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    return (x ^ (x >> 31)) & 255;
}
uint16_t crypto_entropy_lookup(uint64_t s, uint32_t i) { return crypto_prng_lookup(s,i); }

static entropy_binary_record_2_t data(uint32_t n) {
    entropy_binary_record_2_t x = new_entropy_binary_record_2();
    x->length = n;
    x->seq = new_entropy_binary_array_1(n);
    return x;
}
static void *digits(const char *s) {
    entropy_binary_record_2_t x = data(strlen(s));
    for (unsigned i = 0; i < x->length; ++i) x->seq->elems[i] = s[i]-'0';
    return x;
}
static void *hold(entropy_binary_record_2_t x) { ++x->count; return x; }
static void near(const char *name, double got, double want, double eps) {
    printf("%-28s %.10f\n", name, got);
    fflush(stdout);
    if (!isfinite(got) || fabs(got-want)>eps) {
        fprintf(stderr,"%s expected %.12g\n", name, want);
        exit(1);
    }
}
static void estimate(const char *name, void *v, double want, double eps) {
    entropy_binary__estimate_result_t r = v;
    assert(r->usable);
    near(name,crypto_double(r->bits_per_sample),want,eps);
    release_entropy_binary__estimate_result(r);
}
int main(void) {
    const char *bin = "1000111001010101110011000111001010101110";
    estimate("Most common value",entropy_assessment__estimates(digits("01120122010110221021"),true),
             -log2(.4+2.576*sqrt(.4*.6/19)),1e-12);
    estimate("Collision",entropy_binary__collision(digits(bin)),.4483,.0001);
    estimate("Markov",entropy_binary__markov(digits(bin)),.761,.0006);
    entropy_binary_record_2_t zeros=data(6060);
    memset(zeros->seq->elems,0,zeros->length);
    estimate("Compression",entropy_binary__compression(hold(zeros)),0,1e-12);
    estimate("Multi-MCW",entropy_predictors__multi_mcw(hold(zeros),2),0,1e-12);
    estimate("Lag",entropy_predictors__lag(zeros,2),0,1e-12);
    entropy_substrings__tuple_results_t t = entropy_substrings__widths(21,
        entropy_substrings__lcp(digits("220102012120121001000")),3,1,crypto_fp(0),crypto_fp(0));
    assert(t->longest==5 && t->tuple_est->usable && t->lrs_est->usable);
    near("t-tuple",crypto_double(t->tuple_est->bits_per_sample),.273,.0006);
    near("Longest repeated substring",crypto_double(t->lrs_est->bits_per_sample),.6146,.0001);
    release_entropy_substrings__tuple_results(t);
    entropy_predictors__hits_t h=(void*)entropy_context__context_hits(digits("213213131"),3,false);
    assert(h->correct==3 && h->longest==2);
    release_entropy_predictors__hits(h);
    h=(void*)entropy_context__context_hits(digits("2132131312132"),4,true);
    assert(h->correct==4 && h->longest==2);
    estimate("LZ78Y example",entropy_predictors__prediction(3,8,(void*)h),.0191,.0001);

    entropy_binary_record_2_t sample=data(2048);
    for (unsigned i=0;i<sample->length;++i) sample->seq->elems[i]=crypto_prng_lookup(17,i)&3;
    for (int pairs=0;pairs<=1;++pairs) {
        entropy_iid_record_8_t r=entropy_iid__nonbinary_chi(hold(sample),pairs);
        assert(r->applicable && crypto_double(r->pvalue)>=0 && crypto_double(r->pvalue)<=1);
        release_entropy_iid_record_8(r);
    }
    entropy_iid_record_8_t lrs=entropy_iid__lrs_test(hold(sample));
    assert(lrs->applicable && crypto_double(lrs->pvalue)>0);
    release_entropy_iid_record_8(lrs);
    release_entropy_binary_record_2(sample);
    /* One million deterministic bits. Independent sorted 50-bit windows
       gave a longest common prefix of 37. The chi-square values were
       calculated from non-overlapping 11-bit blocks and ten segments. */
    entropy_binary_record_2_t full=data(1000000);
    for (unsigned i=0;i<full->length;++i) full->seq->elems[i]=crypto_prng_lookup(17,i)&1;
    lrs=entropy_iid__lrs_test(hold(full)); assert(lrs->applicable);
    near("Million-symbol LRS test",crypto_double(lrs->pvalue),.973688468449,1e-9);
    release_entropy_iid_record_8(lrs);
    for (int pairs=0;pairs<=1;++pairs) {
        lrs=entropy_iid__binary_chi(hold(full),pairs); assert(lrs->applicable);
        near("Million-symbol chi-square",crypto_double(lrs->pvalue),pairs?.266896484084:.877825760022,1e-8);
        release_entropy_iid_record_8(lrs);
    }
    entropy_binary__estimate_result_t mk=entropy_binary__markov(hold(full));
    assert(mk->usable && crypto_double(mk->bits_per_sample)>.98);
    release_entropy_binary__estimate_result(mk);
    release_entropy_binary_record_2(full);
    const char *permutation="02110302132301020231133321102132";
    assert(!entropy_permutations__iid_permutations(digits(permutation),false,UINT64_MAX));
    assert(entropy_permutations__iid_permutations(digits(permutation),false,200));
    puts("IID tests and 10,000 permutations passed"); fflush(stdout);

    entropy_binary_record_2_t million=data(1000000);
    for (unsigned i=0;i<million->length;++i) million->seq->elems[i]=(i+i/1000)&1;
    double upper=.5+2.576*sqrt(.25/999999);
    estimate("Initial estimate",entropy_assessment__initial_estimate(hold(million),1,true,crypto_fp(1)),
             -log2(upper),1e-12);
    estimate("1000 x 1000 restart",entropy_assessment__restart(hold(million),true,crypto_fp(1)),
             -log2(upper),1e-12);
    for (unsigned i=0;i<million->length;++i) million->seq->elems[i]=i&1;
    entropy_assessment_record_1_t r=entropy_assessment__restart((void*)million,true,crypto_fp(1));
    assert(!r->usable); release_entropy_assessment_record_1(r);
    estimate("Vetted output entropy",entropy_assessment__output_entropy(256,128,128,crypto_fp(128)),
             127,1e-12);
    estimate("Non-vetted cap",entropy_assessment__unvetted(256,128,128,crypto_fp(128),crypto_fp(.5)),
             64,1e-12);
    uint64_t alpha=crypto_fp(ldexp(1.,-20));
    assert(entropy_health__repetition_cutoff(crypto_fp(1),alpha)==21);
    assert(entropy_health__adaptive_cutoff(1024,crypto_fp(1),alpha)==589);
    assert(entropy_health__adaptive_cutoff(512,crypto_fp(8),alpha)==13);
    entropy_health__monitor_t mon=entropy_health__startup(21,1024);
    for (unsigned i=0;i<1024;++i) {
        assert(mon->tested<1024 && !mon->failed);
        mon=entropy_health__monitor_step(21,589,1024,mon,i&1,true);
    }
    ++mon->count;
    assert(entropy_health__may_release(21,1024,mon));
    mon=entropy_health__on_demand(21,1024,mon);
    assert(mon->tested==0);
    for (unsigned i=0;i<21;++i) mon=entropy_health__monitor_step(21,589,1024,mon,0,true);
    assert(mon->failed);
    release_entropy_health__monitor(mon);
    entropy_binary_record_2_t fixture=data(10000);
    assert(fread(fixture->seq->elems,1,fixture->length,stdin)==fixture->length);
    /* NIST SP800-90B_EntropyAssessment cpp/selftest/refdata/rand1_short.res.
       The publication rounds the normal quantile to 2.576. */
    const double tol=.00004;
    estimate("Reference MCV",entropy_assessment__estimates(hold(fixture),true),.96105883,tol);
    estimate("Reference Collision",entropy_binary__collision(hold(fixture)),.69146412,tol);
    estimate("Reference Markov",entropy_binary__markov(hold(fixture)),.98759610,tol);
    estimate("Reference Compression",entropy_binary__compression(hold(fixture)),.61171620,tol);
    t=entropy_substrings__substring_estimates(hold(fixture));
    assert(t->longest==25 && t->tuple_est->usable && t->lrs_est->usable);
    near("Reference t-Tuple",crypto_double(t->tuple_est->bits_per_sample),.86762443,tol);
    near("Reference LRS",crypto_double(t->lrs_est->bits_per_sample),.96262580,tol);
    release_entropy_substrings__tuple_results(t);
    estimate("Reference MultiMCW",entropy_predictors__multi_mcw(hold(fixture),2),.95261806,tol);
    estimate("Reference Lag",entropy_predictors__lag(hold(fixture),2),.94333371,tol);
    estimate("Reference MultiMMC",entropy_context__context_estimate(hold(fixture),2,false),.96161667,tol);
    estimate("Reference LZ78Y",entropy_context__context_estimate(hold(fixture),2,true),.96144625,tol);
    /* An alphabet with two noncontiguous byte values must include the
       three binary estimators when selecting the non-IID minimum. */
    for (unsigned i=0;i<fixture->length;++i) fixture->seq->elems[i]=fixture->seq->elems[i] ? 99 : 12;
    estimate("Non-IID minimum",entropy_assessment__estimates((void*)fixture,false),.61171620,tol);
    puts("SP 800-90B assessments passed");
}
