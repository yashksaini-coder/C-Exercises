#include "exercises.h"
#include "lib.h"
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* Listen for TCP on all interfaces at port; return the fd or -1. */
int tcp_listen(const char *port) {
    (void)port;
    /* TODO: getaddrinfo(NULL, port, AI_PASSIVE) -> socket -> SO_REUSEADDR -> bind -> listen(16). */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int fd = tcp_listen("0");
    if (fd < 0) {
        puts("tcp_listen failed");
        return 1;
    }
    struct sockaddr_in bound;
    socklen_t length = sizeof bound;
    if (getsockname(fd, (struct sockaddr *)&bound, &length) == 0)
        printf("listening on port %u\n", (unsigned)ntohs(bound.sin_port));
    close(fd);
    return 0;
}
#endif
