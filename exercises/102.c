#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Split "METHOD PATH VERSION" into out with bounds checks; false on any malformed line. */
bool parse_request_line(const char *line, RequestLine *out) {
    (void)line;
    (void)out;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    RequestLine request;
    if (parse_request_line("GET /index.html HTTP/1.1", &request))
        printf("method=%s path=%s version=%s\n", request.method, request.path, request.version);
    else
        puts("parse failed");
    return 0;
}
#endif
