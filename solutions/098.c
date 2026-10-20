#include "exercises.h"
#include "lib.h"
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* Connect to host:port over TCP, trying every address getaddrinfo returns; fd or -1. */
int tcp_connect(const char *host, const char *port) {
    if (!host || !port) return -1;
    struct addrinfo hints, *results = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &results) != 0) return -1;

    int fd = -1;
    for (struct addrinfo *p = results; p; p = p->ai_next) {
        fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(results);
    return fd;
}

#ifndef EXERCISE_TEST
int main(void) {
    int fd = tcp_connect("127.0.0.1", "9");
    printf("tcp_connect(127.0.0.1:9) -> %d (expected -1 unless something listens there)\n", fd);
    if (fd >= 0) close(fd);
    return 0;
}
#endif
