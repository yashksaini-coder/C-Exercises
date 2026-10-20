#include "exercises.h"
#include "lib.h"
#include <inttypes.h>

/* n-th Fibonacci number, iteratively. fibonacci(0) = 0, fibonacci(1) = 1. */
uint64_t fibonacci(unsigned n) {
    (void)n;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("fibonacci(10) = %" PRIu64 "\n", fibonacci(10));
    printf("fibonacci(93) = %" PRIu64 "\n", fibonacci(93));
    return 0;
}
#endif
