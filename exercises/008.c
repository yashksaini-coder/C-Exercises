#include "exercises.h"
#include "lib.h"
#include <limits.h>

/* True when a + b would overflow int. Do not compute a + b. */
bool add_overflows(int a, int b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("add_overflows(1, 2)        = %s\n", add_overflows(1, 2) ? "true" : "false");
    printf("add_overflows(INT_MAX, 1)  = %s\n", add_overflows(INT_MAX, 1) ? "true" : "false");
    printf("add_overflows(INT_MIN, -1) = %s\n", add_overflows(INT_MIN, -1) ? "true" : "false");
    return 0;
}
#endif
