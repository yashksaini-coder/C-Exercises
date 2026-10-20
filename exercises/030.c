#include "exercises.h"
#include "lib.h"
#include <ctype.h>
#include <limits.h>

/* Parse a leading decimal int (LeetCode-style), clamping on overflow. */
int my_atoi(const char *s) {
    (void)s;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_atoi(\"   -42abc\")   = %d\n", my_atoi("   -42abc"));
    printf("my_atoi(\"99999999999\") = %d\n", my_atoi("99999999999"));
    return 0;
}
#endif
