#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Owned line without the newline; NULL at EOF with nothing read. */
char *read_line(FILE *stream) {
    (void)stream;
    /* TODO: implement with fgetc and a growing buffer. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("Type lines, Ctrl-D to stop:\n");
    char *line;
    while ((line = read_line(stdin)) != NULL) {
        printf("got [%s] (%zu chars)\n", line, strlen(line));
        free(line);
    }
    return 0;
}
#endif
