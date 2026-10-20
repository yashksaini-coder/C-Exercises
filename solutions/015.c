#include "exercises.h"
#include "lib.h"

ptrdiff_t find_index(const int *values, size_t count, int target) {
    for (size_t i = 0; i < count; ++i)
        if (values[i] == target) return (ptrdiff_t)i;
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {4, 8, 15, 16};
    printf("find_index(15) = %td\n", find_index(values, 4, 15));
    return 0;
}
#endif
