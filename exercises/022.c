#include "exercises.h"
#include "lib.h"

/* Copy source (with its NUL) into destination; return destination. */
char *my_strcpy(char *destination, const char *source) {
    (void)source;
    /* TODO: implement. */
    return destination;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[16];
    printf("copied: \"%s\"\n", my_strcpy(buffer, "hello"));
    return 0;
}
#endif
