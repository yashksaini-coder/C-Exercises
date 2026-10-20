#include "exercises.h"
#include "lib.h"

uint32_t reverse_bits(uint32_t value) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        result = (result << 1) | (value & 1u);
        value >>= 1;
    }
    return result;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("reverse_bits(0x12345678) = 0x%08X\n", (unsigned)reverse_bits(0x12345678u));
    return 0;
}
#endif
