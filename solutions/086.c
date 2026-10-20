#include "exercises.h"
#include "lib.h"

static size_t calls;

static int tick(void) {
    ++calls;
    return 1;
}

/* The fix: arguments are evaluated once, before the call. */
static inline int min_int(int a, int b) { return a < b ? a : b; }

size_t safe_min_calls(void) {
    calls = 0;
    /* Expands to ((tick()) < (100) ? (tick()) : (100)): tick() runs twice. */
    volatile int result = MIN(tick(), 100);
    (void)result;
    return calls;
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
