#include "exercises.h"
#include "lib.h"

void *my_bsearch(const void *key, const void *base, size_t count, size_t size, Comparator compare) {
    const unsigned char *bytes = base;
    size_t low = 0, high = count; /* half-open [low, high) avoids size_t underflow */
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        const unsigned char *element = bytes + mid * size;
        int order = compare(key, element);
        if (order == 0) return (void *)element; /* cast away const like the standard does */
        if (order < 0) high = mid;
        else low = mid + 1;
    }
    return NULL;
}

#ifndef EXERCISE_TEST
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int values[] = {1, 3, 5, 7, 9};
    int key = 7;
    int *found = my_bsearch(&key, values, 5, sizeof values[0], compare_ints);
    printf("7 %s\n", found ? "found" : "not found");
    return 0;
}
#endif
