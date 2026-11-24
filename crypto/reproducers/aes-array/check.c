#include "fixed_array_c.h"
#include <stdio.h>

int main(void) {
    fixed_array__block_t input = new_fixed_array__block(16);
    for (uint32_t i = 0; i < 16; ++i)
        input->elems[i] = (uint8_t)i;
    fixed_array__block_t output = fixed_array__complement(input);
    if (output->size != 16) {
        fprintf(stderr, "Expected 16 bytes, got %u\n", output->size);
        return 1;
    }
    for (uint32_t i = 0; i < 16; ++i)
        if (output->elems[i] != (uint8_t)~i)
            return 1;
    release_fixed_array__block(output);
    puts("16-byte array complement passed.");
    return 0;
}
