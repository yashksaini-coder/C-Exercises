#include "exercises.h"
#include "lib.h"
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

uint64_t hash_djb2(const char *s) {
    uint64_t h = 5381;
    for (const unsigned char *p = (const unsigned char *)s; *p; ++p)
        h = h * 33 + *p; /* unsigned: wraparound is defined */
    return h;
}

static size_t bucket_of(const HashMap *map, const char *key) {
    return (size_t)(hash_djb2(key) % ARRAY_LENGTH(map->buckets));
}

static HashEntry *find(const HashMap *map, const char *key) {
    for (HashEntry *e = map->buckets[bucket_of(map, key)]; e; e = e->next)
        if (strcmp(e->key, key) == 0) return e;
    return NULL;
}

int hashmap_put(HashMap *map, const char *key, int value) {
    HashEntry *existing = find(map, key);
    if (existing) {
        existing->value = value;
        return 0;
    }
    HashEntry *entry = malloc(sizeof *entry);
    if (!entry) return -1;
    size_t length = strlen(key) + 1;
    entry->key = malloc(length);
    if (!entry->key) {
        free(entry);
        return -1;
    }
    memcpy(entry->key, key, length);
    entry->value = value;
    size_t index = bucket_of(map, key);
    entry->next = map->buckets[index]; /* push front: O(1) */
    map->buckets[index] = entry;
    map->count++;
    return 0;
}

bool hashmap_get(const HashMap *map, const char *key, int *out) {
    const HashEntry *entry = find(map, key);
    if (!entry) return false;
    *out = entry->value;
    return true;
}

void hashmap_free(HashMap *map) {
    for (size_t i = 0; i < ARRAY_LENGTH(map->buckets); ++i) {
        HashEntry *e = map->buckets[i];
        while (e) {
            HashEntry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
        map->buckets[i] = NULL;
    }
    map->count = 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("djb2(\"a\") = %" PRIu64 "\n", hash_djb2("a"));
    HashMap m = {0};
    hashmap_put(&m, "one", 1);
    int v = 0;
    printf("one -> %s %d\n", hashmap_get(&m, "one", &v) ? "found" : "missing", v);
    hashmap_free(&m);
    return 0;
}
#endif
