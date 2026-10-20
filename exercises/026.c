#include "exercises.h"
#include "lib.h"

/* Reverse s in place; the NUL stays at the end. */
void reverse_string(char *s) {
    (void)s;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    char word[] = "hello"; /* an array, not a literal: literals are read-only */
    reverse_string(word);
    printf("reversed: \"%s\"\n", word);
    return 0;
}
#endif
