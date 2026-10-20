#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

IntNode *list_reverse(IntNode *head) {
    IntNode *previous = NULL, *current = head;
    while (current) {
        IntNode *next = current->next; /* save before overwriting */
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

#ifndef EXERCISE_TEST
int main(void) {
    IntNode c = {3, NULL}, b = {2, &c}, a = {1, &b};
    for (const IntNode *n = list_reverse(&a); n; n = n->next) printf("%d ", n->value);
    putchar('\n');
    return 0;
}
#endif
