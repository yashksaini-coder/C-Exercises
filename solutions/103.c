#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    const int *start;
    size_t length;
    long sum; /* written only by its own thread, read after join */
} Slice;

static void *sum_slice(void *argument) {
    Slice *slice = argument;
    long total = 0;
    for (size_t i = 0; i < slice->length; ++i) total += slice->start[i];
    slice->sum = total;
    return NULL;
}

/* Sum values with thread_count threads, each over its own slice; join them all. */
long parallel_sum(const int *values, size_t count, size_t thread_count) {
    if (count == 0 || !values) return 0;
    if (thread_count == 0) thread_count = 1;
    if (thread_count > count) thread_count = count;

    Slice *slices = calloc(thread_count, sizeof *slices);
    pthread_t *threads = calloc(thread_count, sizeof *threads);
    if (!slices || !threads) {
        free(slices);
        free(threads);
        Slice whole = {values, count, 0};
        sum_slice(&whole);
        return whole.sum;
    }

    size_t per_thread = count / thread_count;
    size_t offset = 0;
    for (size_t t = 0; t < thread_count; ++t) {
        slices[t].start = values + offset;
        slices[t].length = (t + 1 == thread_count) ? count - offset : per_thread;
        offset += slices[t].length;
    }

    bool *started = calloc(thread_count, sizeof *started);
    for (size_t t = 0; t < thread_count; ++t) {
        if (started && pthread_create(&threads[t], NULL, sum_slice, &slices[t]) == 0)
            started[t] = true;
        else
            sum_slice(&slices[t]); /* fall back to this thread */
    }

    long total = 0;
    for (size_t t = 0; t < thread_count; ++t) {
        if (started && started[t]) pthread_join(threads[t], NULL);
        total += slices[t].sum;
    }
    free(started);
    free(threads);
    free(slices);
    return total;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("parallel_sum = %ld\n", parallel_sum(values, 10, 3));
    return 0;
}
#endif
