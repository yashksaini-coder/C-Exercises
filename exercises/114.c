#include "exercises.h"
#include "lib.h"
#include <string.h>

/* strtok_r: first call with s, later calls with NULL; all state in *state. */
char *next_token(char *s, const char *delimiters, char **state) {
    (void)s;
    (void)delimiters;
    (void)state;
    /* TODO: implement. No static variables. */
    return NULL;
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[] = "one two  three";
    char *state = NULL;
    for (char *token = next_token(text, " ", &state); token; token = next_token(NULL, " ", &state))
        printf("[%s]\n", token);
    return 0;
}
#endif
