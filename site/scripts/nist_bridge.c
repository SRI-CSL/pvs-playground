/* Thin adapters from NIST input fields to generated PVS2C entry points.
 * Expected results stay in the independent NIST data, outside this module. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "pvslib.h"
#ifdef NIST_AES
#include "aes_fips197_c.h"
#endif
#ifdef NIST_SHA
#include "secure_hash_c.h"
#endif
#if defined(NIST_SHA3) || defined(NIST_SHAKE)
#include "keccak_c.h"
#endif
#ifdef NIST_HMAC
#include "keyed_hash_c.h"
#endif
#ifdef NIST_HMAC_DRBG
#include "hmac_drbg_c.h"
#endif
#ifdef NIST_HASH_DRBG
#include "hash_drbg_c.h"
#endif
#ifdef NIST_CTR_DRBG
#include "ctr_drbg_c.h"
#endif
#ifdef NIST_KDF_HMAC
#include "prf_kdf_c.h"
#endif
#ifdef NIST_KDF_CMAC
#include "cmac_kdf_c.h"
#endif
#ifdef NIST_PBKDF
#include "password_kdf_c.h"
#endif
#ifdef NIST_ED25519
#include "ed25519_c.h"
#endif
#ifdef NIST_ED448
#include "ed448_c.h"
#endif

static char actual[131073];
static int invalid;
static unsigned number(const char *s) {
    char *end;
    unsigned long n = strtoul(s, &end, 10);
    if (!*s || *end || n > UINT32_MAX) invalid = 1;
    return (unsigned)n;
}
static unsigned length(const char *hex) {
    if (!strcmp(hex, "-")) return 0;
    size_t n = strlen(hex);
    if (n % 2 || n > 1048576) { invalid = 1; return 0; }
    return (unsigned)(n / 2);
}
static unsigned nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    invalid = 1;
    return 0;
}
static void decode(uint8_t *out, const char *hex, unsigned n) {
    for (unsigned i = 0; i < n; ++i) out[i] = (uint8_t)(16 * nibble(hex[2*i]) + nibble(hex[2*i+1]));
}
static void encode(const uint8_t *data, unsigned n) {
    static const char digits[] = "0123456789abcdef";
    if (n > (sizeof(actual)-1)/2) { invalid = 1; return; }
    for (unsigned i = 0; i < n; ++i) { actual[2*i] = digits[data[i] >> 4]; actual[2*i+1] = digits[data[i] & 15]; }
    actual[2*n] = 0;
}
#define BYTES(name, record, array) \
static record##_t name(const char *hex) { \
    unsigned n = length(hex); record##_t x = new_##record(); \
    x->length = n; x->seq = new_##array(n); decode(x->seq->elems, hex, n); return x; }
#define FINISH(x, release) do { encode((x)->seq->elems, (x)->length); release(x); } while (0)

#ifdef NIST_AES
static aes_fips197__block_t aes_bytes(const char *hex) {
    unsigned n = length(hex); aes_fips197__block_t x = new_aes_fips197__block(n);
    decode(x->elems, hex, n); return x;
}
static void aes_case(char **v) {
    unsigned n = length(v[2]);
    if ((n != 16 && n != 24 && n != 32) || length(v[3]) != 16) { invalid = 1; return; }
    aes_fips197__block_t k = aes_bytes(v[2]), m = aes_bytes(v[3]), out;
    int enc = number(v[1]);
    if (n == 16) out = enc ? aes_fips197__aes128_encrypt(m,k) : aes_fips197__aes128_decrypt(m,k);
    else if (n == 24) out = enc ? aes_fips197__aes192_encrypt(m,k) : aes_fips197__aes192_decrypt(m,k);
    else out = enc ? aes_fips197__aes256_encrypt(m,k) : aes_fips197__aes256_decrypt(m,k);
    encode(out->elems, out->size); release_aes_fips197__block(out);
}
#endif
#ifdef NIST_SHA
BYTES(sha_bytes, secure_hash_record_1, secure_hash_array_0)
typedef secure_hash_record_1_t (*sha_bits)(secure_hash_record_1_t,uint8_t,uint8_t);
static const sha_bits sha_functions[] = {secure_hash__sha1_bits,secure_hash__sha224_bits,secure_hash__sha256_bits,
    secure_hash__sha384_bits,secure_hash__sha512_bits,secure_hash__sha512_224_bits,secure_hash__sha512_256_bits};
static void sha_case(char **v, int monte) {
    unsigned alg = number(v[1]); if (alg >= 7) { invalid=1; return; }
    if (!monte) {
        unsigned bits = number(v[2]), n = bits/8;
        if (length(v[3]) != (bits+7)/8) { invalid=1; return; }
        secure_hash_record_1_t m = new_secure_hash_record_1();m->length=n;m->seq=new_secure_hash_array_0(n);
        decode(m->seq->elems,v[3],n);
        uint8_t tail = bits%8 ? (uint8_t)(16*nibble(v[3][2*n])+nibble(v[3][2*n+1])) : 0;
        secure_hash_record_1_t out = sha_functions[alg](m,tail,bits%8);
        FINISH(out, release_secure_hash_record_1);
    } else {
        unsigned n = length(v[2]); uint8_t a[64],b[64],c[64];
        if (n > 64) { invalid=1; return; }
        decode(a,v[2],n); memcpy(b,a,n); memcpy(c,a,n);
        for (unsigned i=0;i<1000;++i) {
            secure_hash_record_1_t m=new_secure_hash_record_1();m->length=3*n;m->seq=new_secure_hash_array_0(3*n);
            memcpy(m->seq->elems,a,n);memcpy(m->seq->elems+n,b,n);memcpy(m->seq->elems+2*n,c,n);
            secure_hash_record_1_t out=sha_functions[alg](m,0,0);
            if (out->length!=n) { release_secure_hash_record_1(out);invalid=1;return; }
            memcpy(a,b,n);memcpy(b,c,n);memcpy(c,out->seq->elems,n);release_secure_hash_record_1(out);
        }
        encode(c,n);
    }
}
#endif
#if defined(NIST_SHA3) || defined(NIST_SHAKE)
BYTES(keccak_bytes, keccak_record_4, keccak_array_3)
typedef keccak_record_4_t (*sha3_function)(keccak_record_4_t);
static const sha3_function sha3_functions[]={keccak__sha3_224,keccak__sha3_256,keccak__sha3_384,keccak__sha3_512};
static void keccak_case(char **v, int monte) {
    unsigned alg=number(v[1]);if(alg>=6){invalid=1;return;}
    if (!monte) {
        unsigned bits=number(v[2]), outbits=number(v[4]);
        if(bits%8 || outbits%8 || length(v[3])!=bits/8){invalid=1;return;}
        keccak_record_4_t m=keccak_bytes(v[3]);
        keccak_record_4_t out=alg<4?sha3_functions[alg](m):alg==4?keccak__shake128(m,outbits/8):keccak__shake256(m,outbits/8);
        FINISH(out,release_keccak_record_4);
    } else {
        if(alg>=4){invalid=1;return;}
        keccak_record_4_t out=keccak_bytes(v[2]);
        for(unsigned i=0;i<1000;++i)out=sha3_functions[alg](out);
        FINISH(out,release_keccak_record_4);
    }
}
/* SHA3VS section 6.3.3: each checkpoint contains 1,000 XOF calls. */
static void shake_monte_case(char **v) {
    unsigned alg=number(v[1]), low=number(v[3]), high=number(v[4]),n=number(v[5]);
    uint8_t message[16]={0};unsigned seed_length=length(v[2]);
    if((alg!=4 && alg!=5) || low<2 || high>8192 || low>high || n<low || n>high){invalid=1;return;}
    decode(message,v[2],seed_length<16?seed_length:16);
    for(unsigned i=0;i<1000;++i) {
        keccak_record_4_t m=new_keccak_record_4();m->length=16;m->seq=new_keccak_array_3(16);memcpy(m->seq->elems,message,16);
        keccak_record_4_t out=alg==4?keccak__shake128(m,n):keccak__shake256(m,n);
        memset(message,0,16);memcpy(message,out->seq->elems,n<16?n:16);
        if(i==999)encode(out->seq->elems,n);
        n=low+((unsigned)out->seq->elems[n-2]*256+out->seq->elems[n-1])%(high-low+1);
        release_keccak_record_4(out);
    }
}
#endif
#ifdef NIST_HMAC
BYTES(hmac_bytes,keyed_hash_record_1,keyed_hash_array_0)
static void hmac_case(char **v) {
    unsigned alg=number(v[1]),n=number(v[4]);if(alg>=7 || n>64){invalid=1;return;}
    keyed_hash_record_1_t out=keyed_hash__hmac_truncated(alg,hmac_bytes(v[2]),hmac_bytes(v[3]),n);
    FINISH(out,release_keyed_hash_record_1);
}
#endif

