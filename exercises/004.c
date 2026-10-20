#include "exercises.h"
#include "lib.h"

/* Greatest common divisor of a and b (Euclid). Non-negative result. */
int gcd(int a, int b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("gcd(48, 18) = %d\n", gcd(48, 18));
    printf("gcd(-12, 18) = %d\n", gcd(-12, 18));
    printf("gcd(0, 0) = %d\n", gcd(0, 0));
    return 0;
}
#endif
