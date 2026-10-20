#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

char *string_join(const char *const *parts, size_t count, const char *separator) {
    if (!separator) separator = "";
    if (count == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    if (!parts) return NULL;

    /* Pass 1: exact size. */
    size_t separator_length = strlen(separator);
    size_t total = (count - 1) * separator_length;
    for (size_t i = 0; i < count; ++i) total += strlen(parts[i]);

    char *result = malloc(total + 1);
    if (!result) return NULL;

    /* Pass 2: copy. */
    char *cursor = result;
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            memcpy(cursor, separator, separator_length);
            cursor += separator_length;
        }
        size_t part_length = strlen(parts[i]);
        memcpy(cursor, parts[i], part_length);
        cursor += part_length;
    }
    *cursor = '\0';
    return result;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *const parts[] = {"a", "b", "c"};
    char *joined = string_join(parts, 3, ", ");
    if (joined) {
        printf("%s\n", joined);
        free(joined);
    }
    return 0;
}
#endif
