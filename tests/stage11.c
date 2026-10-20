#include "support.h"
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_11_keep_translation_unit_nonempty;

#if EXERCISE == 103
void run_tests(void) {
    CASE("{1,2,3,4,5} with 2 threads");
    int small[] = {1, 2, 3, 4, 5};
    INT(15, parallel_sum(small, 5, 2));
    CASE("100000 values (i) with 1, 3 and 8 threads: 4999950000");
    size_t count = 100000;
    int *values = malloc(count * sizeof *values);
    NOT_NULL(values);
    for (size_t i = 0; i < count; ++i) values[i] = (int)i;
    INT(4999950000LL, parallel_sum(values, count, 1));
    INT(4999950000LL, parallel_sum(values, count, 3));
    INT(4999950000LL, parallel_sum(values, count, 8));
    CASE("thread_count 0 behaves like 1; thread_count > count is capped");
    INT(4999950000LL, parallel_sum(values, count, 0));
    INT(15, parallel_sum(small, 5, 100));
    INT(7, parallel_sum(small + 2, 2, 7));
    CASE("count 0 and a single element");
    INT(0, parallel_sum(values, 0, 4));
    INT(0, parallel_sum(NULL, 0, 4));
    INT(-9, parallel_sum((int[]){-9}, 1, 4));
    CASE("sum exceeds int range: 100000 x INT_MAX fits in long");
    for (size_t i = 0; i < count; ++i) values[i] = INT_MAX;
    INT((intmax_t)INT_MAX * (intmax_t)count, parallel_sum(values, count, 4));
    CASE("remainder slice: 7 values over 3 threads");
    int seven[] = {10, 20, 30, 40, 50, 60, 70};
    INT(280, parallel_sum(seven, 7, 3));
    free(values);
}
#elif EXERCISE == 104
typedef struct { SafeCounter *counter; int iterations; } AddJob;
static void *adder(void *argument) {
    AddJob *job = argument;
    for (int i = 0; i < job->iterations; ++i) safe_counter_add(job->counter, 1);
    return NULL;
}
void run_tests(void) {
    CASE("fresh counter is 0; add 5 and -2 -> 3");
    SafeCounter *counter = safe_counter_new();
    NOT_NULL(counter);
    if (!counter) return;
    INT(0, safe_counter_get(counter));
    safe_counter_add(counter, 5);
    safe_counter_add(counter, -2);
    INT(3, safe_counter_get(counter));
    safe_counter_free(counter);

    CASE("8 threads x 10000 adds of 1 -> exactly 80000 (a racy version loses updates)");
    counter = safe_counter_new();
    NOT_NULL(counter);
    if (!counter) return;
    enum { THREADS = 8, ITERATIONS = 10000 };
    pthread_t threads[THREADS];
    AddJob job = {counter, ITERATIONS};
    int started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, adder, &job) == 0) ++started;
    INT(THREADS, started);
    for (int t = 0; t < started; ++t) pthread_join(threads[t], NULL);
    INT((long)THREADS * ITERATIONS, safe_counter_get(counter));

    CASE("reads interleaved with writers still finish with the exact total");
    started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, adder, &job) == 0) ++started;
    long seen = 0;
    for (int i = 0; i < 1000; ++i) {
        long now = safe_counter_get(counter);
        TRUE(now >= seen); /* never goes backwards */
        seen = now;
    }
    for (int t = 0; t < started; ++t) pthread_join(threads[t], NULL);
    INT(2L * THREADS * ITERATIONS, safe_counter_get(counter));
    safe_counter_free(counter);

    CASE("large amounts and negative totals");
    counter = safe_counter_new();
    NOT_NULL(counter);
    if (!counter) return;
    safe_counter_add(counter, LONG_MAX / 2);
    safe_counter_add(counter, -(LONG_MAX / 2));
    safe_counter_add(counter, -7);
    INT(-7, safe_counter_get(counter));
    safe_counter_free(counter);

    CASE("free(NULL) is a no-op; counters are independent");
    safe_counter_free(NULL);
    SafeCounter *a = safe_counter_new(), *b = safe_counter_new();
    NOT_NULL(a);
    NOT_NULL(b);
    if (a && b) {
        safe_counter_add(a, 1);
        INT(1, safe_counter_get(a));
        INT(0, safe_counter_get(b));
    }
    safe_counter_free(a);
    safe_counter_free(b);
}
#elif EXERCISE == 105
typedef struct { BoundedQueue *queue; int count; long sum; } QueueJob;
static void *producer(void *argument) {
    QueueJob *job = argument;
    for (int i = 0; i < job->count; ++i) bounded_queue_push(job->queue, i);
    return NULL;
}
static void *consumer(void *argument) {
    QueueJob *job = argument;
    job->sum = 0;
    for (int i = 0; i < job->count; ++i) job->sum += bounded_queue_pop(job->queue);
    return NULL;
}
void run_tests(void) {
    CASE("capacity 2: push 1, push 2, pop -> 1, pop -> 2 (FIFO, single thread)");
    BoundedQueue *queue = bounded_queue_new(2);
    NOT_NULL(queue);
    if (!queue) return;
    bounded_queue_push(queue, 1);
    bounded_queue_push(queue, 2);
    INT(1, bounded_queue_pop(queue));
    INT(2, bounded_queue_pop(queue));
    CASE("ring wrap-around: fill, drain half, fill again, drain all in order");
    bounded_queue_push(queue, 10);
    bounded_queue_push(queue, 20);
    INT(10, bounded_queue_pop(queue));
    bounded_queue_push(queue, 30);
    INT(20, bounded_queue_pop(queue));
    INT(30, bounded_queue_pop(queue));
    bounded_queue_free(queue);

    CASE("one producer pushes 0..9 into capacity 4 while main pops: order preserved");
    queue = bounded_queue_new(4);
    NOT_NULL(queue);
    if (!queue) return;
    QueueJob single = {queue, 10, 0};
    pthread_t thread;
    INT(0, pthread_create(&thread, NULL, producer, &single));
    bool in_order = true;
    for (int i = 0; i < 10; ++i)
        if (bounded_queue_pop(queue) != i) in_order = false;
    pthread_join(thread, NULL);
    TRUE(in_order);

    CASE("2 producers x 1000 and 2 consumers x 1000 over capacity 4: totals match");
    QueueJob producers[2] = {{queue, 1000, 0}, {queue, 1000, 0}};
    QueueJob consumers[2] = {{queue, 1000, 0}, {queue, 1000, 0}};
    pthread_t threads[4];
    INT(0, pthread_create(&threads[0], NULL, consumer, &consumers[0]));
    INT(0, pthread_create(&threads[1], NULL, consumer, &consumers[1]));
    INT(0, pthread_create(&threads[2], NULL, producer, &producers[0]));
    INT(0, pthread_create(&threads[3], NULL, producer, &producers[1]));
    for (int t = 0; t < 4; ++t) pthread_join(threads[t], NULL);
    INT(2L * 499500, consumers[0].sum + consumers[1].sum);
    bounded_queue_free(queue);

    CASE("capacity 1 forces strict hand-off between a producer and a consumer");
    queue = bounded_queue_new(1);
    NOT_NULL(queue);
    if (!queue) return;
    QueueJob one_producer = {queue, 500, 0}, one_consumer = {queue, 500, 0};
    INT(0, pthread_create(&threads[0], NULL, producer, &one_producer));
    INT(0, pthread_create(&threads[1], NULL, consumer, &one_consumer));
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    INT(499L * 500 / 2, one_consumer.sum);
    bounded_queue_free(queue);

    CASE("capacity 0 -> NULL; free(NULL) is a no-op");
    IS_NULL(bounded_queue_new(0));
    bounded_queue_free(NULL);
}
#elif EXERCISE == 106
static void *hitter(void *argument) {
    int iterations = *(int *)argument;
    for (int i = 0; i < iterations; ++i) atomic_hit();
    return NULL;
}
void run_tests(void) {
    CASE("reset -> 0; three hits -> 3");
    atomic_hits_reset();
    INT(0, atomic_hits());
    atomic_hit();
    atomic_hit();
    atomic_hit();
    INT(3, atomic_hits());
    CASE("reset after hits -> 0, then one hit -> 1");
    atomic_hits_reset();
    INT(0, atomic_hits());
    atomic_hit();
    INT(1, atomic_hits());
    CASE("8 threads x 10000 hits -> exactly 80000");
    atomic_hits_reset();
    enum { THREADS = 8 };
    int iterations = 10000;
    pthread_t threads[THREADS];
    int started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, hitter, &iterations) == 0) ++started;
    INT(THREADS, started);
    for (int t = 0; t < started; ++t) pthread_join(threads[t], NULL);
    INT(80000, atomic_hits());
    CASE("a second round accumulates on top: 160000");
    started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, hitter, &iterations) == 0) ++started;
    for (int t = 0; t < started; ++t) pthread_join(threads[t], NULL);
    INT(160000, atomic_hits());
    CASE("reads while hitting never go backwards");
    atomic_hits_reset();
    started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, hitter, &iterations) == 0) ++started;
    long seen = 0;
    bool monotonic = true;
    for (int i = 0; i < 1000; ++i) {
        long now = atomic_hits();
        if (now < seen) monotonic = false;
        seen = now;
    }
    for (int t = 0; t < started; ++t) pthread_join(threads[t], NULL);
    TRUE(monotonic);
    INT(80000, atomic_hits());
}
#elif EXERCISE == 107
static void *caller(void *argument) {
    int *wrong = argument;
    *wrong = 0;
    for (int i = 0; i < 1000; ++i)
        if (once_init_value() != 42) ++*wrong;
    return NULL;
}
void run_tests(void) {
    CASE("8 threads x 1000 concurrent calls: every result is 42 (init ran once)");
    enum { THREADS = 8 };
    pthread_t threads[THREADS];
    int wrong[THREADS];
    int started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, caller, &wrong[t]) == 0) ++started;
    INT(THREADS, started);
    int total_wrong = 0;
    for (int t = 0; t < started; ++t) {
        pthread_join(threads[t], NULL);
        total_wrong += wrong[t];
    }
    INT(0, total_wrong);
    CASE("main thread afterwards: still 42");
    INT(42, once_init_value());
    INT(42, once_init_value());
    CASE("a second wave of threads does not re-run init");
    started = 0;
    for (int t = 0; t < THREADS; ++t)
        if (pthread_create(&threads[t], NULL, caller, &wrong[t]) == 0) ++started;
    total_wrong = 0;
    for (int t = 0; t < started; ++t) {
        pthread_join(threads[t], NULL);
        total_wrong += wrong[t];
    }
    INT(0, total_wrong);
    INT(42, once_init_value());
}
#endif
