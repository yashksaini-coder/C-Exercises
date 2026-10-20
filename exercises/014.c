#include "exercises.h"
#include "lib.h"

/* Rotate values[0..count) left by k positions in place. k >= count allowed. */
void array_rotate_left(int *values, size_t count, size_t k) {
    (void)values;
    (void)count;
    (void)k;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4, 5};
    array_rotate_left(values, 5, 2);
    for (size_t i = 0; i < 5; ++i) printf("%d ", values[i]);
    putchar('\n');
    return 0;
}
#endif
