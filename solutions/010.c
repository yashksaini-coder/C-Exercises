#include "exercises.h"
#include "lib.h"
#include <inttypes.h>

int collatz_steps(uint64_t n) {
    if (n == 0) return -1;
    int steps = 0;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        ++steps;
    }
    return steps;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("collatz_steps(27) = %d\n", collatz_steps(27));
    return 0;
}
#endif
