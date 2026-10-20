#include "exercises.h"
#include "lib.h"

/* Return -1, 0 or 1 according to the sign of value. */
int sign(int value) {
    (void)value;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("sign(-42) = %d\n", sign(-42));
    printf("sign(0)   = %d\n", sign(0));
    printf("sign(7)   = %d\n", sign(7));
    return 0;
}
#endif
