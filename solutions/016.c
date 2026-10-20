#include "exercises.h"
#include "lib.h"

ptrdiff_t pointer_distance(const int *first, const int *second) {
    /* Pointer difference is already scaled to elements by the compiler. */
    return second - first;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[8] = {0};
    printf("pointer_distance(v, v + 5) = %td\n", pointer_distance(values, values + 5));
    return 0;
}
#endif
