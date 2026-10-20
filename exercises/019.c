#include "exercises.h"
#include "lib.h"

/* Number of elements for which predicate returns true. */
size_t count_matching(const int *values, size_t count, bool (*predicate)(int)) {
    (void)values;
    (void)count;
    (void)predicate;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
static bool is_even(int x) { return x % 2 == 0; }

int main(void) {
    int values[] = {1, 2, 3, 4, 5, 6};
    printf("evens: %zu\n", count_matching(values, 6, is_even));
    return 0;
}
#endif
