#include "exercises.h"
#include "lib.h"

/* Number of bytes before the terminating NUL. No strlen. */
size_t my_strlen(const char *s) {
    (void)s;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_strlen(\"hello\") = %zu\n", my_strlen("hello"));
    printf("my_strlen(\"\")      = %zu\n", my_strlen(""));
    return 0;
}
#endif
