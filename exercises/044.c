#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Owned string of parts joined by separator; "" when count is 0. */
char *string_join(const char *const *parts, size_t count, const char *separator) {
    (void)parts;
    (void)count;
    (void)separator;
    /* TODO: implement. */
    return NULL;
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
