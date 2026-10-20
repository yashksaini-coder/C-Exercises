#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* The full definition is private to this file; the header only forward-declares it. */
struct Counter {
    int value; /* TODO: the representation is yours; this field is a hint. */
};

/* Allocate a counter starting at `start`; NULL on allocation failure. */
Counter *counter_new(int start) {
    (void)start;
    /* TODO: implement. */
    return NULL;
}

/* Add one to the counter. */
void counter_increment(Counter *counter) {
    (void)counter;
    /* TODO: implement. */
}

/* Return the current value. */
int counter_get(const Counter *counter) {
    (void)counter;
    /* TODO: implement. */
    return 0;
}

/* Release the counter; NULL is allowed. */
void counter_free(Counter *counter) {
    (void)counter;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    Counter *c = counter_new(5);
    if (c) {
        counter_increment(c);
        printf("counter = %d\n", counter_get(c));
    }
    counter_free(c);
    return 0;
}
#endif
