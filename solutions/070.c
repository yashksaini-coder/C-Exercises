#include "exercises.h"
#include "lib.h"

int queue_enqueue(Queue *queue, int value) {
    size_t capacity = ARRAY_LENGTH(queue->items);
    if (queue->count >= capacity) return -1;
    queue->items[(queue->head + queue->count) % capacity] = value;
    queue->count++;
    return 0;
}

int queue_dequeue(Queue *queue, int *out) {
    size_t capacity = ARRAY_LENGTH(queue->items);
    if (queue->count == 0) return -1;
    *out = queue->items[queue->head];
    queue->head = (queue->head + 1) % capacity;
    queue->count--;
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    Queue q = {0};
    for (int i = 1; i <= 3; ++i) queue_enqueue(&q, i);
    int value;
    while (queue_dequeue(&q, &value) == 0) printf("%d ", value);
    putchar('\n');
    return 0;
}
#endif
