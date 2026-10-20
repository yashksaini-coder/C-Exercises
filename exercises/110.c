#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Reverse the order of single-space-separated words in place. */
void reverse_words(char *s) {
    (void)s;
    /* TODO: reverse the whole string, then reverse each word. */
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[] = "hello world foo";
    reverse_words(text);
    printf("%s\n", text);
    return 0;
}
#endif
