#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Stable merge of two ascending arrays into out (a wins ties). */
void merge_sorted_arrays(const int *a, size_t a_count, const int *b, size_t b_count, int *out) {
    size_t i = 0, j = 0, k = 0;
    while (i < a_count && j < b_count) {
        /* <= keeps the merge stable: equal elements from a come first. */
        if (a[i] <= b[j]) out[k++] = a[i++];
        else out[k++] = b[j++];
    }
    if (i < a_count) memcpy(out + k, a + i, (a_count - i) * sizeof *out);
    if (j < b_count) memcpy(out + k, b + j, (b_count - j) * sizeof *out);
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
