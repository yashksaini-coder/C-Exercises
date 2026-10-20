#include "exercises.h"
#include "lib.h"

/* Sum of the decimal digits of |value|. Must handle INT_MIN. */
int digit_sum(int value) {
    (void)value;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("digit_sum(1234) = %d\n", digit_sum(1234));
    printf("digit_sum(-123) = %d\n", digit_sum(-123));
    return 0;
}
#endif
