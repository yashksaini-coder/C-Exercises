#include "exercises.h"
#include "lib.h"

/* First index of the largest element; 0 when count is 0. */
size_t array_max_index(const int *values, size_t count) {
    (void)values;
    (void)count;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {3, 9, 2, 9};
    printf("array_max_index({3, 9, 2, 9}) = %zu\n", array_max_index(values, 4));
    return 0;
}
#endif
