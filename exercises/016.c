#include "exercises.h"
#include "lib.h"

/* second - first, in elements. Both must point into the same array. */
ptrdiff_t pointer_distance(const int *first, const int *second) {
    (void)first;
    (void)second;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[8] = {0};
    printf("pointer_distance(v, v + 5) = %td\n", pointer_distance(values, values + 5));
    printf("pointer_distance(v + 5, v) = %td\n", pointer_distance(values + 5, values));
    return 0;
}
#endif
