#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

char *read_line(FILE *stream) {
    if (!stream) return NULL;
    size_t capacity = 32, length = 0;
    char *line = malloc(capacity);
    if (!line) return NULL;

    int c;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) { /* keep room for the NUL */
            char *grown = realloc(line, capacity * 2);
            if (!grown) {
                free(line);
                return NULL;
            }
            line = grown;
            capacity *= 2;
        }
        line[length++] = (char)c;
    }
    if (c == EOF && length == 0) { /* nothing read at all */
        free(line);
        return NULL;
    }
    line[length] = '\0';
    return line;
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
