#include "exercises.h"
#include "lib.h"

double average(const int *values, size_t count) {
    if (count == 0) return 0.0;
    /* long long holds at least 2^63, so even SIZE_MAX / 2^32 ints cannot
     * overflow it in practice; it also keeps the sum exact. */
    long long sum = 0;
    for (size_t i = 0; i < count; ++i) sum += values[i];
    return (double)sum / (double)count;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4};
    printf("average({1, 2, 3, 4}) = %g\n", average(values, 4));
    return 0;
}
#endif
