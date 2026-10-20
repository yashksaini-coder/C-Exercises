#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

/* Receive exactly length bytes: 0 on success, 1 on EOF before length, -1 on error. */
int recv_exact(int fd, void *buffer, size_t length) {
    unsigned char *p = buffer;
    while (length > 0) {
        ssize_t got = recv(fd, p, length, 0);
        if (got < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (got == 0) return 1; /* orderly shutdown by the peer */
        p += got;
        length -= (size_t)got;
    }
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    int pair[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, pair) != 0) return 1;
    if (write(pair[0], "abcdef", 6) < 0) return 1;
    char text[5] = {0};
    printf("recv_exact -> %d, got \"%s\"\n", recv_exact(pair[1], text, 4), text);
    close(pair[0]);
    close(pair[1]);
    return 0;
}
#endif
