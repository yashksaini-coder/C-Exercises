#include "exercises.h"
#include "lib.h"

/* Find i < j with values[i] + values[j] == target; smallest i then smallest j.
 * O(n^2). The O(n) version walks once, looking each `target - values[k]` up in
 * a hash map of value -> earliest index and inserting values[k] afterwards. */
bool two_sum(const int *values, size_t count, int target, size_t *i, size_t *j) {
    if (!values || count < 2) return false;
    for (size_t a = 0; a + 1 < count; ++a) {
        for (size_t b = a + 1; b < count; ++b) {
            /* long holds any sum of two ints without overflow. */
            if ((long)values[a] + (long)values[b] == (long)target) {
                if (i) *i = a;
                if (j) *j = b;
                return true;
            }
        }
    }
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {2, 7, 11, 15};
    size_t i, j;
    if (two_sum(values, 4, 9, &i, &j)) printf("values[%zu] + values[%zu] = 9\n", i, j);
    return 0;
}
#endif
