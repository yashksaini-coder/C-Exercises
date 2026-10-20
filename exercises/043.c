#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Append value; grow 0->4 then double. 0 on success, -1 on failure. */
int vector_push(IntVector *vector, int value) {
    (void)vector;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Free data and zero every field. */
void vector_free(IntVector *vector) {
    (void)vector;
    /* TODO: implement. */
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
