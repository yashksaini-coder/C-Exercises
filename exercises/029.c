#include "exercises.h"
#include "lib.h"
#include <ctype.h>

/* Number of whitespace-separated words in s. */
size_t count_words(const char *s) {
    (void)s;
    /* TODO: implement. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("count_words(\"  leading and   trailing  \") = %zu\n",
           count_words("  leading and   trailing  "));
    return 0;
}
#endif
