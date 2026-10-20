#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* The "next" pointer of a free block lives in its first sizeof(void *) bytes.
 * memcpy avoids alignment and aliasing questions entirely. */
static void *next_of(const void *block) {
    void *next;
    memcpy(&next, block, sizeof next);
    return next;
}

static void set_next(void *block, void *next) { memcpy(block, &next, sizeof next); }

int pool_init(Pool *pool, size_t block_size, size_t block_count) {
    if (!pool || block_count == 0) return -1;
    const size_t word = sizeof(void *);
    if (block_size < word) block_size = word;
    if (block_size > SIZE_MAX - (word - 1)) return -1;
    block_size = (block_size + word - 1) / word * word; /* round up to a multiple of a pointer */
    if (block_count > SIZE_MAX / block_size) return -1;  /* overflow */

    unsigned char *storage = malloc(block_size * block_count);
    if (!storage) return -1;

    /* Thread every block into the free list: block i -> block i+1 -> ... -> NULL. */
    for (size_t i = 0; i < block_count; ++i) {
        void *block = storage + i * block_size;
        void *next = (i + 1 < block_count) ? (void *)(storage + (i + 1) * block_size) : NULL;
        set_next(block, next);
    }
    pool->storage = storage;
    pool->free_list = storage;
    pool->block_size = block_size;
    pool->block_count = block_count;
    return 0;
}

void *pool_get(Pool *pool) {
    if (!pool || !pool->free_list) return NULL;
    void *block = pool->free_list;
    pool->free_list = next_of(block);
    return block;
}

void pool_put(Pool *pool, void *block) {
    if (!pool || !block) return;
    set_next(block, pool->free_list);
    pool->free_list = block;
}

void pool_free(Pool *pool) {
    if (!pool) return;
    free(pool->storage);
    pool->storage = NULL;
    pool->free_list = NULL;
    pool->block_size = 0;
    pool->block_count = 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    Pool p = {0};
    if (pool_init(&p, 12, 3) == 0) {
        printf("block_size=%zu block_count=%zu\n", p.block_size, p.block_count);
        void *a = pool_get(&p), *b = pool_get(&p), *c = pool_get(&p), *d = pool_get(&p);
        printf("a=%p b=%p c=%p d=%p\n", a, b, c, d);
        pool_put(&p, b);
        printf("after put(b), get -> %p\n", pool_get(&p));
        pool_free(&p);
    }
    return 0;
}
#endif
