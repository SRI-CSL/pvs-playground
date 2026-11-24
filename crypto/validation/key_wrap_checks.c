/* SP 800-38F. Samples from NIST's kwtestvectors.zip, indexed in the table
 * by mode, cipher designation, key size and expected integrity outcome. */
#include "key_wrap_c.h"
#include <assert.h>

static key_wrap_array_1_t octets(const char *hex) {
    size_t n = strlen(hex)/2;
    key_wrap_array_1_t a = new_key_wrap_array_1(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned v;
        assert(sscanf(hex+2*i, "%2x", &v) == 1);
        a->elems[i] = (uint8_t)v;
    }
    return a;
}

static key_wrap_record_2_t buffer(const char *hex) {
    key_wrap_record_2_t b = new_key_wrap_record_2();
    b->seq = octets(hex);
    b->length = b->seq->size;
    return b;
}

static aes_modes__mode_key_adt_t key(const char *hex) {
    key_wrap_array_1_t k = octets(hex);
    if (k->size == 16) return con_aes_modes__mk128((aes_modes_array_1_t)k);
    if (k->size == 24) return con_aes_modes__mk192((aes_modes_array_1_t)k);
    assert(k->size == 32);
    return con_aes_modes__mk256((aes_modes_array_1_t)k);
}

static void expect(key_wrap__result_adt_t r, const char *expected) {
    assert((r->key_wrap__result_adt_index == 0) == (expected != NULL));
    if (expected != NULL) {
        key_wrap_record_2_t b = ((key_wrap__success_t)r)->data;
        key_wrap_array_1_t e = octets(expected);
        assert(b->length == e->size && memcmp(b->seq->elems,e->elems,e->size) == 0);
        release_key_wrap_array_1(e);
    }
    release_key_wrap__result_adt(r);
}

static void check(bool padded, bool inverse_cipher, const char *k, const char *c, const char *p) {
    if (p != NULL) {
        expect(padded ? key_wrap__kwp_wrap(key(k),buffer(p),inverse_cipher)
                      : key_wrap__kw_wrap(key(k),buffer(p),inverse_cipher), c);
    }
    expect(padded ? key_wrap__kwp_unwrap(key(k),buffer(c),inverse_cipher)
                  : key_wrap__kw_unwrap(key(k),buffer(c),inverse_cipher), p);
}

int main(void) {
    check(true,false,"49319c331231cd6bf74c2f70b07fcc5c",
          "9c211f32f8b341f32b052fed5f31a387",
          "e4");
    check(true,false,"30be7ff51227f0eef786cb7be2482510",
          "7f61a0a8b2fe7803f2947d233ec3a255",
          NULL);
    check(true,true,"7877f11e1a2d530a0b27274d4e6d7f2c",
          "ea53d73d75f5f0642c64d4715d1c131a",
          "52");
    check(true,true,"6396fd2a833648b1844c93334ecf8fd1",
          "e33984ab4f8ea18390a9d9f329965cab",
          NULL);
    check(true,false,"58e7c85b60c7675002bd66e290d20cc694279f0bfc766840",
          "f2edd87dabb4a6ae568662f20fcc4770",
          "76");
    check(true,false,"21fb6600c1d34a74adee67612672593a86cf235421735350",
          "56b45c49c3e379b18d9c38b6423db133",
          NULL);
    check(true,true,"427c6c0a2cc30bbe0cd9fc6b11c29f8cfe64df6ab0379433",
          "f5dcb63193a377a526db98a852db6099",
          "98");
    check(true,true,"45bc1a8d26266e0c9d5220a973fc4b435b36bd17c7f92fc2",
          "200c7e2b59ed27214929fa90dbdd46d6",
          NULL);
    check(true,false,"20e4ff6a88ffa9a2818b81702793d8a016722c2fa1ff445f24b9db293cb12069",
          "85011dc927b167f411b0b8e21b11d819",
          "d2");
    check(true,false,"c32cb3e1e41a4b9f4de79989957866f5dd48dba38c22a6ebb80e14c84bdd9534",
          "c29b05c2619a58ecc1d239e7a34273cd",
          NULL);
    check(true,true,"4c02c72f62b4e1e1e99f5b261752ab1967654b7b9a88eecf2865b3e0c1798fb8",
          "4abf38040804263aa66a153350e65a66",
          "75");
    check(true,true,"7e1077271d8c710f3fecb08d414d2992ba9c6c91be40ecbf9cf1112bd8e60fe5",
          "60dfd5986b5c174d18b1fb2522c3d5d0",
          NULL);
    check(false,false,"1cbd2f79078b9500fae23696311953eb",
          "ecbd7a17c5da3cfdfe2225d2bf9ac7abce78c2b2aefa6eac",
          "9c4e675277a3bdc3a071048b327a011e");
    check(false,false,"5d4899ee66beff1bda1fc717a1ad4c50",
          "bb7fd0bce778bd775e4e88d904d26a7134364c53a6c493a0",
          NULL);
    check(false,true,"7aa9e9e3c6b2916b4b62ac06074d14e8",
          "110f6ba8d4aa2a24f0abfd2cd351ebb6cdfafb35941bbe33",
          "77a44e843e1f85707cc7e149e5f873be");
    check(false,true,"a377331672bf423c0e523d39bb549493",
          "1f3c7f161fa59b93b3df55ffa092b0e557f92397a0d40159",
          NULL);
    check(false,false,"26045402548ee6196fc0a60208ffde21137ddb1c6c5d2ba0",
          "fcd55c2c60ff6de19ec3e6b13490c2821f0c565abf10be2d",
          "94b8276743184d086962ce6c4e63bd53");
    check(false,false,"9200a0f688d86c0b6bfd9abeff66341684a373fe3f9a3057",
          "5c685c8596e374710fe327bafc45cd09190215fdcc03d010",
          NULL);
    check(false,true,"fd9f4c93416fe7cb53002a5b011a2d4695ec64460af59826",
          "5e25074c8d7e82f0224c151db4af874578d55dfa5cc98952",
          "1097eb6e48232f5c5f15fb5d1c8b5f44");
    check(false,true,"17b748d603b417844dbcc3e20da4e1889526a241e3836ceb",
          "2b1c48f42551855f375b534dc06476f221f267002314f291",
          NULL);
    check(false,false,"80aa997327a4806b6a7a41a52b86c3710386f932786ef79676fafb90b8263c5f",
          "423c960d8a2ac4c1d33d3d977bf0a91559f99c8acd293d43",
          "0a256ba75cfa03aaa02ba94203f15baa");
    check(false,false,"08c936b25b567a0aa679c29f201bf8b190327df0c2563e39cee061f149f4d91b",
          "e227eb8ae9d239ccd8928adec39c28810ca9b3dc1f366444",
          NULL);
    check(false,true,"d660410f4c4eeb7b0f9dfb7b5dcd4eabac1cfcbb072b1825c96026f6a64dd7dd",
          "157629ebd041bf5b9f354bbda3a4906e7ec84cac6d7d7702",
          "4142bea750ab0f332e9ea5185157af13");
    check(false,true,"86d1ce44183eee696c70a30f598ee1e51f0650c12b901c03451e083b1ce9d956",
          "c992214acf5c95bac5497c90bed8ae3f97e0ca08f1943d4d",
          NULL);
    expect(key_wrap__kw_wrap(key("000102030405060708090a0b0c0d0e0f"),buffer("00"),false),NULL);
    expect(key_wrap__kwp_wrap(key("000102030405060708090a0b0c0d0e0f"),buffer(""),false),NULL);
    puts("SP 800-38F KW and KWP vectors passed.");
    return 0;
}
