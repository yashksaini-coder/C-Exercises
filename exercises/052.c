#include "exercises.h"
#include "lib.h"

/* True for 1, 2, 4, 8, ...; false for 0 and everything else. */
bool is_power_of_two(uint64_t value) {
    (void)value;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    for (uint64_t v = 0; v <= 17; ++v) printf("%llu: %d\n", (unsigned long long)v, is_power_of_two(v));
    return 0;
}
#endif
