#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* TODO: static helpers unlink(cache, node) and push_front(cache, node) make the rest short. */

/* Set capacity and empty the cache. */
void lru_init(LruCache *cache, size_t capacity) {
    (void)cache;
    (void)capacity;
    /* TODO: implement. */
}

/* Look up key, moving it to the front when found. */
bool lru_get(LruCache *cache, int key, int *out) {
    (void)cache;
    (void)key;
    (void)out;
    /* TODO: implement. */
    return false;
}

/* Insert or update; evict the tail when over capacity. 0 on success, -1 on allocation failure. */
int lru_put(LruCache *cache, int key, int value) {
    (void)cache;
    (void)key;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Free every node and reset the cache. */
void lru_free(LruCache *cache) {
    (void)cache;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    LruCache cache;
    lru_init(&cache, 2);
    lru_put(&cache, 1, 1);
    lru_put(&cache, 2, 2);
    lru_put(&cache, 3, 3); /* evicts key 2 */
    int value = 0;
    printf("get 2: %s\n", lru_get(&cache, 2, &value) ? "hit" : "miss");
    printf("get 3: %s %d\n", lru_get(&cache, 3, &value) ? "hit" : "miss", value);
    lru_free(&cache);
    return 0;
}
#endif
