#include <bzlib.h>
#include <stdint.h>
#include <stdlib.h>
uint32_t crypto_bzip_length(const uint8_t *data, uint32_t n) {
    uint64_t cap = (uint64_t)n + n / 100 + 601;
    if (cap > UINT32_MAX) return 0;
    unsigned size = (unsigned)cap;
    char *dst = malloc(size);
    if (!dst) return 0;
    int status = BZ2_bzBuffToBuffCompress(dst, &size, (char *)data, n, 5, 0, 0);
    free(dst);
    return status == BZ_OK ? size : 0;
}
