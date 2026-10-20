#include "exercises.h"
#include "lib.h"
#include <limits.h>

/* Write value in decimal (with '-' and NUL); return chars written or -1. */
int int_to_string(int value, char *destination, size_t capacity) {
    (void)value;
    (void)destination;
    (void)capacity;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[16];
    int written = int_to_string(-42, buffer, sizeof buffer);
    printf("int_to_string(-42) -> \"%s\" (%d chars)\n", buffer, written);
    return 0;
}
#endif
