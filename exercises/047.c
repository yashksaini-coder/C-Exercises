#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* rows x columns zeroed ints, indexable as matrix[r][c]; NULL on 0 or failure. */
int **matrix_alloc(size_t rows, size_t columns) {
    (void)rows;
    (void)columns;
    /* TODO: implement with one or two allocations. */
    return NULL;
}

/* Release everything matrix_alloc allocated. */
void matrix_free(int **matrix) {
    (void)matrix;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int **m = matrix_alloc(3, 4);
    if (m) {
        m[1][2] = 7;
        for (size_t r = 0; r < 3; ++r) {
            for (size_t c = 0; c < 4; ++c) printf("%d ", m[r][c]);
            printf("\n");
        }
        matrix_free(m);
    }
    return 0;
}
#endif
