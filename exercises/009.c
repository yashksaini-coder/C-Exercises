#include "exercises.h"
#include "lib.h"

/* Mean of count ints as a double; 0.0 when count is 0. Must not overflow. */
double average(const int *values, size_t count) {
    (void)values;
    (void)count;
    /* TODO: implement. */
    return 0.0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4};
    printf("average({1, 2, 3, 4}) = %g\n", average(values, 4));
    printf("average(NULL, 0)      = %g\n", average(NULL, 0));
    return 0;
}
#endif
