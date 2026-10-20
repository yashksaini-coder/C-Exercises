#include "exercises.h"
#include "lib.h"

/* Binary search a sorted array; return a pointer to a matching element or NULL. Must not call bsearch. */
void *my_bsearch(const void *key, const void *base, size_t count, size_t size, Comparator compare) {
    (void)key;
    (void)base;
    (void)count;
    (void)size;
    (void)compare;
    /* TODO: implement. */
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
