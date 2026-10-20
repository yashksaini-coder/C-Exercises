#include "exercises.h"
#include "lib.h"
#include <limits.h>
#include <stdlib.h>

/* k-th largest (1-based); may reorder values; INT_MIN when k is out of range. */
int kth_largest(int *values, size_t count, size_t k) {
    (void)values;
    (void)count;
    (void)k;
    /* TODO: quickselect (partition, recurse into the side holding index k-1). */
    return INT_MIN;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {3, 2, 1, 5, 6, 4};
    printf("2nd largest = %d\n", kth_largest(values, 6, 2));
    return 0;
}
#endif
