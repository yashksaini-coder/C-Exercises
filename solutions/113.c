#include "exercises.h"
#include "lib.h"
#include <limits.h>
#include <stdlib.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* k-th largest (1-based); may reorder values; INT_MIN when k is out of range.
 * Quickselect in descending order: after partitioning, every value in
 * [low, store) is > pivot, [store, high] is <= pivot. */
int kth_largest(int *values, size_t count, size_t k) {
    if (!values || count == 0 || k == 0 || k > count) return INT_MIN;
    size_t target = k - 1; /* index in descending order */
    size_t low = 0, high = count - 1;
    while (low < high) {
        /* Middle pivot avoids the quadratic case on sorted input. Move it to the end. */
        size_t middle = low + (high - low) / 2;
        int pivot = values[middle];
        swap(&values[middle], &values[high]);
        size_t store = low;
        for (size_t i = low; i < high; ++i)
            if (values[i] > pivot) swap(&values[i], &values[store++]);
        swap(&values[store], &values[high]); /* pivot into its final place */

        /* All-equal input: values[store] == pivot, and everything before store is
         * strictly greater, so the pivot is exactly the (store+1)-th largest. */
        if (target == store) return values[store];
        if (target < store) high = store - 1;
        else low = store + 1;
    }
    return values[low];
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {3, 2, 1, 5, 6, 4};
    printf("2nd largest = %d\n", kth_largest(values, 6, 2));
    return 0;
}
#endif
