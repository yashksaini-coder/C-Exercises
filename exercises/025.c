#include "exercises.h"
#include "lib.h"

/* First occurrence of needle in haystack, or NULL. Empty needle -> haystack. */
char *my_strstr(const char *haystack, const char *needle) {
    (void)haystack;
    (void)needle;
    /* TODO: implement. */
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
