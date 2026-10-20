#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

/* The full definition is private to this file; the header only forward-declares it. */
struct SafeCounter {
    long value;            /* TODO: guard every access to this... */
    pthread_mutex_t mutex; /* ...with this. */
};

/* Allocate a counter at 0 with an initialised mutex; NULL on failure. */
SafeCounter *safe_counter_new(void) {
    /* TODO: implement. */
    return NULL;
}

/* Add amount under the lock. */
void safe_counter_add(SafeCounter *counter, long amount) {
    (void)counter;
    (void)amount;
    /* TODO: implement. */
}

/* Read the value under the lock. */
long safe_counter_get(SafeCounter *counter) {
    (void)counter;
    /* TODO: implement. */
    return 0;
}

/* Destroy the mutex and free; NULL allowed. */
void safe_counter_free(SafeCounter *counter) {
    (void)counter;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    SafeCounter *counter = safe_counter_new();
    if (counter) {
        safe_counter_add(counter, 5);
        safe_counter_add(counter, -2);
        printf("counter = %ld\n", safe_counter_get(counter));
    }
    safe_counter_free(counter);
    return 0;
}
#endif
