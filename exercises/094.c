#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

/* Send every byte of buffer, looping over partial sends; 0 on success, -1 on error. */
int send_all(int fd, const void *buffer, size_t length) {
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
    if (send_all(pair[0], "hello", 5) == 0) {
        char text[6] = {0};
        ssize_t got = read(pair[1], text, 5);
        printf("received %zd bytes: %s\n", got, text);
    }
    close(pair[0]);
    close(pair[1]);
    return 0;
}
#endif
