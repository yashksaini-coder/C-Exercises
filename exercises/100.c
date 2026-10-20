#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/* Wait up to timeout_ms for any fd to be readable; fill ready[], return how many. */
int wait_readable(const int *fds, size_t count, int timeout_ms, bool *ready) {
    (void)fds;
    (void)count;
    (void)timeout_ms;
    (void)ready;
    /* TODO: implement with poll(). */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int pair[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, pair) != 0) return 1;
    bool ready[2];
    printf("idle:  %d ready\n", wait_readable(pair, 2, 50, ready));
    if (write(pair[0], "x", 1) < 0) return 1;
    printf("after write: %d ready (fd1 %s)\n", wait_readable(pair, 2, 50, ready),
           ready[1] ? "readable" : "idle");
    close(pair[0]);
    close(pair[1]);
    return 0;
}
#endif
