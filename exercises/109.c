#include "exercises.h"
#include "lib.h"

/* True when (), [] and {} are properly nested; other characters are ignored. */
bool balanced_brackets(const char *s) {
    (void)s;
    /* TODO: char stack[1024]; push openers, match closers, empty at the end. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *samples[] = {"([]{})", "([)]", "((", ""};
    for (int i = 0; i < 4; ++i)
        printf("\"%s\" -> %s\n", samples[i], balanced_brackets(samples[i]) ? "balanced" : "not");
    return 0;
}
#endif
