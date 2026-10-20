#include "exercises.h"
#include "lib.h"

/* Bit 0 <-> bit 31, bit 1 <-> bit 30, ... */
uint32_t reverse_bits(uint32_t value) {
    (void)value;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("reverse_bits(0x12345678) = 0x%08X\n", (unsigned)reverse_bits(0x12345678u));
    return 0;
}
#endif
