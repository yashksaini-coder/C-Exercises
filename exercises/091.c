#include "exercises.h"
#include "lib.h"

/* True when address and network agree in their first prefix_length bits (0..32). */
bool ipv4_in_subnet(const uint8_t address[4], const uint8_t network[4], unsigned prefix_length) {
    (void)address;
    (void)network;
    (void)prefix_length;
    /* TODO: implement. Beware: shifting a 32-bit value by 32 is undefined. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    uint8_t host[4] = {10, 1, 2, 3}, net[4] = {10, 0, 0, 0};
    printf("10.1.2.3 in 10.0.0.0/8: %s\n", ipv4_in_subnet(host, net, 8) ? "yes" : "no");
    return 0;
}
#endif
