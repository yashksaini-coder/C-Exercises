#include "exercises.h"
#include "lib.h"
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

/* djb2: h = 5381; for each byte c: h = h * 33 + c. */
uint64_t hash_djb2(const char *s) {
    (void)s;
    /* TODO: implement. */
    return 0;
}

/* Insert or overwrite; copies the key. 0 on success, -1 on allocation failure. */
int hashmap_put(HashMap *map, const char *key, int value) {
    (void)map;
    (void)key;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Look up key; true and *out set when present. */
bool hashmap_get(const HashMap *map, const char *key, int *out) {
    (void)map;
    (void)key;
    (void)out;
    /* TODO: implement. */
    return false;
}

/* Free every entry and key; leave the map zeroed. */
void hashmap_free(HashMap *map) {
    (void)map;
    /* TODO: implement. */
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
