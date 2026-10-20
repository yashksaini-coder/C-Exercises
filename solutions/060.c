#include "exercises.h"
#include "lib.h"

uint16_t internet_checksum(const unsigned char *data, size_t length) {
    uint32_t sum = 0;
    size_t i = 0;
    for (; i + 1 < length; i += 2) sum += ((uint32_t)data[i] << 8) | data[i + 1];
    if (i < length) sum += (uint32_t)data[i] << 8; /* odd trailing byte, zero-padded */
    while (sum >> 16) sum = (sum & 0xFFFFu) + (sum >> 16); /* fold carries (may need two rounds) */
    return (uint16_t)~sum;
}

#ifndef EXERCISE_TEST
int main(void) {
    const unsigned char header[20] = {0x45, 0x00, 0x00, 0x3C, 0x1C, 0x46, 0x40, 0x00, 0x40, 0x06,
                                      0x00, 0x00, 0xAC, 0x10, 0x0A, 0x63, 0xAC, 0x10, 0x0A, 0x0C};
    printf("checksum = 0x%04X (expected 0xB1E6)\n", (unsigned)internet_checksum(header, 20));
    return 0;
}
#endif
