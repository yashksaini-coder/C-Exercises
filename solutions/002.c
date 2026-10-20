#include "exercises.h"
#include "lib.h"

int max_of_three(int a, int b, int c) {
    int best = a;
    if (b > best) best = b;
    if (c > best) best = c;
    return best;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("max_of_three(1, 2, 3) = %d\n", max_of_three(1, 2, 3));
    return 0;
}
#endif
