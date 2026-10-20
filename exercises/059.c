#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <string.h>

/* Inverse of pack: c -> int*, h -> uint16_t*, l -> uint32_t*, q -> uint64_t*, s -> char*. */
size_t unpack(const unsigned char *buffer, const char *format, ...) {
    (void)buffer;
    (void)format;
    /* TODO: implement with va_start / va_arg / va_end. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    const unsigned char wire[] = {0x41, 0x12, 0x34, 0xDE, 0xAD, 0xBE, 0xEF, 0, 0, 0, 0, 0, 0, 0, 1,
                                  0x00, 0x02, 'h', 'i'};
    int c = 0;
    uint16_t h = 0;
    uint32_t l = 0;
    uint64_t q = 0;
    char s[16] = {0};
    size_t n = unpack(wire, "chlqs", &c, &h, &l, &q, s);
    printf("%zu bytes: c=0x%X h=0x%X l=0x%X q=%llu s=\"%s\"\n", n, (unsigned)c, (unsigned)h,
           (unsigned)l, (unsigned long long)q, s);
    return 0;
}
#endif
