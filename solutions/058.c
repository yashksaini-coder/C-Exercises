#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <string.h>

/* Write the low `count` bytes of value, most significant first. */
static size_t put_be(unsigned char *out, uint64_t value, size_t count) {
    for (size_t i = 0; i < count; ++i) out[i] = (unsigned char)(value >> (8 * (count - 1 - i)));
    return count;
}

size_t pack(unsigned char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t written = 0;
    for (; *format; ++format) {
        switch (*format) {
        case 'c': /* char and short are promoted to int through "..." */
            written += put_be(buffer + written, (uint64_t)(unsigned)va_arg(args, int), 1);
            break;
        case 'h':
            written += put_be(buffer + written, (uint64_t)(unsigned)va_arg(args, int), 2);
            break;
        case 'l':
            written += put_be(buffer + written, va_arg(args, uint32_t), 4);
            break;
        case 'q':
            written += put_be(buffer + written, va_arg(args, uint64_t), 8);
            break;
        case 's': {
            const char *s = va_arg(args, const char *);
            size_t length = strlen(s);
            written += put_be(buffer + written, (uint64_t)length, 2);
            memcpy(buffer + written, s, length);
            written += length;
            break;
        }
        default:
            break; /* unknown: write nothing, consume nothing */
        }
    }
    va_end(args);
    return written;
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
