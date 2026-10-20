#include "exercises.h"
#include "lib.h"

/* Run-length encode s into destination ("aaab" -> "a3b"); length or -1. */
int compress_runs(const char *s, char *destination, size_t capacity) {
    (void)s;
    (void)destination;
    (void)capacity;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[32];
    int length = compress_runs("aaabccdddd", buffer, sizeof buffer);
    printf("compress_runs(\"aaabccdddd\") -> \"%s\" (%d)\n", buffer, length);
    return 0;
}
#endif
