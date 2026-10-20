#include "exercises.h"
#include "lib.h"

/* Exchange *a and *b. a == b is allowed. */
void swap_int(int *a, int *b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    int x = 1, y = 2;
    swap_int(&x, &y);
    printf("after swap: x = %d, y = %d\n", x, y);
    return 0;
}
#endif
