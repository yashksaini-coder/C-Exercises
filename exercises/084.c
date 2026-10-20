#include "exercises.h"
#include "lib.h"
#include <stdarg.h>

/* Sum `count` int arguments into a long. */
long sum_ints(size_t count, ...) {
    (void)count;
    /* TODO: implement with va_list / va_start / va_arg / va_end. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("sum_ints(3, 1, 2, 3) = %ld\n", sum_ints(3, 1, 2, 3));
    printf("sum_ints(0) = %ld\n", sum_ints(0));
    return 0;
}
#endif
