#include "exercises.h"
#include "lib.h"

static size_t decimal_width(unsigned value) {
    return value >= 100 ? 3 : value >= 10 ? 2 : 1;
}

/* Write "A.B.C.D" into destination; return its length, or -1 if it does not fit. */
int format_ipv4(const uint8_t address[4], char *destination, size_t capacity) {
    if (!address || !destination || capacity == 0) return -1;

    /* Measure first so a too-small buffer is left untouched. */
    size_t needed = 3; /* three dots */
    for (int i = 0; i < 4; ++i) needed += decimal_width(address[i]);
    if (needed + 1 > capacity) return -1;

    char *p = destination;
    for (int i = 0; i < 4; ++i) {
        unsigned value = address[i];
        size_t width = decimal_width(value);
        /* Write the digits right-to-left into their slot. */
        for (size_t k = width; k > 0; --k) {
            p[k - 1] = (char)('0' + value % 10);
            value /= 10;
        }
        p += width;
        if (i < 3) *p++ = '.';
    }
    *p = '\0';
    return (int)needed;
}

#ifndef EXERCISE_TEST
int main(void) {
    uint8_t address[4] = {192, 168, 1, 10};
    char text[16];
    int length = format_ipv4(address, text, sizeof text);
    if (length >= 0) printf("%s (%d chars)\n", text, length);
    return 0;
}
#endif
