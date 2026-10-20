#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Evaluate an RPN expression over longs; false on any malformed input or division by zero. */
bool evaluate_rpn(const char *expression, long *result) {
    (void)expression;
    (void)result;
    /* TODO: long stack[256]; tokens -> push / apply operator. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    long value;
    if (evaluate_rpn("3 4 + 2 *", &value)) printf("3 4 + 2 * = %ld\n", value);
    else puts("error");
    return 0;
}
#endif
