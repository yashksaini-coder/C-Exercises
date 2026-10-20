#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Zeroed count*size bytes; NULL if the multiplication overflows or malloc fails. */
void *my_calloc(size_t count, size_t size) {
    (void)count;
    (void)size;
    /* TODO: implement with malloc + memset; no calloc. */
    return NULL;
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
