#include "exercises.h"
#include "lib.h"

/* Index of the first element equal to target, or -1. */
ptrdiff_t find_index(const int *values, size_t count, int target) {
    (void)values;
    (void)count;
    (void)target;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {4, 8, 15, 16};
    printf("find_index(15) = %td\n", find_index(values, 4, 15));
    printf("find_index(7)  = %td\n", find_index(values, 4, 7));
    return 0;
}
#endif
