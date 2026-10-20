#include "exercises.h"
#include "lib.h"
#include <stdatomic.h>

static _Atomic long hits = 0;

/* Set the counter back to 0. */
void atomic_hits_reset(void) { atomic_store(&hits, 0); }

/* Add one, safely from any number of threads at once. A relaxed order would
 * also be correct for a pure counter; seq_cst is the readable default. */
void atomic_hit(void) { atomic_fetch_add(&hits, 1); }

/* Current count. */
long atomic_hits(void) { return atomic_load(&hits); }

#ifndef EXERCISE_TEST
int main(void) {
    atomic_hits_reset();
    atomic_hit();
    atomic_hit();
    printf("hits = %ld\n", atomic_hits());
    return 0;
}
#endif
