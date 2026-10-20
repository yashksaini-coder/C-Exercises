#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <string.h>

/* Serialize arguments per format (c h l q s) big-endian; return bytes written. */
size_t pack(unsigned char *buffer, const char *format, ...) {
    (void)buffer;
    (void)format;
    /* TODO: implement with va_start / va_arg / va_end. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    unsigned char buffer[64];
    size_t n = pack(buffer, "chlqs", 0x41, 0x1234, (uint32_t)0xDEADBEEF, (uint64_t)1, "hi");
    printf("%zu bytes:", n);
    for (size_t i = 0; i < n; ++i) printf(" %02X", buffer[i]);
    printf("\n");
    return 0;
}
#endif