/* Both hash DRBGs have the same operational sequence and different generated types. */
#define DRBG(name, bytes_record, bytes_array, state_type, result_type, instantiate, reseed_fn, generate_fn, release_result) \
BYTES(name##_bytes,bytes_record,bytes_array) \
static void name##_case(char **v) { \
    unsigned alg=number(v[1]),pr=number(v[3]),rs=number(v[4]),bits=number(v[5]); \
    if(alg>=7 || bits==0 || bits>524288){invalid=1;return;} \
    state_type s=instantiate(alg,name##_bytes(v[6]),name##_bytes(v[7]),name##_bytes(v[8])); \
    if(rs)s=reseed_fn(s,name##_bytes(v[9]),name##_bytes(v[10])); \
    if(pr)s=reseed_fn(s,name##_bytes(v[11]),name##_bytes(v[12])); \
    result_type first=generate_fn(s,bits,name##_bytes(pr?"-":v[12])); \
    if(!first->success){release_result(first);invalid=1;return;} \
    first->current->count++;s=first->current;release_result(first); \
    if(pr)s=reseed_fn(s,name##_bytes(v[13]),name##_bytes(v[14])); \
    result_type second=generate_fn(s,bits,name##_bytes(pr?"-":v[14])); \
    if(second->success)encode(second->data->seq->elems,second->data->length);else invalid=1; \
    release_result(second); }
#ifdef NIST_HMAC_DRBG
DRBG(hmac_drbg,hmac_drbg_record_1,hmac_drbg_array_0,hmac_drbg__state_t,hmac_drbg__result_t,
     hmac_drbg__instantiate,hmac_drbg__reseed,hmac_drbg__generate,release_hmac_drbg__result)
#endif
#ifdef NIST_HASH_DRBG
DRBG(hash_drbg,hash_drbg_record_1,hash_drbg_array_0,hash_drbg__hash_state_t,hash_drbg__hash_result_t,
     hash_drbg__hash_instantiate,hash_drbg__hash_reseed,hash_drbg__hash_generate,release_hash_drbg__hash_result)
#endif
#ifdef NIST_CTR_DRBG
BYTES(ctr_bytes,ctr_drbg_record_1,ctr_drbg_array_0)
static void ctr_case(char **v) {
    unsigned alg=number(v[1]),df=number(v[2]),pr=number(v[3]),rs=number(v[4]),bits=number(v[5]);
    if(alg>=3 || bits==0 || bits>524288){invalid=1;return;}
    ctr_drbg__ctr_state_t s=df?ctr_drbg__instantiate_df(alg,ctr_bytes(v[6]),ctr_bytes(v[7]),ctr_bytes(v[8])):
        ctr_drbg__instantiate_direct(alg,ctr_bytes(v[6]),ctr_bytes(v[8]));
    if(rs)s=df?ctr_drbg__ctr_reseed_df(s,ctr_bytes(v[9]),ctr_bytes(v[10])):ctr_drbg__ctr_reseed_direct(s,ctr_bytes(v[9]),ctr_bytes(v[10]));
    if(pr)s=df?ctr_drbg__ctr_reseed_df(s,ctr_bytes(v[11]),ctr_bytes(v[12])):ctr_drbg__ctr_reseed_direct(s,ctr_bytes(v[11]),ctr_bytes(v[12]));
    ctr_drbg__ctr_result_t first=ctr_drbg__ctr_generate(s,bits,ctr_bytes(pr?"-":v[12]));
    if(!first->success){release_ctr_drbg__ctr_result(first);invalid=1;return;}
    first->current->count++;s=first->current;release_ctr_drbg__ctr_result(first);
    if(pr)s=df?ctr_drbg__ctr_reseed_df(s,ctr_bytes(v[13]),ctr_bytes(v[14])):ctr_drbg__ctr_reseed_direct(s,ctr_bytes(v[13]),ctr_bytes(v[14]));
    ctr_drbg__ctr_result_t second=ctr_drbg__ctr_generate(s,bits,ctr_bytes(pr?"-":v[14]));
    if(second->success)encode(second->data->seq->elems,second->data->length);else invalid=1;
    release_ctr_drbg__ctr_result(second);
}
#endif
#ifdef NIST_KDF_HMAC
BYTES(kdf_bytes,prf_kdf_record_1,prf_kdf_array_0)
static void kdf_case(char **v) {
    prf_kdf_record_6_t out=prf_kdf__kbkdf(number(v[1]),kdf_bytes(v[4]),number(v[2]),number(v[3]),kdf_bytes(v[5]),kdf_bytes(v[6]),number(v[7]));
    if(out->ok)encode(out->data->seq->elems,out->data->length);else invalid=1;
    release_prf_kdf_record_6(out);
}
#endif
#ifdef NIST_KDF_CMAC
BYTES(cmac_bytes,cmac_kdf_record_1,cmac_kdf_array_0)
static void cmac_kdf_case(char **v) {
    unsigned alg=number(v[1]),n=length(v[4]);
    if(alg>=3 || n!=16+8*alg){invalid=1;return;}
    aes_modes_array_1_t a=new_aes_modes_array_1(n);decode(a->elems,v[4],n);
    aes_modes__mode_key_adt_t key=alg==0?con_aes_modes__mk128(a):alg==1?con_aes_modes__mk192(a):con_aes_modes__mk256(a);
    cmac_kdf_record_6_t out=cmac_kdf__kbkdf_cmac(key,number(v[2]),number(v[3]),cmac_bytes(v[5]),cmac_bytes(v[6]),number(v[7]));
    if(out->ok)encode(out->data->seq->elems,out->data->length);else invalid=1;
    release_cmac_kdf_record_6(out);
}
#endif
#ifdef NIST_PBKDF
BYTES(password_bytes,password_kdf__salt_buffer,password_kdf_array_0)
static void pbkdf_case(char **v) {
    password_kdf__salt_buffer_t out=password_kdf__pbkdf2(number(v[1]),password_bytes(v[2]),password_bytes(v[3]),number(v[4]),number(v[5]));
    FINISH(out,release_password_kdf__salt_buffer);
}
#endif
#ifdef NIST_ED25519
BYTES(ed25519_bytes,ed25519__scalar_bytes,ed25519_array_2)
static void ed25519_case(char **v) {
    if(!strcmp(v[1],"key")) {ed25519__scalar_bytes_t out=ed25519__public_key(ed25519_bytes(v[2]));FINISH(out,release_ed25519__scalar_bytes);}
    else if(!strcmp(v[1],"sign")) {
        ed25519__scalar_bytes_t out=number(v[2])?ed25519__sign_ph(ed25519_bytes(v[3]),ed25519_bytes(v[4]),ed25519_bytes(v[5])):
            ed25519__sign(ed25519_bytes(v[3]),ed25519_bytes(v[4]));FINISH(out,release_ed25519__scalar_bytes);
    } else {
        bool out=number(v[2])?ed25519__verify_ph(ed25519_bytes(v[3]),ed25519_bytes(v[4]),ed25519_bytes(v[6]),ed25519_bytes(v[5])):
            ed25519__verify(ed25519_bytes(v[3]),ed25519_bytes(v[4]),ed25519_bytes(v[6]));strcpy(actual,out?"true":"false");
    }
}
#endif
#ifdef NIST_ED448
BYTES(ed448_bytes,ed448__key_bytes,ed448_array_3)
static void ed448_case(char **v) {
    if(!strcmp(v[1],"key")) {ed448__key_bytes_t out=ed448__public_key(ed448_bytes(v[2]));FINISH(out,release_ed448__key_bytes);}
    else if(!strcmp(v[1],"sign")) {
        ed448__key_bytes_t out=number(v[2])?ed448__sign_ph(ed448_bytes(v[3]),ed448_bytes(v[4]),ed448_bytes(v[5])):
            ed448__sign(ed448_bytes(v[3]),ed448_bytes(v[4]),ed448_bytes(v[5]));FINISH(out,release_ed448__key_bytes);
    } else {
        bool out=number(v[2])?ed448__verify_ph(ed448_bytes(v[3]),ed448_bytes(v[4]),ed448_bytes(v[6]),ed448_bytes(v[5])):
            ed448__verify(ed448_bytes(v[3]),ed448_bytes(v[4]),ed448_bytes(v[6]),ed448_bytes(v[5]));strcpy(actual,out?"true":"false");
    }
}
#endif

const char *nist_eval(const char *input) {
    char *copy=strdup(input), *v[20], *token=strtok(copy," ");unsigned n=0;
    invalid=0;actual[0]=0;
    while(token && n<20){v[n++]=token;token=strtok(NULL," ");}
    if(token || !n){free(copy);return "ERROR: invalid vector input";}
    if(0){}
#ifdef NIST_AES
    else if(!strcmp(v[0],"aes") && n==4)aes_case(v);
#endif
#ifdef NIST_SHA
    else if(!strcmp(v[0],"sha") && n==5)sha_case(v,0);
    else if(!strcmp(v[0],"sha-monte") && n==3)sha_case(v,1);
#endif
#if defined(NIST_SHA3) || defined(NIST_SHAKE)
    else if((!strcmp(v[0],"sha3") || !strcmp(v[0],"shake")) && n==5)keccak_case(v,0);
    else if(!strcmp(v[0],"sha3-monte") && n==3)keccak_case(v,1);
    else if(!strcmp(v[0],"shake-monte") && n==6)shake_monte_case(v);
#endif
#ifdef NIST_HMAC
    else if(!strcmp(v[0],"hmac") && n==5)hmac_case(v);
#endif
#ifdef NIST_HMAC_DRBG
    else if(!strcmp(v[0],"hmac-drbg") && n==15)hmac_drbg_case(v);
#endif
#ifdef NIST_HASH_DRBG
    else if(!strcmp(v[0],"hash-drbg") && n==15)hash_drbg_case(v);
#endif
#ifdef NIST_CTR_DRBG
    else if(!strcmp(v[0],"ctr-drbg") && n==15)ctr_case(v);
#endif
#ifdef NIST_KDF_HMAC
    else if(!strcmp(v[0],"kdf-hmac") && n==8)kdf_case(v);
#endif
#ifdef NIST_KDF_CMAC
    else if(!strcmp(v[0],"kdf-cmac") && n==8)cmac_kdf_case(v);
#endif
#ifdef NIST_PBKDF
    else if(!strcmp(v[0],"pbkdf") && n==6)pbkdf_case(v);
#endif
#ifdef NIST_ED25519
    else if(!strcmp(v[0],"ed25519") && ((n==3 && !strcmp(v[1],"key")) || (n==6 && !strcmp(v[1],"sign")) || (n==7 && !strcmp(v[1],"verify"))))ed25519_case(v);
#endif
#ifdef NIST_ED448
    else if(!strcmp(v[0],"ed448") && ((n==3 && !strcmp(v[1],"key")) || (n==6 && !strcmp(v[1],"sign")) || (n==7 && !strcmp(v[1],"verify"))))ed448_case(v);
#endif
    else invalid=1;
    free(copy);return invalid?"ERROR: invalid vector or rejected operation":actual;
}
