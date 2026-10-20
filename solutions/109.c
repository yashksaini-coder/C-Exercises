#include "exercises.h"
#include "lib.h"

static char closer_for(char opener) {
    switch (opener) {
    case '(': return ')';
    case '[': return ']';
    case '{': return '}';
    default: return 0;
    }
}

/* True when (), [] and {} are properly nested; other characters are ignored. */
bool balanced_brackets(const char *s) {
    if (!s) return false;
    char stack[1024];
    size_t depth = 0;
    for (; *s; ++s) {
        char c = *s;
        if (c == '(' || c == '[' || c == '{') {
            if (depth == sizeof stack) return false; /* bounded nesting */
            stack[depth++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (depth == 0) return false; /* closer with nothing open */
            if (closer_for(stack[depth - 1]) != c) return false;
            --depth;
        }
    }
    return depth == 0; /* anything still open is unbalanced */
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *samples[] = {"([]{})", "([)]", "((", ""};
    for (int i = 0; i < 4; ++i)
        printf("\"%s\" -> %s\n", samples[i], balanced_brackets(samples[i]) ? "balanced" : "not");
    return 0;
}
#endif
