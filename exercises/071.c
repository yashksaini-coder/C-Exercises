#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Append a node; 0 on success, -1 on allocation failure. */
int list_push_back(IntNode **head, int value) {
    (void)head;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Number of nodes; NULL is the empty list. */
size_t list_length(const IntNode *head) {
    (void)head;
    /* TODO: implement. */
    return 0;
}

/* Free every node. */
void list_free(IntNode *head) {
    (void)head;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    IntNode *head = NULL;
    for (int i = 1; i <= 3; ++i) list_push_back(&head, i);
    printf("length = %zu\n", list_length(head));
    for (const IntNode *n = head; n; n = n->next) printf("%d ", n->value);
    putchar('\n');
    list_free(head);
    return 0;
}
#endif
