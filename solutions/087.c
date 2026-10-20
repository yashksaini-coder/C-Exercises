#include "exercises.h"
#include "lib.h"
#include <limits.h>

Error safe_divide(int a, int b, int *out) {
    if (!out) return ERR_INVALID;
    if (b == 0) return ERR_DIVIDE_BY_ZERO;
    if (a == INT_MIN && b == -1) return ERR_OVERFLOW; /* -INT_MIN does not fit: UB, SIGFPE on x86 */
    *out = a / b;
    return ERR_OK;
}

const char *error_string(Error error) {
    switch (error) {
    case ERR_OK: return "ok";
    case ERR_DIVIDE_BY_ZERO: return "divide by zero";
    case ERR_OVERFLOW: return "overflow";
    case ERR_INVALID: return "invalid";
    default: return "invalid"; /* an enum is an int; callers can pass anything */
    }
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
