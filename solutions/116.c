#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

enum { STACK_CAPACITY = 256 };

/* Parse "-?[0-9]+" occupying exactly [token, token + length). */
static bool parse_number(const char *token, size_t length, long *out) {
    size_t i = 0;
    bool negative = false;
    if (i < length && token[i] == '-') {
        negative = true;
        ++i;
    }
    if (i == length) return false; /* no digits */
    long value = 0;
    for (; i < length; ++i) {
        if (token[i] < '0' || token[i] > '9') return false;
        value = value * 10 + (token[i] - '0');
    }
    *out = negative ? -value : value;
    return true;
}

/* Evaluate an RPN expression over longs; false on any malformed input or division by zero. */
bool evaluate_rpn(const char *expression, long *result) {
    if (!expression || !result) return false;
    long stack[STACK_CAPACITY];
    size_t depth = 0;
    const char *p = expression;

    for (;;) {
        while (*p == ' ') ++p;
        if (*p == '\0') break;
        const char *token = p;
        while (*p && *p != ' ') ++p;
        size_t length = (size_t)(p - token);

        if (length == 1 && strchr("+-*/", token[0])) {
            if (depth < 2) return false; /* underflow */
            long right = stack[--depth], left = stack[--depth];
            long value;
            switch (token[0]) {
            case '+': value = left + right; break;
            case '-': value = left - right; break;
            case '*': value = left * right; break;
            default:
                if (right == 0) return false;
                value = left / right; /* truncates toward zero, as C does */
                break;
            }
            stack[depth++] = value;
        } else {
            long value;
            if (!parse_number(token, length, &value)) return false;
            if (depth == STACK_CAPACITY) return false; /* bounded stack */
            stack[depth++] = value;
        }
    }
    if (depth != 1) return false; /* nothing, or leftover operands */
    *result = stack[0];
    return true;
}

#ifndef EXERCISE_TEST
int main(void) {
    long value;
    if (evaluate_rpn("3 4 + 2 *", &value)) printf("3 4 + 2 * = %ld\n", value);
    return 0;
}
#endif
