#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* One allocation holding the header and the copied string; free() releases it. */
OwnedString *owned_string_new(const char *s) {
    (void)s;
    /* TODO: implement. */
    return NULL;
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
