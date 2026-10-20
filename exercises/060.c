#include "exercises.h"
#include "lib.h"

/* RFC 1071 one's-complement checksum of 16-bit big-endian words; odd tail padded with 0. */
uint16_t internet_checksum(const unsigned char *data, size_t length) {
    (void)data;
    (void)length;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    const unsigned char header[20] = {0x45, 0x00, 0x00, 0x3C, 0x1C, 0x46, 0x40, 0x00, 0x40, 0x06,
                                      0x00, 0x00, 0xAC, 0x10, 0x0A, 0x63, 0xAC, 0x10, 0x0A, 0x0C};
    printf("checksum = 0x%04X (expected 0xB1E6)\n", (unsigned)internet_checksum(header, 20));
    return 0;
}
#endif
