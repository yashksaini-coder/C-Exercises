#include "exercises.h"
#include "lib.h"
#include <string.h>

_Static_assert(sizeof(float) == sizeof(uint32_t), "float must be 32 bits");

typedef union {
    float f;
    uint32_t u;
} FloatPun;

uint32_t float_bits(float value) {
    FloatPun pun;
    pun.f = value;
    return pun.u; /* reading the inactive member is defined in C11 */
}

float bits_to_float(uint32_t bits) {
    /* memcpy is the other sanctioned approach; shown here for contrast. */
    float f;
    memcpy(&f, &bits, sizeof f);
    return f;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("float_bits(1.0f) = 0x%08X\n", (unsigned)float_bits(1.0f));
    printf("bits_to_float(0x40490FDB) = %.8g\n", (double)bits_to_float(0x40490FDBu));
    return 0;
}
#endif
