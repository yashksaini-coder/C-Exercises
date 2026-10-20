#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

OwnedString *owned_string_new(const char *s) {
    if (!s) return NULL;
    size_t length = strlen(s);
    OwnedString *owned = malloc(sizeof *owned + length + 1);
    if (!owned) return NULL;
    owned->length = length;
    memcpy(owned->data, s, length + 1); /* +1 copies the NUL */
    return owned;
}

#ifndef EXERCISE_TEST
int main(void) {
    OwnedString *owned = owned_string_new("hello");
    if (owned) {
        printf("length=%zu data=\"%s\" sizeof(OwnedString)=%zu\n", owned->length, owned->data,
               sizeof(OwnedString));
        free(owned);
    }
    return 0;
}
#endif
