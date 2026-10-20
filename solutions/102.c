#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Copy the token at *cursor (up to a space or NUL) into dest. Advances *cursor
 * past the token. Returns false if the token is empty, too long, or contains
 * a CR/LF. */
static bool take_token(const char **cursor, char *dest, size_t capacity) {
    const char *start = *cursor, *p = start;
    while (*p && *p != ' ') {
        if (*p == '\r' || *p == '\n') return false;
        ++p;
    }
    size_t length = (size_t)(p - start);
    if (length == 0 || length + 1 > capacity) return false;
    memcpy(dest, start, length);
    dest[length] = '\0';
    *cursor = p;
    return true;
}

/* Split "METHOD PATH VERSION" into out with bounds checks; false on any malformed line. */
bool parse_request_line(const char *line, RequestLine *out) {
    if (!line || !out) return false;
    const char *p = line;
    if (!take_token(&p, out->method, sizeof out->method)) return false;
    if (*p != ' ') return false;
    ++p;
    if (!take_token(&p, out->path, sizeof out->path)) return false;
    if (*p != ' ') return false;
    ++p;
    if (!take_token(&p, out->version, sizeof out->version)) return false;
    return *p == '\0'; /* nothing may follow the version */
}

#ifndef EXERCISE_TEST
int main(void) {
    RequestLine request;
    if (parse_request_line("GET /index.html HTTP/1.1", &request))
        printf("method=%s path=%s version=%s\n", request.method, request.path, request.version);
    return 0;
}
#endif
