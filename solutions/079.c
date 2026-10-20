#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Detach node from the list, fixing head/tail as needed. */
static void unlink_node(LruCache *cache, LruNode *node) {
    if (node->prev) node->prev->next = node->next;
    else cache->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else cache->tail = node->prev;
    node->prev = node->next = NULL;
}

/* Make node the most recently used entry. */
static void push_front(LruCache *cache, LruNode *node) {
    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}

static LruNode *find(const LruCache *cache, int key) {
    for (LruNode *n = cache->head; n; n = n->next)
        if (n->key == key) return n;
    return NULL;
}

void lru_init(LruCache *cache, size_t capacity) {
    cache->capacity = capacity;
    cache->count = 0;
    cache->head = cache->tail = NULL;
}

bool lru_get(LruCache *cache, int key, int *out) {
    LruNode *node = find(cache, key);
    if (!node) return false;
    unlink_node(cache, node);
    push_front(cache, node);
    *out = node->value;
    return true;
}

int lru_put(LruCache *cache, int key, int value) {
    LruNode *node = find(cache, key);
    if (node) {
        node->value = value;
        unlink_node(cache, node);
        push_front(cache, node);
        return 0;
    }
    node = malloc(sizeof *node);
    if (!node) return -1;
    node->key = key;
    node->value = value;
    push_front(cache, node);
    cache->count++;
    if (cache->count > cache->capacity) {
        LruNode *victim = cache->tail; /* least recently used */
        unlink_node(cache, victim);
        free(victim);
        cache->count--;
    }
    return 0;
}

void lru_free(LruCache *cache) {
    LruNode *n = cache->head;
    while (n) {
        LruNode *next = n->next;
        free(n);
        n = next;
    }
    cache->head = cache->tail = NULL;
    cache->count = 0;
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
