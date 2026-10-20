#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Owned copy of s (caller frees); NULL on NULL input or allocation failure. */
char *my_strdup(const char *s) {
    (void)s;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    char *copy = my_strdup("hello");
    if (copy) {
        printf("%s\n", copy);
        free(copy);
    }
    return 0;
}
#endif
