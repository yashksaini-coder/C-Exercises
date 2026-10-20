#include "exercises.h"
#include "lib.h"

int digit_sum(int value) {
    int sum = 0;
    /* Never negate value: -INT_MIN overflows. Instead take the absolute
     * value of each digit, which is always in -9..9. */
    while (value != 0) {
        int digit = value % 10;
        sum += digit < 0 ? -digit : digit;
        value /= 10;
    }
    return sum;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("digit_sum(-123) = %d\n", digit_sum(-123));
    return 0;
}
#endif
