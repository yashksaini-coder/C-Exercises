#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

int list_push_back(IntNode **head, int value) {
    IntNode *node = malloc(sizeof *node);
    if (!node) return -1;
    node->value = value;
    node->next = NULL;
    /* Walk the chain of `next` pointers until we find the NULL slot; for an
     * empty list that slot is *head itself. */
    IntNode **link = head;
    while (*link) link = &(*link)->next;
    *link = node;
    return 0;
}

size_t list_length(const IntNode *head) {
    size_t n = 0;
    for (; head; head = head->next) ++n;
    return n;
}

void list_free(IntNode *head) {
    while (head) {
        IntNode *next = head->next; /* read before free */
        free(head);
        head = next;
    }
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
