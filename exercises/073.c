#include "exercises.h"
#include "lib.h"

/* True if the list loops back on itself (tortoise and hare). */
bool list_has_cycle(const IntNode *head) {
    (void)head;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    IntNode c = {3, NULL}, b = {2, &c}, a = {1, &b};
    printf("straight: %d\n", list_has_cycle(&a));
    c.next = &a;
    printf("looped:   %d\n", list_has_cycle(&a));
    return 0;
}
#endif
