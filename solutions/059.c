#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <string.h>

/* Read `count` big-endian bytes into a uint64_t. */
static uint64_t get_be(const unsigned char *in, size_t count) {
    uint64_t value = 0;
    for (size_t i = 0; i < count; ++i) value = (value << 8) | (uint64_t)in[i];
    return value;
}

size_t unpack(const unsigned char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t consumed = 0;
    for (; *format; ++format) {
        switch (*format) {
        case 'c': {
            int value = (int)get_be(buffer + consumed, 1);
            if (value > 127) value -= 256; /* sign-extend without assuming char is signed */
            *va_arg(args, int *) = value;
            consumed += 1;
            break;
        }
        case 'h':
            *va_arg(args, uint16_t *) = (uint16_t)get_be(buffer + consumed, 2);
            consumed += 2;
            break;
        case 'l':
            *va_arg(args, uint32_t *) = (uint32_t)get_be(buffer + consumed, 4);
            consumed += 4;
            break;
        case 'q':
            *va_arg(args, uint64_t *) = get_be(buffer + consumed, 8);
            consumed += 8;
            break;
        case 's': {
            size_t length = (size_t)get_be(buffer + consumed, 2);
            consumed += 2;
            char *out = va_arg(args, char *);
            memcpy(out, buffer + consumed, length);
            out[length] = '\0';
            consumed += length;
            break;
        }
        default:
            break;
        }
    }
    va_end(args);
    return consumed;
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
