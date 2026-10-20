#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* 094 and 095 are not linked here: copy their loops as static helpers (or move
 * them into lib.c). */

/* Send a 4-byte big-endian length then the payload; 0 on success, -1 on error. */
int send_frame(int fd, const void *payload, uint32_t length) {
    (void)fd;
    (void)payload;
    (void)length;
    /* TODO: implement. */
    return -1;
}

/* Receive one frame: payload length, -3 on clean EOF, -2 if too big, -1 on error. */
ptrdiff_t recv_frame(int fd, void *buffer, size_t capacity) {
    (void)fd;
    (void)buffer;
    (void)capacity;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int pair[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, pair) != 0) return 1;
    if (send_frame(pair[0], "hello", 5) == 0) {
        char text[16] = {0};
        ptrdiff_t n = recv_frame(pair[1], text, sizeof text);
        printf("frame of %td bytes: %s\n", n, n > 0 ? text : "");
    }
    close(pair[0]);
    close(pair[1]);
    return 0;
}
#endif
