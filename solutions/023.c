#include "exercises.h"
#include "lib.h"

int my_strcmp(const char *a, const char *b) {
    const unsigned char *ua = (const unsigned char *)a;
    const unsigned char *ub = (const unsigned char *)b;
    while (*ua && *ua == *ub) {
        ++ua;
        ++ub;
    }
    /* Both are 0..255 so the subtraction cannot overflow int. */
    return (int)*ua - (int)*ub;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("my_strcmp(\"abc\", \"abd\") = %d\n", my_strcmp("abc", "abd"));
    return 0;
}
#endif
