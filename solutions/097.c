#include "exercises.h"
#include "lib.h"
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* Listen for TCP on all interfaces at port; return the fd or -1. */
int tcp_listen(const char *port) {
    if (!port) return -1;
    struct addrinfo hints, *results = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;       /* IPv4 only: deterministic without IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = AI_PASSIVE;     /* with NULL node: bind to all interfaces */
    if (getaddrinfo(NULL, port, &hints, &results) != 0) return -1;

    int fd = -1;
    for (struct addrinfo *p = results; p; p = p->ai_next) {
        fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0) continue;
        int yes = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
        if (bind(fd, p->ai_addr, p->ai_addrlen) == 0) break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(results);
    if (fd < 0) return -1;

    if (listen(fd, 16) != 0) {
        close(fd);
        return -1;
    }
    return fd;
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
