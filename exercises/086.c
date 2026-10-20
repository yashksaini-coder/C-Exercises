#include "exercises.h"
#include "lib.h"

static size_t calls; /* how many times tick() ran */

/* Increment the counter and return a value below 100. */
static int tick(void) {
    /* TODO: implement. */
    return 0;
}

/* The fix: a function evaluates each argument exactly once. */
static inline int min_int(int a, int b) { return a < b ? a : b; }

/* Reset the counter, evaluate MIN(tick(), 100) once, return how many times tick() ran. */
size_t safe_min_calls(void) {
    (void)tick;
    (void)min_int;
    (void)calls;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("MIN(tick(), 100) ran tick() %zu time(s)\n", safe_min_calls());
    calls = 0;
    volatile int m = min_int(tick(), 100);
    printf("min_int(tick(), 100) = %d, ran tick() %zu time(s)\n", m, calls);
    return 0;
}
#endif
