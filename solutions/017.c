#include "exercises.h"
#include "lib.h"

void matrix_transpose(size_t n, int matrix[n][n]) {
    /* Only visit the upper triangle so each pair is swapped once. */
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            int temporary = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temporary;
        }
    }
}

#ifndef EXERCISE_TEST
int main(void) {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    matrix_transpose(3, m);
    for (size_t i = 0; i < 3; ++i) printf("%d %d %d\n", m[i][0], m[i][1], m[i][2]);
    return 0;
}
#endif
