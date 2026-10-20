#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t count, size_t size) {
    /* Check before multiplying: size_t wraps silently. */
    if (size != 0 && count > SIZE_MAX / size) return NULL;
    size_t total = count * size;
    void *block = malloc(total);
    if (!block) return NULL;
    memset(block, 0, total);
    return block;
}

#ifndef EXERCISE_TEST
int main(void) {
    int *p = my_calloc(4, sizeof *p);
    if (p) {
        printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
        free(p);
    }
    printf("overflowing request -> %s\n", my_calloc(SIZE_MAX / 2, 4) ? "pointer" : "NULL");
    return 0;
}
#endif
