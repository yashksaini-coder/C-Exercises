#include "exercises.h"
#include "lib.h"

/* Return the largest of a, b and c. */
int max_of_three(int a, int b, int c) {
    (void)a;
    (void)b;
    (void)c;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("max_of_three(1, 2, 3)  = %d\n", max_of_three(1, 2, 3));
    printf("max_of_three(9, 4, 7)  = %d\n", max_of_three(9, 4, 7));
    printf("max_of_three(-5,-2,-9) = %d\n", max_of_three(-5, -2, -9));
    return 0;
}
#endif
