#include "exercises.h"
#include "lib.h"

/* Write "A.B.C.D" into destination; return its length, or -1 if it does not fit. */
int format_ipv4(const uint8_t address[4], char *destination, size_t capacity) {
    (void)address;
    (void)destination;
    (void)capacity;
    /* TODO: implement. */
    return -1;
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
