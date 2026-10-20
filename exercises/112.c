#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Stable merge of two ascending arrays into out (a wins ties). */
void merge_sorted_arrays(const int *a, size_t a_count, const int *b, size_t b_count, int *out) {
    (void)a;
    (void)a_count;
    (void)b;
    (void)b_count;
    (void)out;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int a[] = {1, 3, 5}, b[] = {2, 4, 6}, out[6] = {0};
    merge_sorted_arrays(a, 3, b, 3, out);
    for (int i = 0; i < 6; ++i) printf("%d ", out[i]);
    putchar('\n');
    return 0;
}
#endif
