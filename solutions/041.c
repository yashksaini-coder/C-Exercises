#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

char *my_strdup(const char *s) {
    if (!s) return NULL;
    size_t length = strlen(s);
    char *copy = malloc(length + 1);
    if (!copy) return NULL;
    memcpy(copy, s, length + 1);
    return copy;
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
