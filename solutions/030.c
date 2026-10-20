#include "exercises.h"
#include "lib.h"
#include <ctype.h>
#include <limits.h>

int my_atoi(const char *s) {
    while (isspace((unsigned char)*s)) ++s;
    bool negative = false;
    if (*s == '+' || *s == '-') negative = (*s++ == '-');

    /* Accumulate the magnitude as a negative number: INT_MIN's magnitude
     * does not fit in a positive int, but every magnitude fits negated. */
    int result = 0;
    while (isdigit((unsigned char)*s)) {
        int digit = *s++ - '0';
        if (result < (INT_MIN + digit) / 10) return negative ? INT_MIN : INT_MAX;
        result = result * 10 - digit;
    }
    if (!negative) {
        if (result == INT_MIN) return INT_MAX; /* -INT_MIN would overflow */
        return -result;
    }
    return result;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_atoi(\"   -42abc\") = %d\n", my_atoi("   -42abc"));
    return 0;
}
#endif
