#include "exercises.h"
#include "lib.h"

/* Number of 1 bits in value. */
unsigned bit_count(uint32_t value) {
    (void)value;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("bit_count(0xA5A5A5A5) = %u\n", bit_count(0xA5A5A5A5u));
    return 0;
}
#endif
