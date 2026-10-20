#include "exercises.h"
#include "lib.h"

/* Push value; 0 on success, -1 when full. */
int stack_push(Stack *stack, int value) {
    (void)stack;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* Pop into *out; 0 on success, -1 when empty. */
int stack_pop(Stack *stack, int *out) {
    (void)stack;
    (void)out;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    Stack s = {0};
    for (int i = 1; i <= 3; ++i) stack_push(&s, i);
    int value;
    while (stack_pop(&s, &value) == 0) printf("%d ", value);
    putchar('\n');
    return 0;
}
#endif
