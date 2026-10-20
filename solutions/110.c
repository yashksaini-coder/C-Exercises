#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Reverse the characters in [first, last). */
static void reverse_range(char *first, char *last) {
    while (first < last) {
        --last;
        char tmp = *first;
        *first++ = *last;
        *last = tmp;
    }
}

/* Reverse the order of single-space-separated words in place. */
void reverse_words(char *s) {
    if (!s) return;
    size_t length = strlen(s);
    reverse_range(s, s + length); /* "hello world" -> "dlrow olleh" */
    char *word = s;
    for (char *p = s;; ++p) {
        if (*p == ' ' || *p == '\0') {
            reverse_range(word, p); /* fix each word back up */
            if (*p == '\0') break;
            word = p + 1;
        }
    }
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[] = "hello world foo";
    reverse_words(text);
    printf("%s\n", text);
    return 0;
}
#endif
