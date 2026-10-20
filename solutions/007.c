#include "exercises.h"
#include "lib.h"
#include <inttypes.h>

uint64_t fibonacci(unsigned n) {
    uint64_t previous = 0, current = 1;
    for (unsigned i = 0; i < n; ++i) {
        uint64_t next = previous + current;
        previous = current;
        current = next;
    }
    return previous;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("fibonacci(93) = %" PRIu64 "\n", fibonacci(93));
    return 0;
}
#endif
