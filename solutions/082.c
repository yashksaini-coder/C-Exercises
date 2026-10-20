#include "exercises.h"
#include "lib.h"
#include <stdio.h>

size_t count_lines(FILE *stream) {
    size_t lines = 0;
    int c, last = '\n'; /* int, so EOF (-1) is distinguishable from byte 0xFF */
    while ((c = fgetc(stream)) != EOF) {
        if (c == '\n') ++lines;
        last = c;
    }
    if (last != '\n') ++lines; /* final line without a newline */
    return lines;
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
