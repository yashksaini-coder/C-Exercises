#include "exercises.h"
#include "lib.h"

/* Transpose an n x n matrix in place. */
void matrix_transpose(size_t n, int matrix[n][n]) {
    (void)n;
    (void)matrix;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_transpose(3, m);
    for (size_t i = 0; i < 3; ++i) printf("%d %d %d\n", m[i][0], m[i][1], m[i][2]);
    return 0;
}
#endif
