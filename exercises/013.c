#include "exercises.h"
#include "lib.h"

/* Reverse values[0..count) in place. */
void array_reverse(int *values, size_t count) {
    (void)values;
    (void)count;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4};
    array_reverse(values, 4);
    printf("reversed: %d %d %d %d\n", values[0], values[1], values[2], values[3]);
    return 0;
}
#endif
