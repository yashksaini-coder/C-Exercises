#include "exercises.h"
#include "lib.h"

/* Return a pointer to the first maximal element of the array, or NULL if count is 0. */
const void *generic_max(const void *base, size_t count, size_t size, Comparator compare) {
    (void)base;
    (void)count;
    (void)size;
    (void)compare;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int values[] = {3, 9, 2, 9};
    const int *max = generic_max(values, 4, sizeof values[0], compare_ints);
    if (max) printf("max = %d at index %td\n", *max, max - values);
    return 0;
}
#endif
