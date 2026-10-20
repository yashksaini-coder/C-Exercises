#include "exercises.h"
#include "lib.h"
#include <pthread.h>

static pthread_once_t control = PTHREAD_ONCE_INIT;
static int value;
static int init_count;

static void init(void) {
    init_count++;
    value = 42;
}

/* Initialise once, then return value + 100 * (init_count - 1): 42 iff init ran once. */
int once_init_value(void) {
    pthread_once(&control, init);
    /* pthread_once guarantees init() happened-before this point in every thread. */
    return value + 100 * (init_count - 1);
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("once_init_value() = %d\n", once_init_value());
    printf("once_init_value() = %d\n", once_init_value());
    return 0;
}
#endif
