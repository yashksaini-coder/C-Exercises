#include "exercises.h"
#include "lib.h"
#include <pthread.h>

/* These statics are the exercise: pthread_once makes init() run exactly once. */
static pthread_once_t control = PTHREAD_ONCE_INIT;
static int value;
static int init_count;

static void init(void) {
    /* TODO: init_count++; value = 42; */
}

/* Initialise once, then return value + 100 * (init_count - 1): 42 iff init ran once. */
int once_init_value(void) {
    (void)control;
    (void)init;
    /* TODO: pthread_once(&control, init); then the arithmetic. */
    return value + 100 * (init_count - 1);
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("once_init_value() = %d\n", once_init_value());
    printf("once_init_value() = %d\n", once_init_value());
    return 0;
}
#endif
