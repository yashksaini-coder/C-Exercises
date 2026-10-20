#include "exercises.h"
#include "lib.h"

uint8_t encode_permissions(Permissions p) {
    return (uint8_t)(p.read | (p.write << 1) | (p.execute << 2) | (p.level << 3));
}

Permissions decode_permissions(uint8_t byte) {
    Permissions p;
    p.read = byte & 1u;
    p.write = (byte >> 1) & 1u;
    p.execute = (byte >> 2) & 1u;
    p.level = (byte >> 3) & 0x1Fu;
    return p;
}

#ifndef EXERCISE_TEST
int main(void) {
    Permissions p = {1, 0, 1, 0};
    printf("sizeof(Permissions) = %zu\n", sizeof(Permissions));
    printf("encode = 0x%02X\n", encode_permissions(p));
    Permissions q = decode_permissions(0x2A);
    printf("decode(0x2A): r=%u w=%u x=%u level=%u\n", q.read, q.write, q.execute, q.level);
    return 0;
}
#endif
