/* SP 800-38E. NIST XTSVS, XTSGenAES128/256.rsp (128-bit hex tweak).
 * Exercise every distinct data-unit length in those two response files. */
#include "xts_c.h"
#include <assert.h>

static xts_array_1_t octets(const char *hex, size_t n) {
    xts_array_1_t b = new_xts_array_1(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned v;
        assert(sscanf(hex+2*i, "%2x", &v) == 1);
        b->elems[i] = (uint8_t)v;
    }
    return b;
}

static xts__xts_key_adt_t key(const char *hex) {
    size_t half = strlen(hex)/4;
    xts_array_1_t a = octets(hex,half), b = octets(hex+2*half,half);
    assert(half == 16 || half == 32);
    return half == 16 ? con_xts__xts128(a,b) : con_xts__xts256(a,b);
}

static void check(uint32_t bits, const char *k, const char *t, const char *p, const char *c) {
    uint32_t n = (bits+7)/8;
    xts_record_16_t x = new_xts_record_16();
    x->length = n;
    x->seq = octets(p,n);
    xts_record_16_t y = xts__encrypt(key(k),octets(t,16),bits,x);
    xts_array_1_t e = octets(c,n);
    assert(y->length == n && memcmp(y->seq->elems,e->elems,n) == 0);
    release_xts_array_1(e);
    x = xts__decrypt(key(k),octets(t,16),bits,y);
    e = octets(p,n);
    assert(x->length == n && memcmp(x->seq->elems,e->elems,n) == 0);
    release_xts_array_1(e);
    release_xts_record_16(x);
}

int main(void) {
    check(128,"a1b90cba3f06ac353b2c343876081762090923026e91771815f29dab01932f2f",
          "4faef7117cda59c66e4b92013e768ad5","ebabce95b14d3c8d6fb350390790311c",
          "778ae8b43cb98d5a825081d5be471c63");
    check(256,"b7b93f516aef295eff3a29d837cf1f135347e8a21dae616ff5062b2e8d78ce5e",
          "873edea653b643bd8bcf51403197ed14","236f8a5b58dd55f6194ed70c4ac1a17f1fe60ec9a6c454d087ccb77d6b638c47",
          "22e6a3c6379dcf7599b052b5a749c7f78ad8a11b9f1aa9430cf3aef445682e19");
    check(130,"258a0e54b33347abb36fa24d28cae61902d514172df1a83756ae3932b9353f56",
          "720438c7211b6df569b40867b71d7989","b556cac9983f337345f81587f55a482a40",
          "4a48e2cf351572e2708ca9ad05a3ee2580");
    check(200,"394c97881abd989d29c703e48a72b397a7acf51b59649eeea9b33274d8541df4",
          "4b15c684a152d485fe9937d39b168c29","2f3b9dcfbae729583b1d1ffdd16bb6fe2757329435662a78f0",
          "f3473802e38a3ffef4d4fb8e6aa266ebde553a64528a06463e");
    check(256,"1ea661c58d943a0e4801e42f4b0947149e7f9f8e3e68d0c7505210bd311a0e7cd6e13ffdf2418d8d1911c004cda58da3d619b7e2b9141e58318eea392cf41b08",
          "adf8d92627464ad2f0428e84a9f87564","2eedea52cd8215e1acc647e810bbc3642e87287f8d2e57e36c0a24fbc12a202e",
          "cbaad0e2f6cea3f50b37f934d46a9b130b9d54f07e34f36af793e86f73c6d7db");
    check(384,"266c336b3b01489f3267f52835fd92f674374b88b4e1ebd2d36a5f457581d9d042c3eef7b0b7e5137b086496b4d9e6ac658d7196a23f23f036172fdb8faee527",
          "06b209a7a22f486ecbfadb0f3137ba42","ca7d65ef8d3dfad345b61ccddca1ad81de830b9e86c7b426d76cb7db766852d981c6b21409399d78f42cc0b33a7bbb06",
          "c73256870cc2f4dd57acc74b5456dbd776912a128bc1f77d72cdebbf270044b7a43ceed29025e1e8be211fa3c3ed002d");
    check(140,"4272a2be234ff9763e4996b1bdcc1b6bfb89fcbaf5097e737ca52c6f1b25807c81de7433738c6d5347740c8626bc9a7f8609a34298e01c3beb4b2fbd5a824284",
          "3034e9dcf27b260970cc555027bc0ec7","77348d634fc8e2b057c940cdf94abda3e050",
          "2c40695ba73014e0db5ecacd54b239557570");
    check(250,"d6b58f6638f64c3692a5b53671c5d51e0abf5169437aacb363fbcfcb91f9f6b0f536d0e12dd662d3151a77524eae5ad5e1b9cf860199981edd09ccf99f86fcd2",
          "f5bf2260198883d03b133810fafec16c","8b81371f87661e49b904c8272def606717c3050c125905d23a2f0c142132ee00",
          "84a7f42be588fa36442d33f098ec56e554a8629d76db46d0c516fca52c9c9000");
    puts("SP 800-38E XTS vectors passed.");
    return 0;
}
