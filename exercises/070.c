#include "exercises.h"
#include "lib.h"

/* Enqueue value; 0 on success, -1 when full. */
int queue_enqueue(Queue *queue, int value) {
    (void)queue;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Dequeue the oldest value into *out; 0 on success, -1 when empty. */
int queue_dequeue(Queue *queue, int *out) {
    (void)queue;
    (void)out;
    /* TODO: implement. */
    return -1;
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
