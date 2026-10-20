#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Owned copy of count ints (caller frees); NULL on NULL input or failure. */
int *array_clone(const int *values, size_t count) {
    (void)values;
    (void)count;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    int original[] = {1, 2, 3};
    int *copy = array_clone(original, 3);
    if (copy) {
        printf("%d %d %d\n", copy[0], copy[1], copy[2]);
        free(copy);
    }
    return 0;
}
#endif
