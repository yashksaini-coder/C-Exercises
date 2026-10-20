#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Common prefix of all strings into out (truncated to fit); returns the full prefix length. */
size_t longest_common_prefix(const char *const *strings, size_t count, char *out, size_t capacity) {
    size_t length = 0;
    if (count > 0 && strings && strings[0]) {
        length = strlen(strings[0]);
        for (size_t k = 1; k < count && length > 0; ++k) {
            const char *s = strings[k];
            size_t match = 0;
            while (match < length && s[match] && s[match] == strings[0][match]) ++match;
            length = match;
        }
    }
    if (out && capacity > 0) {
        size_t copy = length < capacity - 1 ? length : capacity - 1;
        if (copy > 0) memcpy(out, strings[0], copy);
        out[copy] = '\0';
    }
    return length;
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
