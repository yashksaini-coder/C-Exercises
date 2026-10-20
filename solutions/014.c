#include "exercises.h"
#include "lib.h"

static void reverse_range(int *values, size_t from, size_t to) {
    /* Reverses values[from..to), to is exclusive. */
    while (from + 1 < to) {
        --to;
        int temporary = values[from];
        values[from] = values[to];
        values[to] = temporary;
        ++from;
    }
}

void array_rotate_left(int *values, size_t count, size_t k) {
    if (count == 0) return;
    k %= count;
    if (k == 0) return;
    /* Three reversals: [A B] -> [A^r B^r] -> [B A]. */
    reverse_range(values, 0, k);
    reverse_range(values, k, count);
    reverse_range(values, 0, count);
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
