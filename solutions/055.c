#include "exercises.h"
#include "lib.h"

uint32_t read_u32_be(const unsigned char *bytes) {
    /* Cast before shifting: int << 24 overflows for bytes >= 0x80. */
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) |
           (uint32_t)bytes[3];
}

#ifndef EXERCISE_TEST
int main(void) {
    const unsigned char bytes[4] = {0x12, 0x34, 0x56, 0x78};
    printf("0x%08X\n", (unsigned)read_u32_be(bytes));
    return 0;
}
#endif
