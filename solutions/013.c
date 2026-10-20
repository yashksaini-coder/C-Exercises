#include "exercises.h"
#include "lib.h"

void array_reverse(int *values, size_t count) {
    if (count < 2) return;
    size_t left = 0, right = count - 1;
    while (left < right) {
        int temporary = values[left];
        values[left] = values[right];
        values[right] = temporary;
        ++left;
        --right;
    }
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4};
    array_reverse(values, 4);
    printf("reversed: %d %d %d %d\n", values[0], values[1], values[2], values[3]);
    return 0;
}
#endif
