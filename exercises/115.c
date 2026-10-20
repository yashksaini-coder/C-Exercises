#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Decimal string addition; returns the result length or -1 if it does not fit / bad input. */
int bigint_add(const char *a, const char *b, char *out, size_t capacity) {
    (void)a;
    (void)b;
    (void)out;
    (void)capacity;
    /* TODO: implement right-to-left with a carry. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    char sum[64];
    if (bigint_add("99999999999999999999", "1", sum, sizeof sum) >= 0) puts(sum);
    return 0;
}
#endif
