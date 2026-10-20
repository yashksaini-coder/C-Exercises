#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

/* Receive exactly length bytes: 0 on success, 1 on EOF before length, -1 on error. */
int recv_exact(int fd, void *buffer, size_t length) {
    (void)fd;
    (void)buffer;
    (void)length;
    /* TODO: implement. */
    return -1;
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
