#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Append s, doubling capacity as needed; 0 on success, -1 on failure. */
int sb_append(StringBuilder *sb, const char *s) {
    (void)sb;
    (void)s;
    /* TODO: implement. */
    return -1;
}

/* Hand the owned buffer to the caller ("" if empty) and reset sb to {0}. */
char *sb_finish(StringBuilder *sb) {
    (void)sb;
    /* TODO: implement. */
    return NULL;
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
