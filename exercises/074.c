#include "exercises.h"
#include "lib.h"

/* Merge two sorted lists by relinking nodes; stable; returns the new head. */
IntNode *list_merge_sorted(IntNode *a, IntNode *b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    IntNode a3 = {5, NULL}, a2 = {3, &a3}, a1 = {1, &a2};
    IntNode b2 = {4, NULL}, b1 = {2, &b2};
    for (const IntNode *n = list_merge_sorted(&a1, &b1); n; n = n->next) printf("%d ", n->value);
    putchar('\n');
    return 0;
}
#endif
