/* The Ascon designers' SP 800-232 KATs, ascon/ascon-c, crypto_{hash,cxof,aead}.
 * Hash256 counts 1 and 9, XOF128 count 1, CXOF128 count 2, AEAD counts 1 and 530. */
#include "ascon_c.h"
#include "ascon_options_c.h"
#include <assert.h>

static ascon__block_t block(uint64_t lo, uint64_t hi) {
    ascon__block_t b = new_ascon__block();
    b->lo = lo;
    b->hi = hi;
    return b;
}

static ascon__frame_t frame(unsigned blocks, uint8_t bits, uint64_t tail) {
    ascon__frame_t f = new_ascon__frame();
    f->blocks = blocks;
    f->body = new_ascon_array_5(blocks);
    if (blocks) f->body->elems[0] = block(UINT64_C(0x2726252423222120), UINT64_C(0x2f2e2d2c2b2a2928));
    f->tail = block(tail, 0);
    f->tail_bits = bits;
    return f;
}

static void check_lane(uint64_t word, const char *hex) {
    for (unsigned b = 0; b < 8; ++b) {
        unsigned expected;
        assert(sscanf(hex + 2*b, "%2x", &expected) == 1);
        assert(((word >> (8*b)) & 255) == expected);
    }
}

static void hash(int whole, const char *expected) {
    /* Generated constants are borrowed. Retain before passing to consuming functions. */
    ascon__lanes_t s = ascon__hash256_init();
    ++s->count;
    if (whole) s = ascon__absorb(s, UINT64_C(0x0706050403020100));
    ascon__digest256_t h = ascon__hash256_finish(s, 0, 0);
    check_lane(h->w0, expected);
    check_lane(h->w1, expected+16);
    check_lane(h->w2, expected+32);
    check_lane(h->w3, expected+48);
    release_ascon__digest256(h);
}

static void xof(ascon__lanes_t s, const char *expected) {
    s = ascon__finish_hash(s, 0, 0);
    for (unsigned i = 0; i < 8; ++i) {
        check_lane(s->x0, expected + 16*i);
        if (i != 7) s = ascon__squeeze_next(s);
    }
    release_ascon__lanes(s);
}

static ascon__block_t key(void) {
    return block(UINT64_C(0x0706050403020100), UINT64_C(0x0f0e0d0c0b0a0908));
}
static ascon__block_t nonce(void) {
    return block(UINT64_C(0x1716151413121110), UINT64_C(0x1f1e1d1c1b1a1918));
}
static void aead(unsigned blocks, unsigned tailbits, const char *kat) {
    unsigned adbits = blocks ? 8 : 0;
    ascon__sealed_t c = ascon__encrypt(key(), nonce(), frame(0, adbits, 0x30), frame(blocks, tailbits, 5));
    if (kat) {
        if (blocks) {
            check_lane(c->data->body->elems[0]->lo, kat);
            check_lane(c->data->body->elems[0]->hi, kat+16);
            kat += 32;
        }
        check_lane(c->auth->lo, kat);
        check_lane(c->auth->hi, kat+16);
    }
    ++c->count;
    ascon__opened_t p = ascon__decrypt(key(), nonce(), frame(0, adbits, 0x30), c);
    assert(p->valid && p->plaintext->blocks == blocks && p->plaintext->tail_bits == tailbits);
    if (tailbits) assert(p->plaintext->tail->lo == 5);
    if (blocks) assert(p->plaintext->body->elems[0]->hi == UINT64_C(0x2f2e2d2c2b2a2928));
    release_ascon__opened(p);
    c->auth->lo ^= 1;
    p = ascon__decrypt(key(), nonce(), frame(0, adbits, 0x30), c);
    assert(!p->valid && p->plaintext->blocks == 0 && p->plaintext->tail_bits == 0);
    release_ascon__opened(p);
}

static void profiles(void) {
    const uint64_t low=UINT64_C(0x31c9be1182279c4f);
    const uint64_t high=UINT64_C(0xc62e8bee468ff66b);
    for (unsigned bits=32; bits<=128; ++bits) {
        ascon_options__settings_t k=new_ascon_options__settings();
        k->auth_bits=bits;
        k->key=(ascon_options_record_1_t)key();
        k->nonce_mask=(ascon_options_record_1_t)nonce();
        k->count+=2;
        /* The public nonce is zero, so mask XOR nonce equals the published nonce. */
        ascon_options_record_5_t c=ascon_options__encrypt_profile(k,(ascon_options_record_1_t)block(0,0),
                    (ascon_options_record_4_t)frame(0,0,0),(ascon_options_record_4_t)frame(0,0,0));
        uint64_t lo=bits>=64 ? low : low & ((UINT64_C(1)<<bits)-1);
        uint64_t hi=bits==128 ? high : bits<=64 ? 0 : high & ((UINT64_C(1)<<(bits-64))-1);
        assert(c->auth->lo==lo && c->auth->hi==hi);
        ++c->count;
        ascon_options_record_6_t out=ascon_options__decrypt_profile(k,(ascon_options_record_1_t)block(0,0),
                                                   (ascon_options_record_4_t)frame(0,0,0),c);
        assert(out->valid);
        release_ascon_options_record_6(out);
        c->auth->lo^=1;
        out=ascon_options__decrypt_profile(k,(ascon_options_record_1_t)block(0,0),
                                           (ascon_options_record_4_t)frame(0,0,0),c);
        assert(!out->valid && !out->plaintext->blocks && !out->plaintext->tail_bits);
        release_ascon_options_record_6(out);
    }
}
int main(void) {
    profiles();
    hash(0, "0B3BE5850F2F6B98CAF29F8FDEA89B64A1FA70AA249B8F839BD53BAA304D92B2");
    hash(1, "B88E497AE8E6FB641B87EF622EB8F2FCA0ED95383F7FFEBE167ACF1099BA764F");
    ascon__lanes_t s = ascon__xof128_init();
    ++s->count;
    xof(s, "473D5E6164F58B39DFD84AACDB8AE42EC2D91FED33388EE0D960D9B3993295C6"
           "AD77855A5D3B13FE6AD9E6098988373AF7D0956D05A8F1665D2C67D1A3AD10FF");
    ascon__custom_words_t z = new_ascon__custom_words(32);
    memset(z->elems, 0, 32*sizeof(uint64_t));
    z->elems[0] = 0x10;
    xof(ascon__cxof128_init(z, 8),
        "0C93A483E7D574D49FE52CCE03EE646117977D57A8AA57704AB4DAF44B501430"
        "FF6AC11A5D1FD6F2154B5C65728268270C8BB578508487B8965718ADA6272FD6");
    aead(0, 0, "4F9C278211BEC9316BF68F46EE8B2EC6");
    aead(1, 0, "96107D8A29A7529A7941BDC7DF1FE3C6B48691673A22DA04BCC261FEE0FD6A4D");
    aead(1, 3, NULL);
    puts("SP 800-232 hash, XOF, CXOF, AEAD and tag-rejection checks passed.");
    return 0;
}
