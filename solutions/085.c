#include "exercises.h"
#include "lib.h"
#include <stdarg.h>
#include <stdio.h>

int log_message(char *buffer, size_t capacity, const char *level, const char *format, ...) {
    int prefix = snprintf(buffer, capacity, "[%s] ", level);
    if (prefix < 0) return prefix;
    /* If the prefix was truncated, the remaining capacity is 0, not a wrapped size_t. */
    size_t used = (size_t)prefix < capacity ? (size_t)prefix : capacity;
    va_list args;
    va_start(args, format);
    int message = vsnprintf(buffer ? buffer + used : NULL, capacity - used, format, args);
    va_end(args);
    if (message < 0) return message;
    return prefix + message;
}

#ifndef EXERCISE_TEST
int main(void) {
    char buffer[64];
    int n = log_message(buffer, sizeof buffer, "INFO", "x=%d", 5);
    printf("%s (%d)\n", buffer, n);
    return 0;
}
#endif
