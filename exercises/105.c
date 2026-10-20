#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

/* The full definition is private to this file; the header only forward-declares it. */
struct BoundedQueue {
    int *items;               /* TODO: ring buffer of `capacity` slots */
    size_t capacity, head, count;
    pthread_mutex_t mutex;    /* guards every field above */
    pthread_cond_t not_full;  /* producers wait here while count == capacity */
    pthread_cond_t not_empty; /* consumers wait here while count == 0 */
};

/* Allocate a queue with the given capacity; NULL on capacity 0 or failure. */
BoundedQueue *bounded_queue_new(size_t capacity) {
    (void)capacity;
    /* TODO: implement. */
    return NULL;
}

/* Append value, blocking while the queue is full. */
void bounded_queue_push(BoundedQueue *queue, int value) {
    (void)queue;
    (void)value;
    /* TODO: lock; while full wait(not_full); store; signal(not_empty); unlock. */
}

/* Remove and return the oldest value, blocking while the queue is empty. */
int bounded_queue_pop(BoundedQueue *queue) {
    (void)queue;
    /* TODO: lock; while empty wait(not_empty); take; signal(not_full); unlock. */
    return 0;
}

/* Destroy the synchronisation objects and free everything; NULL allowed. */
void bounded_queue_free(BoundedQueue *queue) {
    (void)queue;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    BoundedQueue *queue = bounded_queue_new(2);
    if (queue) {
        bounded_queue_push(queue, 1);
        bounded_queue_push(queue, 2);
        int first = bounded_queue_pop(queue), second = bounded_queue_pop(queue);
        printf("pop = %d, pop = %d\n", first, second);
    }
    bounded_queue_free(queue);
    return 0;
}
#endif
