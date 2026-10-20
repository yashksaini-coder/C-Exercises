#include "exercises.h"
#include "lib.h"
#include <string.h>

/* strtok_r: first call with s, later calls with NULL; all state in *state. */
char *next_token(char *s, const char *delimiters, char **state) {
    if (!state || !delimiters) return NULL;
    if (!s) s = *state;
    if (!s) return NULL;

    s += strspn(s, delimiters); /* skip leading delimiters */
    if (*s == '\0') {
        *state = NULL;
        return NULL;
    }
    char *token = s;
    s += strcspn(s, delimiters); /* end of token */
    if (*s != '\0') {
        *s = '\0';       /* terminate the token in place */
        *state = s + 1;  /* resume after the delimiter */
    } else {
        *state = NULL;   /* that was the last one */
    }
    return token;
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
