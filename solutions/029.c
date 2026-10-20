#include "exercises.h"
#include "lib.h"
#include <ctype.h>

size_t count_words(const char *s) {
    size_t words = 0;
    bool in_word = false;
    for (; *s; ++s) {
        if (isspace((unsigned char)*s)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++words;
        }
    }
    return words;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("count_words(\"hello world\") = %zu\n", count_words("hello world"));
    return 0;
}
#endif
