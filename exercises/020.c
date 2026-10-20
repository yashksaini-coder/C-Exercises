#include "exercises.h"
#include "lib.h"

/* Compact a sorted array in place; return the number of distinct elements. */
size_t remove_duplicates_sorted(int *values, size_t count) {
    (void)values;
    (void)count;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 1, 2, 3, 3, 3, 4};
    size_t length = remove_duplicates_sorted(values, 7);
    printf("%zu distinct:", length);
    for (size_t i = 0; i < length; ++i) printf(" %d", values[i]);
    putchar('\n');
    return 0;
}
#endif
