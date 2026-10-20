#include "exercises.h"
#include "lib.h"

void reverse_string(char *s) {
    size_t length = 0;
    while (s[length]) ++length;
    if (length < 2) return;
    for (size_t left = 0, right = length - 1; left < right; ++left, --right) {
        char temporary = s[left];
        s[left] = s[right];
        s[right] = temporary;
    }
}

#ifndef EXERCISE_TEST
int main(void) {
    char word[] = "hello";
    reverse_string(word);
    printf("reversed: \"%s\"\n", word);
    return 0;
}
#endif
