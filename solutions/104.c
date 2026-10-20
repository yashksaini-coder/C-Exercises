#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

struct SafeCounter {
    long value;
    pthread_mutex_t mutex;
};

/* Allocate a counter at 0 with an initialised mutex; NULL on failure. */
SafeCounter *safe_counter_new(void) {
    SafeCounter *counter = malloc(sizeof *counter);
    if (!counter) return NULL;
    counter->value = 0;
    if (pthread_mutex_init(&counter->mutex, NULL) != 0) {
        free(counter);
        return NULL;
    }
    return counter;
}

/* Add amount under the lock. */
void safe_counter_add(SafeCounter *counter, long amount) {
    pthread_mutex_lock(&counter->mutex);
    counter->value += amount;
    pthread_mutex_unlock(&counter->mutex);
}

/* Read the value under the lock: an unlocked read racing a write is UB. */
long safe_counter_get(SafeCounter *counter) {
    pthread_mutex_lock(&counter->mutex);
    long value = counter->value;
    pthread_mutex_unlock(&counter->mutex);
    return value;
}

/* Destroy the mutex and free; NULL allowed. */
void safe_counter_free(SafeCounter *counter) {
    if (!counter) return;
    pthread_mutex_destroy(&counter->mutex);
    free(counter);
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
