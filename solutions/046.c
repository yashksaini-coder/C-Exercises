#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

int arena_init(Arena *arena, size_t capacity) {
    if (!arena) return -1;
    /* malloc(0) may return NULL; allocate at least one byte so init succeeds. */
    unsigned char *base = malloc(capacity ? capacity : 1);
    if (!base) return -1;
    arena->base = base;
    arena->capacity = capacity;
    arena->used = 0;
    return 0;
}

void *arena_alloc(Arena *arena, size_t size, size_t alignment) {
    if (!arena || !arena->base) return NULL;
    if (alignment == 0) alignment = 1;
    /* Round up to a multiple of alignment (a power of two). */
    size_t start = (arena->used + alignment - 1) & ~(alignment - 1);
    if (start < arena->used) return NULL;              /* overflow in rounding */
    if (start > arena->capacity) return NULL;
    if (size > arena->capacity - start) return NULL;   /* no overflow here */
    arena->used = start + size;
    return arena->base + start;
}

void arena_free(Arena *arena) {
    if (!arena) return;
    free(arena->base);
    arena->base = NULL;
    arena->capacity = 0;
    arena->used = 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    Arena a = {0};
    if (arena_init(&a, 64) == 0) {
        void *p = arena_alloc(&a, 1, 1);
        void *q = arena_alloc(&a, 4, 8);
        printf("p offset=%td q offset=%td used=%zu\n", p ? (unsigned char *)p - a.base : -1,
               q ? (unsigned char *)q - a.base : -1, a.used);
        arena_free(&a);
    }
    return 0;
}
#endif
