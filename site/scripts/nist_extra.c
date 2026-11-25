/* Input-only adapters: expected answers stay in the fetched NIST packets. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
static char output[262145];
static unsigned nibble(char c) { return c<='9' ? c-'0' : (c|32)-'a'+10; }
static uint8_t *unhex(const char *hex, size_t *length) {
    *length = !strcmp(hex,"-") ? 0 : (strlen(hex)+1)/2;
    uint8_t *bytes=calloc(*length+16,1);
    size_t odd=strlen(hex)%2;
    for(size_t i=0;i<*length;i++) {
        long p=(long)(2*i)-(long)odd;
        bytes[i]=(p<0 ? 0 : nibble(hex[p])*16)+nibble(hex[p+1]);
    }
    return bytes;
}
static void hexout(const uint8_t *bytes,size_t count,char *out) {
    const char *digits="0123456789abcdef";
    for(size_t i=0;i<count;i++){out[2*i]=digits[bytes[i]>>4];out[2*i+1]=digits[bytes[i]&15];}
    out[2*count]=0;
}
#if defined(NIST_ASCON)
#include "ascon_options_c.h"
static uint64_t lane(const uint8_t *p,unsigned bits) {
    uint64_t value=0;
    for(unsigned i=0;i<bits;i++) value |= (uint64_t)((p[i/8]>>(i%8))&1)<<i;
    return value;
}
static void laneout(uint64_t value,uint8_t *p,unsigned bits) {
    for(unsigned i=0;i<(bits+7)/8;i++) p[i]=(uint8_t)(value>>(8*i));
    if(bits%8) p[bits/8]&=(1u<<(bits%8))-1;
}
static ascon__block_t block(const uint8_t *p,unsigned bits) {
    ascon__block_t b=new_ascon__block();
    b->lo=lane(p,bits<64?bits:64);b->hi=bits>64 ? lane(p+8,bits-64) : 0;return b;
}
static ascon__frame_t frame(const uint8_t *p,unsigned bits) {
    ascon__frame_t f=new_ascon__frame();f->blocks=bits/128;f->tail_bits=bits%128;
    f->body=new_ascon_array_5(f->blocks);
    for(unsigned i=0;i<f->blocks;i++) f->body->elems[i]=block(p+16*i,128);
    f->tail=block(p+16*f->blocks,f->tail_bits);return f;
}
static void frameout(ascon__frame_t f,uint8_t *p) {
    for(unsigned i=0;i<f->blocks;i++){laneout(f->body->elems[i]->lo,p+16*i,64);laneout(f->body->elems[i]->hi,p+16*i+8,64);}
    p+=16*f->blocks;laneout(f->tail->lo,p,f->tail_bits<64?f->tail_bits:64);
    if(f->tail_bits>64)laneout(f->tail->hi,p+8,f->tail_bits-64);
}
static const char *ascon_hash(char **a) {
    unsigned bits=strtoul(a[2],0,10),outbits=strtoul(a[4],0,10),custombits=strtoul(a[5],0,10);
    if(outbits>1048576 || custombits>2048)return "ERROR: Ascon lengths";
    size_t n;uint8_t *msg=unhex(a[3],&n),*custom=unhex(a[6],&n);
    ascon__lanes_t state;
    if(!strcmp(a[1],"CXOF128")) {
        ascon__custom_words_t z=new_ascon__custom_words(32);
        for(unsigned i=0;i<32;i++)z->elems[i]=i*64<custombits?lane(custom+i*8,custombits-i*64<64?custombits-i*64:64):0;
        state=ascon__cxof128_init(z,custombits);
    } else {state=!strcmp(a[1],"Hash256")?ascon__hash256_init():ascon__xof128_init();state->count++;}
    for(unsigned i=0;i<bits/64;i++)state=ascon__absorb(state,lane(msg+i*8,64));
    state=ascon__finish_hash(state,lane(msg+(bits/64)*8,bits%64),bits%64);
    uint8_t *result=calloc((outbits+7)/8+8,1);
    for(unsigned i=0;i<outbits;i+=64){laneout(state->x0,result+i/8,outbits-i<64?outbits-i:64);if(i+64<outbits)state=ascon__squeeze_next(state);}
    release_ascon__lanes(state);hexout(result,(outbits+7)/8,output);free(msg);free(custom);free(result);return output;
}
static const char *ascon_aead(char **a) {
    unsigned enc=atoi(a[1]),adbits=atoi(a[5]),bits=atoi(a[7]),tagbits=atoi(a[9]);
    size_t n;uint8_t *key=unhex(a[2],&n),*mask=unhex(a[3],&n),*nonce=unhex(a[4],&n),*ad=unhex(a[6],&n),*msg=unhex(a[8],&n),*tag=unhex(a[10],&n);
    ascon_options__settings_t settings=new_ascon_options__settings();
    settings->key=block(key,128);settings->nonce_mask=block(mask,128);settings->auth_bits=tagbits;
    uint8_t *result=calloc((bits+7)/8+32,1);
    if(enc){
        ascon__sealed_t c=(ascon__sealed_t)ascon_options__encrypt_profile(settings,block(nonce,128),frame(ad,adbits),frame(msg,bits));
        frameout(c->data,result);unsigned size=(bits+7)/8;
        laneout(c->auth->lo,result+size,tagbits<64?tagbits:64);
        if(tagbits>64)laneout(c->auth->hi,result+size+8,tagbits-64);
        hexout(result,size+(tagbits+7)/8,output);release_ascon__sealed(c);
    }else{
        ascon__sealed_t c=new_ascon__sealed();c->data=frame(msg,bits);c->auth=block(tag,tagbits);
        ascon__opened_t p=(ascon__opened_t)ascon_options__decrypt_profile(settings,block(nonce,128),frame(ad,adbits),c);
        if(p->valid){frameout(p->plaintext,result);hexout(result,(bits+7)/8,output);}else strcpy(output,"false");
        release_ascon__opened(p);
    }
    free(key);free(mask);free(nonce);free(ad);free(msg);free(tag);free(result);return output;
}
#endif
#if defined(NIST_ECDSA) || defined(NIST_ECDH)
#include "prime_curve_c.h"
#if defined(NIST_ECDSA)
#include "ecdsa_signing_c.h"
#endif
static prime_curve_record_5_t ecbytes(const char *hex){
    size_t n;uint8_t *data=unhex(hex,&n);prime_curve_record_5_t b=new_prime_curve_record_5();
    b->length=n;b->seq=new_prime_curve_array_4(n);memcpy(b->seq->elems,data,n);free(data);return b;
}
static prime_curve_record_1_t scalar(unsigned c,const char *hex){return (prime_curve_record_1_t)crypto_limbs__from_bytes(nist_prime_curves__width(c),(crypto_limbs_record_4_t)ecbytes(hex),true);}
static prime_curve__affine_t point(unsigned c,const char *x,const char *y){
    prime_curve__affine_t q=new_prime_curve__affine();q->finite=true;
    q->x=(prime_curve_record_1_t)scalar(c,x);q->y=(prime_curve_record_1_t)scalar(c,y);return q;
}
#if defined(NIST_ECDSA)
static const char *ecdsa(char **a){
    unsigned c=atoi(a[1]),h=atoi(a[2]);
    bool valid=ecdsa_signing__verify(c,h,point(c,a[3],a[4]),(ecdsa_signing_record_1_t)ecbytes(a[7]),
        (ecdsa_signing_record_3_t)scalar(c,a[5]),(ecdsa_signing_record_3_t)scalar(c,a[6]));
    return valid?"true":"false";
}
#endif
static const char *ecdh(char **a){
    unsigned c=atoi(a[1]);prime_curve__secret_result_t r=prime_curve__cdh(c,(prime_curve_record_1_t)scalar(c,a[2]),point(c,a[3],a[4]));
    if(r->valid)hexout(r->value->seq->elems,r->value->length,output);else strcpy(output,"false");
    release_prime_curve__secret_result(r);return output;
}
#endif
#if defined(NIST_AES_MODES)
#include "aes_modes_c.h"
static aes_modes_array_1_t modebytes(const char *hex){
    size_t n;uint8_t *data=unhex(hex,&n);aes_modes_array_1_t b=new_aes_modes_array_1(n);memcpy(b->elems,data,n);free(data);return b;
}
static const char *modes(char **a){
    aes_modes_array_1_t k=modebytes(a[3]);
    aes_modes__mode_key_adt_t key=k->size==16?con_aes_modes__mk128(k):k->size==24?con_aes_modes__mk192(k):con_aes_modes__mk256(k);
    unsigned enc=atoi(a[2]);aes_modes_array_1_t result;
    if(!strcmp(a[1],"cbc"))result=enc?aes_modes__cbc_encrypt(key,modebytes(a[4]),modebytes(a[5])):aes_modes__cbc_decrypt(key,modebytes(a[4]),modebytes(a[5]));
    else {aes_modes__feedback_t f=!strcmp(a[1],"ofb")?aes_modes__ofb(key,modebytes(a[4]),modebytes(a[5]),128):aes_modes__cfb(key,modebytes(a[4]),modebytes(a[5]),128,!enc);f->data->count++;result=f->data;release_aes_modes__feedback(f);}
    hexout(result->elems,result->size,output);release_aes_modes_array_1(result);return output;
}
#endif
const char *nist_eval(const char *input) {
    char *copy=strdup(input),*save=0,*args[20];unsigned n=0;
    for(char *p=strtok_r(copy," ",&save);p && n<20;p=strtok_r(0," ",&save))args[n++]=p;
    const char *answer="ERROR: unknown vector operation";
#if defined(NIST_ASCON)
    if(n==7 && !strcmp(args[0],"ascon-hash"))answer=ascon_hash(args);
    if(n==11 && !strcmp(args[0],"ascon-aead"))answer=ascon_aead(args);
#endif
#if defined(NIST_ECDSA) || defined(NIST_ECDH)
#if defined(NIST_ECDSA)
    if(n==8 && !strcmp(args[0],"ecdsa"))answer=ecdsa(args);
#endif
    if(n==5 && !strcmp(args[0],"ecdh"))answer=ecdh(args);
#endif
#if defined(NIST_AES_MODES)
    if(n==6 && !strcmp(args[0],"aes-modes"))answer=modes(args);
#endif
    free(copy);return answer;
}
