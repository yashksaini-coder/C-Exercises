#include "exercises.h"
#include "lib.h"

char *my_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') return (char *)haystack;
    for (const char *start = haystack; *start; ++start) {
        const char *h = start;
        const char *n = needle;
        /* *h is checked implicitly: when *h == '\0' and *n != '\0' they
         * differ, so the loop stops before reading past the terminator. */
        while (*n && *h == *n) {
            ++h;
            ++n;
        }
        if (*n == '\0') return (char *)start;
    }
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *s = "hello world";
    char *p = my_strstr(s, "o w");
    printf("my_strstr(\"hello world\", \"o w\") -> index %td\n", p ? p - s : (ptrdiff_t)-1);
    return 0;
}
#endif
