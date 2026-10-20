#include "exercises.h"
#include "lib.h"

/* Each returns TYPE_NAME(value) — see the macro in exercises.h. */
const char *describe_int(int value) {
    (void)value;
    /* TODO: implement. */
    return NULL;
}

const char *describe_double(double value) {
    (void)value;
    /* TODO: implement. */
    return NULL;
}

const char *describe_string(const char *value) {
    (void)value;
    /* TODO: implement. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("%s %s %s\n", describe_int(7), describe_double(2.5), describe_string("hi"));
    printf("'a' is %s, 1.0f is %s\n", TYPE_NAME('a'), TYPE_NAME(1.0f));
    return 0;
}
#endif
