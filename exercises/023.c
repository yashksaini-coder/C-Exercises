#include "exercises.h"
#include "lib.h"

/* <0, 0 or >0 as a sorts before, equal to, or after b (unsigned bytes). */
int my_strcmp(const char *a, const char *b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_strcmp(\"abc\", \"abd\") = %d\n", my_strcmp("abc", "abd"));
    printf("my_strcmp(\"b\", \"a\")     = %d\n", my_strcmp("b", "a"));
    return 0;
}
#endif
