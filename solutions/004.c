#include "exercises.h"
#include "lib.h"

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("gcd(48, 18) = %d\n", gcd(48, 18));
    return 0;
}
#endif
