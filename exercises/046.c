#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* malloc capacity bytes; 0 on success, -1 on failure. */
int arena_init(Arena *arena, size_t capacity) {
    (void)arena;
    (void)capacity;
    /* TODO: implement. */
    return -1;
}

/* Bump `used` to the next multiple of alignment, then by size; NULL if it does not fit. */
void *arena_alloc(Arena *arena, size_t size, size_t alignment) {
    (void)arena;
    (void)size;
    (void)alignment;
    /* TODO: implement. */
    return NULL;
}

/* Free base and zero the fields. */
void arena_free(Arena *arena) {
    (void)arena;
    /* TODO: implement. */
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
