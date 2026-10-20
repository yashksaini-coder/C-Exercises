#include "exercises.h"
#include "lib.h"

int stack_push(Stack *stack, int value) {
    if (stack->count >= ARRAY_LENGTH(stack->items)) return -1;
    stack->items[stack->count++] = value;
    return 0;
}

int stack_pop(Stack *stack, int *out) {
    if (stack->count == 0) return -1;
    *out = stack->items[--stack->count];
    return 0;
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
