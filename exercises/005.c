#include "exercises.h"
#include "lib.h"

/* Return true when value is prime. Must run in O(sqrt(value)). */
bool is_prime(unsigned value) {
    (void)value;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    unsigned values[] = {1, 2, 91, 97, 4294967291u};
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i)
        printf("is_prime(%u) = %s\n", values[i], is_prime(values[i]) ? "true" : "false");
    return 0;
}
#endif
