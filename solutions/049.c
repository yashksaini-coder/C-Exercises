#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

static int sb_reserve(StringBuilder *sb, size_t needed) {
    if (needed <= sb->capacity) return 0;
    size_t new_capacity = sb->capacity ? sb->capacity : 16;
    while (new_capacity < needed) new_capacity *= 2;
    char *grown = realloc(sb->data, new_capacity);
    if (!grown) return -1;
    sb->data = grown;
    sb->capacity = new_capacity;
    return 0;
}

int sb_append(StringBuilder *sb, const char *s) {
    if (!sb || !s) return -1;
    size_t added = strlen(s);
    if (sb_reserve(sb, sb->length + added + 1) != 0) return -1;
    memcpy(sb->data + sb->length, s, added + 1); /* includes the NUL */
    sb->length += added;
    return 0;
}

char *sb_finish(StringBuilder *sb) {
    if (!sb) return NULL;
    char *result = sb->data;
    if (!result) { /* never appended: still hand back an allocated "" */
        result = malloc(1);
        if (!result) return NULL;
        result[0] = '\0';
    } else {
        char *shrunk = realloc(result, sb->length + 1);
        if (shrunk) result = shrunk; /* shrinking is optional; keep the old block if it fails */
    }
    sb->data = NULL;
    sb->length = 0;
    sb->capacity = 0;
    return result;
}

#ifndef EXERCISE_TEST
int main(void) {
    StringBuilder sb = {0};
    sb_append(&sb, "foo");
    sb_append(&sb, "bar");
    sb_append(&sb, "!");
    char *s = sb_finish(&sb);
    if (s) {
        printf("%s\n", s);
        free(s);
    }
    return 0;
}
#endif
