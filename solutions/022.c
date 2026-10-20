#include "exercises.h"
#include "lib.h"

char *my_strcpy(char *destination, const char *source) {
    char *d = destination;
    /* The assignment's value is the byte copied; the loop ends after the
     * NUL has been written. */
    while ((*d++ = *source++) != '\0') {
    }
    return destination;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[16];
    printf("copied: \"%s\"\n", my_strcpy(buffer, "hello"));
    return 0;
}
#endif
