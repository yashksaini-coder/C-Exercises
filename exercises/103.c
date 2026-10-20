#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

/* Sum values with thread_count threads, each over its own slice; join them all. */
long parallel_sum(const int *values, size_t count, size_t thread_count) {
    (void)values;
    (void)count;
    (void)thread_count;
    /* TODO: a struct per thread { const int *start; size_t length; long sum; }. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("parallel_sum = %ld\n", parallel_sum(values, 10, 3));
    return 0;
}
#endif
