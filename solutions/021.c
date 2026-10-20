#include "exercises.h"
#include "lib.h"

size_t my_strlen(const char *s) {
    const char *p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_strlen(\"hello\") = %zu\n", my_strlen("hello"));
    return 0;
}
#endif
