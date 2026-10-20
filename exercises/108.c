#include "exercises.h"
#include "lib.h"

/* Find i < j with values[i] + values[j] == target; smallest i then smallest j. */
bool two_sum(const int *values, size_t count, int target, size_t *i, size_t *j) {
    (void)values;
    (void)count;
    (void)target;
    (void)i;
    (void)j;
    /* TODO: implement. Compare in long to avoid int overflow. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {2, 7, 11, 15};
    size_t i, j;
    if (two_sum(values, 4, 9, &i, &j)) printf("values[%zu] + values[%zu] = 9\n", i, j);
    else puts("no pair");
    return 0;
}
#endif
