#include "exercises.h"
#include "lib.h"

/* Pack: read=bit0, write=bit1, execute=bit2, level=bits 3..7. */
uint8_t encode_permissions(Permissions p) {
    (void)p;
    /* TODO: implement. */
    return 0;
}

/* Inverse of encode_permissions. */
Permissions decode_permissions(uint8_t byte) {
    Permissions p = {0, 0, 0, 0};
    (void)byte;
    /* TODO: implement. */
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
