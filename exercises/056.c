#include "exercises.h"
#include "lib.h"

/* uint32_t -> four big-endian bytes, byte by byte. */
void write_u32_be(unsigned char *bytes, uint32_t value) {
    (void)bytes;
    (void)value;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    unsigned char bytes[4] = {0};
    write_u32_be(bytes, 0x12345678u);
    printf("%02X %02X %02X %02X\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    return 0;
}
#endif
