#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

int *array_clone(const int *values, size_t count) {
    if (!values) return NULL;
    int *copy = malloc(count * sizeof *copy);
    if (!copy) return NULL;
    memcpy(copy, values, count * sizeof *copy);
    return copy;
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
