#include "exercises.h"
#include "lib.h"

unsigned bit_count(uint32_t value) {
    unsigned count = 0;
    while (value) {
        value &= value - 1; /* clears the lowest set bit */
        ++count;
    }
    return count;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("bit_count(0xA5A5A5A5) = %u\n", bit_count(0xA5A5A5A5u));
    return 0;
}
#endif
