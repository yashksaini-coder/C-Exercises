#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Raw IEEE-754 bits of value. */
uint32_t float_bits(float value) {
    (void)value;
    /* TODO: implement with a union. */
    return 0;
}

/* The float whose IEEE-754 bits are given. */
float bits_to_float(uint32_t bits) {
    (void)bits;
    /* TODO: implement. */
    return 0.0f;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("float_bits(1.0f) = 0x%08X\n", (unsigned)float_bits(1.0f));
    printf("bits_to_float(0x40490FDB) = %.8g\n", (double)bits_to_float(0x40490FDBu));
    return 0;
}
#endif
