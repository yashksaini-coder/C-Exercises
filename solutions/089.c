#include "exercises.h"
#include "lib.h"

/* Parse "A.B.C.D" into four bytes; false on any malformed input. */
bool parse_ipv4(const char *s, uint8_t out[4]) {
    if (!s || !out) return false;
    for (int octet = 0; octet < 4; ++octet) {
        if (*s < '0' || *s > '9') return false; /* empty octet or non-digit */
        unsigned value = 0;
        while (*s >= '0' && *s <= '9') {
            value = value * 10 + (unsigned)(*s - '0');
            if (value > 255) return false; /* check while accumulating */
            ++s;
        }
        out[octet] = (uint8_t)value;
        if (octet < 3) {
            if (*s != '.') return false;
            ++s;
        }
    }
    return *s == '\0'; /* nothing may follow the fourth octet */
}

#ifndef EXERCISE_TEST
int main(void) {
    uint8_t bytes[4];
    if (parse_ipv4("192.168.1.10", bytes))
        printf("%u %u %u %u\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    return 0;
}
#endif
