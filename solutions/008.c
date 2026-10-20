#include "exercises.h"
#include "lib.h"
#include <limits.h>

bool add_overflows(int a, int b) {
    /* INT_MAX - b (b > 0) and INT_MIN - b (b < 0) never overflow, so the
     * comparison is made entirely with well-defined values. */
    if (b > 0) return a > INT_MAX - b;
    if (b < 0) return a < INT_MIN - b;
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("add_overflows(INT_MAX, 1) = %s\n", add_overflows(INT_MAX, 1) ? "true" : "false");
    return 0;
}
#endif
