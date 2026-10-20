#include "exercises.h"
#include "lib.h"

uint32_t bit_set(uint32_t value, unsigned index, bool on) {
    if (index >= 32) return value; /* shifting by >= width is undefined */
    uint32_t mask = UINT32_C(1) << index;
    return on ? (value | mask) : (value & ~mask);
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("bit_set(0xFF, 3, false) = 0x%02X\n", (unsigned)bit_set(0xFFu, 3, false));
    printf("bit_set(0, 31, true)    = 0x%08X\n", (unsigned)bit_set(0u, 31, true));
    return 0;
}
#endif
