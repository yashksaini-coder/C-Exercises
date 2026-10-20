#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

static int send_all_local(int fd, const void *buffer, size_t length) {
    const unsigned char *p = buffer;
    while (length > 0) {
        ssize_t sent = send(fd, p, length, 0);
        if (sent < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (sent == 0) return -1;
        p += sent;
        length -= (size_t)sent;
    }
    return 0;
}

/* Accept one client, echo until it closes, close it; 0 on success, -1 on error. */
int echo_serve_one(int listen_fd) {
    int client;
    do {
        client = accept(listen_fd, NULL, NULL);
    } while (client < 0 && errno == EINTR);
    if (client < 0) return -1;

    unsigned char buffer[4096];
    int status = 0;
    for (;;) {
        ssize_t got = recv(client, buffer, sizeof buffer, 0);
        if (got < 0) {
            if (errno == EINTR) continue;
            status = -1;
            break;
        }
        if (got == 0) break; /* client finished sending */
        if (send_all_local(client, buffer, (size_t)got) != 0) {
            status = -1;
            break;
        }
    }
    close(client);
    return status;
}

#ifndef EXERCISE_TEST
int main(void) {
    puts("Run the tests: make test N=99 (they start a client for you).");
    return 0;
}
#endif
