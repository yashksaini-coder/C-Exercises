#include "exercises.h"
#include "lib.h"
#include <string.h>

/* Split "host:port" or "[v6]:port" into host and port; 0 on success, -1 on error. */
int parse_host_port(const char *s, char *host, size_t host_capacity, uint16_t *port) {
    (void)s;
    (void)host;
    (void)host_capacity;
    (void)port;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    char host[64];
    uint16_t port;
    if (parse_host_port("[::1]:443", host, sizeof host, &port) == 0)
        printf("host=%s port=%u\n", host, (unsigned)port);
    else
        puts("parse failed");
    return 0;
}
#endif
