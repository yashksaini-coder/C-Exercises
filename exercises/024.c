#include "exercises.h"
#include "lib.h"

/* Pointer to the first c in s (the NUL counts), or NULL. */
char *my_strchr(const char *s, int c) {
    (void)s;
    (void)c;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *s = "hello";
    char *p = my_strchr(s, 'l');
    printf("my_strchr(\"hello\", 'l') -> index %td\n", p ? p - s : (ptrdiff_t)-1);
    return 0;
}
#endif
