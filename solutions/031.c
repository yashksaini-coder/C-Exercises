#include "exercises.h"
#include "lib.h"
#include <limits.h>

int int_to_string(int value, char *destination, size_t capacity) {
    /* Work on the magnitude as unsigned: (unsigned)INT_MIN is well defined
     * and 0u - (unsigned)INT_MIN gives 2147483648 without overflow. */
    bool negative = value < 0;
    unsigned magnitude = negative ? 0u - (unsigned)value : (unsigned)value;

    char digits[16];
    size_t digit_count = 0;
    do {
        digits[digit_count++] = (char)('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude != 0);

    size_t length = digit_count + (negative ? 1 : 0);
    if (length + 1 > capacity) {
        if (capacity > 0) destination[0] = '\0';
        return -1;
    }

    size_t out = 0;
    if (negative) destination[out++] = '-';
    while (digit_count > 0) destination[out++] = digits[--digit_count];
    destination[out] = '\0';
    return (int)length;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[16];
    int written = int_to_string(INT_MIN, buffer, sizeof buffer);
    printf("int_to_string(INT_MIN) -> \"%s\" (%d chars)\n", buffer, written);
    return 0;
}
#endif
