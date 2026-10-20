#include "exercises.h"
#include "lib.h"
#include <ctype.h>

char *trim(char *s) {
    size_t start = 0;
    while (s[start] && isspace((unsigned char)s[start])) ++start;
    size_t end = start;
    while (s[end]) ++end; /* one past the last byte */
    while (end > start && isspace((unsigned char)s[end - 1])) --end;
    /* Shift [start, end) to the front; a forward copy is safe because the
     * destination never runs ahead of the source. */
    size_t length = end - start;
    for (size_t i = 0; i < length; ++i) s[i] = s[start + i];
    s[length] = '\0';
    return s;
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[] = "  hello  ";
    printf("trimmed: \"%s\"\n", trim(text));
    return 0;
}
#endif
