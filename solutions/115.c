#include "exercises.h"
#include "lib.h"
#include <string.h>

static bool all_digits(const char *s) {
    if (!s || !*s) return false;
    for (; *s; ++s)
        if (*s < '0' || *s > '9') return false;
    return true;
}

/* Digit i (0 = least significant) of the sum, running the carry; the caller
 * loops i from 0 upwards and keeps `carry` between calls. */
static int sum_digit(const char *a, size_t la, const char *b, size_t lb, size_t i, int *carry) {
    int da = i < la ? a[la - 1 - i] - '0' : 0;
    int db = i < lb ? b[lb - 1 - i] - '0' : 0;
    int sum = da + db + *carry;
    *carry = sum / 10;
    return sum % 10;
}

/* Decimal string addition; returns the result length or -1 if it does not fit / bad input. */
int bigint_add(const char *a, const char *b, char *out, size_t capacity) {
    if (!all_digits(a) || !all_digits(b) || !out) return -1;
    size_t la = strlen(a), lb = strlen(b);
    size_t width = la > lb ? la : lb;

    /* Pass 1: measure. The length is the position of the highest non-zero digit
     * plus one (inputs may carry leading zeros), or 1 for an all-zero sum. */
    size_t length = 1;
    int carry = 0;
    for (size_t i = 0; i < width; ++i)
        if (sum_digit(a, la, b, lb, i, &carry) != 0) length = i + 1;
    if (carry) length = width + 1;
    if (length + 1 > capacity) return -1;

    /* Pass 2: write right-to-left into exactly `length` slots. */
    carry = 0;
    for (size_t i = 0; i < length; ++i) {
        int digit = i < width ? sum_digit(a, la, b, lb, i, &carry) : carry; /* top carry */
        out[length - 1 - i] = (char)('0' + digit);
    }
    out[length] = '\0';
    return (int)length;
}

#ifndef EXERCISE_TEST
int main(void) {
    char sum[64];
    if (bigint_add("99999999999999999999", "1", sum, sizeof sum) >= 0) puts(sum);
    return 0;
}
#endif
