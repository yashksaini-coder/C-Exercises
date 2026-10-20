#include "exercises.h"
#include "lib.h"

const char *describe_int(int value) { return TYPE_NAME(value); }
const char *describe_double(double value) { return TYPE_NAME(value); }
/* Exact type match: const char * selects the "const char *" branch, not "char *". */
const char *describe_string(const char *value) { return TYPE_NAME(value); }

#ifndef EXERCISE_TEST
int main(void) {
    printf("%s %s %s\n", describe_int(7), describe_double(2.5), describe_string("hi"));
    printf("'a' is %s, 1.0f is %s\n", TYPE_NAME('a'), TYPE_NAME(1.0f));
    return 0;
}
#endif
