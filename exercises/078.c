#include "exercises.h"
#include "lib.h"

/* Push value and sift up; 0 on success, -1 when full. */
int heap_push(MinHeap *heap, int value) {
    (void)heap;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Pop the minimum into *out and sift down; 0 on success, -1 when empty. */
int heap_pop(MinHeap *heap, int *out) {
    (void)heap;
    (void)out;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    MinHeap h = {0};
    int values[] = {5, 3, 8, 1};
    for (size_t i = 0; i < 4; ++i) heap_push(&h, values[i]);
    int value;
    while (heap_pop(&h, &value) == 0) printf("%d ", value);
    putchar('\n');
    return 0;
}
#endif
