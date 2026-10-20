#include "exercises.h"
#include "lib.h"
#include <string.h>

static bool host_is_little_endian(void) {
    union {
        uint16_t u;
        unsigned char b[2];
    } probe = {1};
    return probe.b[0] == 1; /* little-endian stores the low byte first */
}

uint16_t my_htons(uint16_t value) {
    if (!host_is_little_endian()) return value;
    return (uint16_t)((value >> 8) | (value << 8));
}

uint32_t my_htonl(uint32_t value) {
    if (!host_is_little_endian()) return value;
    return (value >> 24) | ((value >> 8) & 0x0000FF00u) | ((value << 8) & 0x00FF0000u) |
           (value << 24);
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_htons(0x1234)     = 0x%04X\n", (unsigned)my_htons(0x1234u));
    printf("my_htonl(0x12345678) = 0x%08X\n", (unsigned)my_htonl(0x12345678u));
    return 0;
}
#endif
