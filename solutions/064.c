#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Swap two elements of `size` bytes without knowing their type. */
static void swap_bytes(unsigned char *a, unsigned char *b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        unsigned char t = a[i];
        a[i] = b[i];
        b[i] = t;
    }
}

/* Hoare-style quicksort with middle pivot, recursing on the smaller side so
 * the stack depth stays O(log n). Elements are addressed as byte offsets. */
static void sort_range(unsigned char *base, size_t count, size_t size, Comparator compare) {
    while (count > 1) {
        /* Move the pivot to the end so it stays put during partitioning. */
        swap_bytes(base + (count / 2) * size, base + (count - 1) * size, size);
        unsigned char *pivot = base + (count - 1) * size;
        size_t store = 0;
        for (size_t i = 0; i + 1 < count; ++i) {
            if (compare(base + i * size, pivot) < 0) {
                swap_bytes(base + i * size, base + store * size, size);
                ++store;
            }
        }
        swap_bytes(base + store * size, pivot, size);
        /* Now [0, store) < pivot, pivot at store, (store, count) >= pivot. */
        size_t left = store, right = count - store - 1;
        if (left < right) {
            sort_range(base, left, size, compare);
            base += (store + 1) * size;
            count = right;
        } else {
            sort_range(base + (store + 1) * size, right, size, compare);
            count = left;
        }
    }
}

void my_qsort(void *base, size_t count, size_t size, Comparator compare) {
    if (!base || count < 2 || size == 0) return;
    sort_range(base, count, size, compare);
}

#ifndef EXERCISE_TEST
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int values[] = {5, 1, 4, 2, 3};
    my_qsort(values, 5, sizeof values[0], compare_ints);
    for (size_t i = 0; i < 5; ++i) printf("%d ", values[i]);
    putchar('\n');
    return 0;
}
#endif
