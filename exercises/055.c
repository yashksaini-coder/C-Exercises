#include "exercises.h"
#include "lib.h"

/* Four big-endian bytes -> uint32_t, byte by byte. */
uint32_t read_u32_be(const unsigned char *bytes) {
    (void)bytes;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    const unsigned char bytes[4] = {0x12, 0x34, 0x56, 0x78};
    printf("0x%08X\n", (unsigned)read_u32_be(bytes));
    return 0;
}
#endif
