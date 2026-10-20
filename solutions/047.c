#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

int **matrix_alloc(size_t rows, size_t columns) {
    if (rows == 0 || columns == 0) return NULL;
    if (columns > SIZE_MAX / rows / sizeof(int)) return NULL; /* overflow */

    int **matrix = malloc(rows * sizeof *matrix);
    if (!matrix) return NULL;
    int *data = calloc(rows * columns, sizeof *data); /* zeroed */
    if (!data) {
        free(matrix);
        return NULL;
    }
    for (size_t r = 0; r < rows; ++r) matrix[r] = data + r * columns;
    return matrix;
}

void matrix_free(int **matrix) {
    if (!matrix) return;
    free(matrix[0]); /* the contiguous data block */
    free(matrix);    /* the row-pointer array */
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
