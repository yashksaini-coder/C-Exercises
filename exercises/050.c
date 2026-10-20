#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* One allocation of block_size*block_count bytes threaded into an intrusive free list. */
int pool_init(Pool *pool, size_t block_size, size_t block_count) {
    (void)pool;
    (void)block_size;
    (void)block_count;
    /* TODO: implement. */
    return -1;
}

/* Pop a block from the free list; NULL when exhausted. */
void *pool_get(Pool *pool) {
    (void)pool;
    /* TODO: implement. */
    return NULL;
}

/* Push a block back onto the free list. */
void pool_put(Pool *pool, void *block) {
    (void)pool;
    (void)block;
    /* TODO: implement. */
}

/* Free storage and zero the fields. */
void pool_free(Pool *pool) {
    (void)pool;
    /* TODO: implement. */
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
