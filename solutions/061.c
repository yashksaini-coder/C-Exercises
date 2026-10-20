#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Private representation: only this translation unit knows the layout. */
struct Counter {
    int value;
};

Counter *counter_new(int start) {
    Counter *counter = malloc(sizeof *counter);
    if (!counter) return NULL;
    counter->value = start;
    return counter;
}

void counter_increment(Counter *counter) { counter->value++; }

int counter_get(const Counter *counter) { return counter->value; }

void counter_free(Counter *counter) { free(counter); /* free(NULL) is a no-op */ }

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
