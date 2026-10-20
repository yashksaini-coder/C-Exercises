#include "exercises.h"
#include "lib.h"

const void *generic_max(const void *base, size_t count, size_t size, Comparator compare) {
    if (count == 0) return NULL;
    const unsigned char *bytes = base; /* void * converts implicitly in C */
    const unsigned char *best = bytes;
    for (size_t i = 1; i < count; ++i) {
        const unsigned char *candidate = bytes + i * size;
        /* Strictly greater keeps the first of equal maxima. */
        if (compare(candidate, best) > 0) best = candidate;
    }
    return best;
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
