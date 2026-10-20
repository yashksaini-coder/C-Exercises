#include "exercises.h"
#include "lib.h"

void write_u32_be(unsigned char *bytes, uint32_t value) {
    bytes[0] = (unsigned char)(value >> 24);
    bytes[1] = (unsigned char)(value >> 16);
    bytes[2] = (unsigned char)(value >> 8);
    bytes[3] = (unsigned char)value;
}

#ifndef EXERCISE_TEST
int main(void) {
    unsigned char bytes[4] = {0};
    write_u32_be(bytes, 0x12345678u);
    printf("%02X %02X %02X %02X\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    return 0;
}
#endif
