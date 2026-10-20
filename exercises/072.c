#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Reverse in place; return the new head. */
IntNode *list_reverse(IntNode *head) {
    (void)head;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    IntNode c = {3, NULL}, b = {2, &c}, a = {1, &b};
    for (const IntNode *n = list_reverse(&a); n; n = n->next) printf("%d ", n->value);
    putchar('\n');
    return 0;
}
#endif
