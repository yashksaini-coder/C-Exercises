#include "exercises.h"
#include "lib.h"
#include <ctype.h>

/* Strip leading and trailing whitespace in place; return s itself. */
char *trim(char *s) {
    /* TODO: implement. */
    return s;
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[] = "  hello  ";
    printf("trimmed: \"%s\"\n", trim(text));
    return 0;
}
#endif
