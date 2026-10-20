#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Sort count elements of size bytes in place according to compare. Must not call qsort. */
void my_qsort(void *base, size_t count, size_t size, Comparator compare) {
    (void)base;
    (void)count;
    (void)size;
    (void)compare;
    /* TODO: implement. A static helper that swaps `size` bytes is a good start. */
}

#ifndef EXERCISE_TEST
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int values[] = {5, 1, 4, 2, 3};
    my_qsort(values, 5, sizeof values[0], compare_ints);
    for (size_t i = 0; i < 5; ++i) printf("%d ", values[i]);
    putchar('\n');
    return 0;
}
#endif
