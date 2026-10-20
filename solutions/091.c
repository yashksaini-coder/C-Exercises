#include "exercises.h"
#include "lib.h"

static uint32_t pack_be(const uint8_t bytes[4]) {
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) |
           (uint32_t)bytes[3];
}

/* True when address and network agree in their first prefix_length bits (0..32). */
bool ipv4_in_subnet(const uint8_t address[4], const uint8_t network[4], unsigned prefix_length) {
    if (!address || !network || prefix_length > 32) return false;
    /* A 64-bit shift sidesteps the "shift by 32 is UB" trap for /0. */
    uint32_t mask = (uint32_t)(0xFFFFFFFFull << (32 - prefix_length));
    return (pack_be(address) & mask) == (pack_be(network) & mask);
}

#ifndef EXERCISE_TEST
int main(void) {
    uint8_t host[4] = {10, 1, 2, 3}, net[4] = {10, 0, 0, 0};
    printf("10.1.2.3 in 10.0.0.0/8: %s\n", ipv4_in_subnet(host, net, 8) ? "yes" : "no");
    return 0;
}
#endif
