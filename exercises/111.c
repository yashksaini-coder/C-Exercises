#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Common prefix of all strings into out (truncated to fit); returns the full prefix length. */
size_t longest_common_prefix(const char *const *strings, size_t count, char *out, size_t capacity) {
    (void)strings;
    (void)count;
    (void)out;
    (void)capacity;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *words[] = {"flower", "flow", "flight"};
    char prefix[16];
    size_t length = longest_common_prefix(words, 3, prefix, sizeof prefix);
    printf("prefix \"%s\" (length %zu)\n", prefix, length);
    return 0;
}
#endif
