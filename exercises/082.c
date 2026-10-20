#include "exercises.h"
#include "lib.h"
#include <stdio.h>

/* Count lines until EOF using fgetc; an unterminated last line counts. */
size_t count_lines(FILE *stream) {
    (void)stream;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    FILE *f = fopen("exercises/082.md", "rb");
    if (!f) return 1;
    printf("082.md has %zu lines\n", count_lines(f));
    fclose(f);
    return 0;
}
#endif
