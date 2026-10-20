#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <stdio.h>

/* Format "[level] message" into buffer; returns the snprintf-style full length. */
int log_message(char *buffer, size_t capacity, const char *level, const char *format, ...) {
    (void)buffer;
    (void)capacity;
    (void)level;
    (void)format;
    /* TODO: implement with snprintf for the prefix and vsnprintf for the message. */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[64];
    int n = log_message(buffer, sizeof buffer, "INFO", "x=%d", 5);
    printf("%s (%d)\n", buffer, n);
    return 0;
}
#endif
