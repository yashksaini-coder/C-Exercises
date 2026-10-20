#include "exercises.h"
#include "lib.h"

/* Append one byte if there is room for it plus a NUL; return false if not. */
static bool put(char *destination, size_t capacity, size_t *used, char c) {
    if (*used + 1 >= capacity) return false;
    destination[(*used)++] = c;
    return true;
}

static bool put_count(char *destination, size_t capacity, size_t *used, size_t count) {
    char digits[32];
    size_t n = 0;
    do {
        digits[n++] = (char)('0' + count % 10);
        count /= 10;
    } while (count != 0);
    while (n > 0)
        if (!put(destination, capacity, used, digits[--n])) return false;
    return true;
}

int compress_runs(const char *s, char *destination, size_t capacity) {
    if (capacity == 0) return -1;
    size_t used = 0;
    while (*s) {
        char c = *s;
        size_t run = 0;
        while (*s == c) {
            ++run;
            ++s;
        }
        if (!put(destination, capacity, &used, c) ||
            (run > 1 && !put_count(destination, capacity, &used, run))) {
            destination[0] = '\0';
            return -1;
        }
    }
    destination[used] = '\0';
    return (int)used;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[32];
    int length = compress_runs("aaabccdddd", buffer, sizeof buffer);
    printf("compress_runs(\"aaabccdddd\") -> \"%s\" (%d)\n", buffer, length);
    return 0;
}
#endif
