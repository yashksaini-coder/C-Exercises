#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Host -> network (big-endian) 16-bit; swap only on a little-endian host. */
uint16_t my_htons(uint16_t value) {
    (void)value;
    /* TODO: implement with a runtime endianness probe. */
    return 0;
}

/* Host -> network (big-endian) 32-bit. */
uint32_t my_htonl(uint32_t value) {
    (void)value;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_htons(0x1234)     = 0x%04X\n", (unsigned)my_htons(0x1234u));
    printf("my_htonl(0x12345678) = 0x%08X\n", (unsigned)my_htonl(0x12345678u));
    return 0;
}
#endif
