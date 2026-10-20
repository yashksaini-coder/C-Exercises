#include "exercises.h"
#include "lib.h"
#include <limits.h>

/* Divide a by b into *out; report failure as an Error code instead of crashing. */
Error safe_divide(int a, int b, int *out) {
    (void)a;
    (void)b;
    (void)out;
    /* TODO: implement. */
    return ERR_INVALID;
}

/* Human-readable name for an Error; unknown values are "invalid". */
const char *error_string(Error error) {
    (void)error;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    int q = 0;
    Error e = safe_divide(7, 2, &q);
    printf("7 / 2: %s (%d)\n", error_string(e), q);
    e = safe_divide(1, 0, &q);
    printf("1 / 0: %s\n", error_string(e));
    return 0;
}
#endif
