#include "exercises.h"
#include "lib.h"

bool is_prime(unsigned value) {
    if (value < 2) return false;
    if (value % 2 == 0) return value == 2;
    /* divisor <= value / divisor is the overflow-free form of
     * divisor * divisor <= value. */
    for (unsigned divisor = 3; divisor <= value / divisor; divisor += 2)
        if (value % divisor == 0) return false;
    return true;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("is_prime(4294967291) = %s\n", is_prime(4294967291u) ? "true" : "false");
    return 0;
}
#endif
