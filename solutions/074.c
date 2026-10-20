#include "exercises.h"
#include "lib.h"

IntNode *list_merge_sorted(IntNode *a, IntNode *b) {
    IntNode *head = NULL;
    IntNode **tail = &head; /* where the next node gets attached */
    while (a && b) {
        if (a->value <= b->value) { /* <= keeps a's node first on ties: stable */
            *tail = a;
            a = a->next;
        } else {
            *tail = b;
            b = b->next;
        }
        tail = &(*tail)->next;
    }
    *tail = a ? a : b; /* the leftover run is already sorted */
    return head;
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
