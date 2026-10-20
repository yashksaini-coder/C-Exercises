#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

int vector_push(IntVector *vector, int value) {
    if (!vector) return -1;
    if (vector->length == vector->capacity) {
        size_t new_capacity = vector->capacity ? vector->capacity * 2 : 4;
        /* realloc into a temporary: on failure the old block is still ours. */
        int *grown = realloc(vector->data, new_capacity * sizeof *grown);
        if (!grown) return -1;
        vector->data = grown;
        vector->capacity = new_capacity;
    }
    vector->data[vector->length++] = value;
    return 0;
}

void vector_free(IntVector *vector) {
    if (!vector) return;
    free(vector->data);
    vector->data = NULL;
    vector->length = 0;
    vector->capacity = 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    IntVector v = {0};
    for (int i = 1; i <= 5; ++i) vector_push(&v, i * i);
    for (size_t i = 0; i < v.length; ++i) printf("%d ", v.data[i]);
    printf("\nlength=%zu capacity=%zu\n", v.length, v.capacity);
    vector_free(&v);
    return 0;
}
#endif
