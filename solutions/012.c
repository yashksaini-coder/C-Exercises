#include "exercises.h"
#include "lib.h"

size_t array_max_index(const int *values, size_t count) {
    size_t best = 0;
    for (size_t i = 1; i < count; ++i)
        if (values[i] > values[best]) best = i; /* strict: keep the first */
    return best;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {3, 9, 2, 9};
    printf("array_max_index({3, 9, 2, 9}) = %zu\n", array_max_index(values, 4));
    return 0;
}
#endif
