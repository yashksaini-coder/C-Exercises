#include "exercises.h"
#include "lib.h"
#include <stdarg.h>

long sum_ints(size_t count, ...) {
    va_list args;
    va_start(args, count);
    long total = 0;
    for (size_t i = 0; i < count; ++i) total += va_arg(args, int);
    va_end(args);
    return total;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("sum_ints(3, 1, 2, 3) = %ld\n", sum_ints(3, 1, 2, 3));
    printf("sum_ints(0) = %ld\n", sum_ints(0));
    return 0;
}
#endif
