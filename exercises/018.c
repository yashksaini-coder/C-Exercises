#include "exercises.h"
#include "lib.h"

/* values[i] = transform(values[i]) for every i. */
void apply_each(int *values, size_t count, int (*transform)(int)) {
    (void)values;
    (void)count;
    (void)transform;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
static int square(int x) { return x * x; }

int main(void) {
    int values[] = {1, 2, 3};
    apply_each(values, 3, square);
    printf("squared: %d %d %d\n", values[0], values[1], values[2]);
    return 0;
}
#endif
