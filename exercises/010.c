#include "exercises.h"
#include "lib.h"
#include <inttypes.h>

/* Number of Collatz steps from n to 1; 0 for n == 1; -1 for n == 0. */
int collatz_steps(uint64_t n) {
    (void)n;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("collatz_steps(6)  = %d\n", collatz_steps(6));
    printf("collatz_steps(27) = %d\n", collatz_steps(27));
    printf("collatz_steps(%" PRIu64 ") = %d\n", (uint64_t)1 << 40, collatz_steps((uint64_t)1 << 40));
    return 0;
}
#endif
