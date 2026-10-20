#include "exercises.h"
#include "lib.h"

int sign(int value) { return (value > 0) - (value < 0); }

#ifndef EXERCISE_TEST
int main(void) {
    printf("sign(-42) = %d\n", sign(-42));
    return 0;
}
#endif
