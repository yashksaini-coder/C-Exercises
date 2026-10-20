#include "exercises.h"
#include "lib.h"
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* Connect to host:port over TCP, trying every address getaddrinfo returns; fd or -1. */
int tcp_connect(const char *host, const char *port) {
    (void)host;
    (void)port;
    /* TODO: getaddrinfo(host, port) -> for each: socket, connect; freeaddrinfo. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int fd = tcp_connect("127.0.0.1", "9");
    printf("tcp_connect(127.0.0.1:9) -> %d (expected -1 unless something listens there)\n", fd);
    if (fd >= 0) close(fd);
    return 0;
}
#endif
