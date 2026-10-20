#include "exercises.h"
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

struct BoundedQueue {
    int *items;
    size_t capacity, head, count;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
};

/* Allocate a queue with the given capacity; NULL on capacity 0 or failure. */
BoundedQueue *bounded_queue_new(size_t capacity) {
    if (capacity == 0) return NULL;
    BoundedQueue *queue = malloc(sizeof *queue);
    if (!queue) return NULL;
    queue->items = malloc(capacity * sizeof *queue->items);
    if (!queue->items) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->head = queue->count = 0;
    if (pthread_mutex_init(&queue->mutex, NULL) != 0) goto fail_mutex;
    if (pthread_cond_init(&queue->not_full, NULL) != 0) goto fail_not_full;
    if (pthread_cond_init(&queue->not_empty, NULL) != 0) goto fail_not_empty;
    return queue;

fail_not_empty:
    pthread_cond_destroy(&queue->not_full);
fail_not_full:
    pthread_mutex_destroy(&queue->mutex);
fail_mutex:
    free(queue->items);
    free(queue);
    return NULL;
}

/* Append value, blocking while the queue is full. */
void bounded_queue_push(BoundedQueue *queue, int value) {
    pthread_mutex_lock(&queue->mutex);
    /* `while`, not `if`: spurious wakeups and lost races both re-check. */
    while (queue->count == queue->capacity) pthread_cond_wait(&queue->not_full, &queue->mutex);
    queue->items[(queue->head + queue->count) % queue->capacity] = value;
    queue->count++;
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->mutex);
}

/* Remove and return the oldest value, blocking while the queue is empty. */
int bounded_queue_pop(BoundedQueue *queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->count == 0) pthread_cond_wait(&queue->not_empty, &queue->mutex);
    int value = queue->items[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;
    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->mutex);
    return value;
}

/* Destroy the synchronisation objects and free everything; NULL allowed. */
void bounded_queue_free(BoundedQueue *queue) {
    if (!queue) return;
    pthread_cond_destroy(&queue->not_empty);
    pthread_cond_destroy(&queue->not_full);
    pthread_mutex_destroy(&queue->mutex);
    free(queue->items);
    free(queue);
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
