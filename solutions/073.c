#include "exercises.h"
#include "lib.h"

bool list_has_cycle(const IntNode *head) {
    const IntNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
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
