#include "exercises.h"
#include "lib.h"

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int heap_push(MinHeap *heap, int value) {
    if (heap->count >= ARRAY_LENGTH(heap->items)) return -1;
    size_t i = heap->count++;
    heap->items[i] = value;
    /* Sift up: swap with the parent while smaller than it. */
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (heap->items[parent] <= heap->items[i]) break;
        swap(&heap->items[parent], &heap->items[i]);
        i = parent;
    }
    return 0;
}

int heap_pop(MinHeap *heap, int *out) {
    if (heap->count == 0) return -1;
    *out = heap->items[0];
    heap->items[0] = heap->items[--heap->count];
    /* Sift down: swap with the smaller child while a child is smaller. */
    size_t i = 0;
    for (;;) {
        size_t left = 2 * i + 1, right = left + 1, smallest = i;
        if (left < heap->count && heap->items[left] < heap->items[smallest]) smallest = left;
        if (right < heap->count && heap->items[right] < heap->items[smallest]) smallest = right;
        if (smallest == i) break;
        swap(&heap->items[i], &heap->items[smallest]);
        i = smallest;
    }
    return 0;
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
