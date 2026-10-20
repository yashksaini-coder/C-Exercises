#include "exercises.h"
#include "lib.h"
#include <stdatomic.h>

/* TODO: static _Atomic long hits; — the one file-scope variable this track asks for. */

/* Set the counter back to 0. */
void atomic_hits_reset(void) {
    /* TODO: atomic_store. */
}

/* Add one, safely from any number of threads at once. */
void atomic_hit(void) {
    /* TODO: atomic_fetch_add. */
}

/* Current count. */
long atomic_hits(void) {
    /* TODO: atomic_load. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    atomic_hits_reset();
    atomic_hit();
    atomic_hit();
    printf("hits = %ld\n", atomic_hits());
    return 0;
}
#endif
