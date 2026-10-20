#include "exercises.h"
#include "lib.h"

char *my_strchr(const char *s, int c) {
    char target = (char)c;
    /* Test for a match before testing for the end so '\0' can be found. */
    for (;; ++s) {
        if (*s == target) return (char *)s;
        if (*s == '\0') return NULL;
    }
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *s = "hello";
    char *p = my_strchr(s, 'l');
    printf("my_strchr(\"hello\", 'l') -> index %td\n", p ? p - s : (ptrdiff_t)-1);
    return 0;
}
#endif
