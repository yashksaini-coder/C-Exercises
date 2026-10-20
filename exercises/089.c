#include "exercises.h"
#include "lib.h"

/* Parse "A.B.C.D" into four bytes; false on any malformed input. */
bool parse_ipv4(const char *s, uint8_t out[4]) {
    (void)s;
    (void)out;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    uint8_t bytes[4];
    if (parse_ipv4("192.168.1.10", bytes))
        printf("%u %u %u %u\n", bytes[0], bytes[1], bytes[2], bytes[3]);
    else
        puts("parse failed");
    return 0;
}
#endif
