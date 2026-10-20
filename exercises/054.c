#include "exercises.h"
#include "lib.h"

/* Set (on) or clear (!on) bit `index` (0..31); index >= 32 leaves value unchanged. */
uint32_t bit_set(uint32_t value, unsigned index, bool on) {
    (void)value;
    (void)index;
    (void)on;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("bit_set(0xFF, 3, false) = 0x%02X\n", (unsigned)bit_set(0xFFu, 3, false));
    printf("bit_set(0, 31, true)    = 0x%08X\n", (unsigned)bit_set(0u, 31, true));
    return 0;
}
#endif
