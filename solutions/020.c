#include "exercises.h"
#include "lib.h"

size_t remove_duplicates_sorted(int *values, size_t count) {
    if (count == 0) return 0;
    size_t write = 1; /* values[0] is always kept */
    for (size_t read = 1; read < count; ++read) {
        if (values[read] != values[write - 1]) values[write++] = values[read];
    }
    return write;
}

#ifndef EXERCISE_TEST
int main(void) {
    int values[] = {1, 1, 2, 3, 3, 3, 4};
    size_t length = remove_duplicates_sorted(values, 7);
    printf("%zu distinct:", length);
    for (size_t i = 0; i < length; ++i) printf(" %d", values[i]);
    putchar('\n');
    return 0;
}
#endif
