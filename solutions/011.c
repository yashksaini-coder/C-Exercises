#include "exercises.h"
#include "lib.h"

void swap_int(int *a, int *b) {
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

#ifndef EXERCISE_TEST
int main(void) {
    int x = 1, y = 2;
    swap_int(&x, &y);
    printf("after swap: x = %d, y = %d\n", x, y);
    return 0;
}
#endif
