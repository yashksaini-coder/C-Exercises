#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* Local copies of 094/095: each exercise is compiled alone. */
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

/* 0 = got all, 1 = EOF before all (received_out tells how many arrived), -1 = error. */
static int recv_exact_local(int fd, void *buffer, size_t length, size_t *received_out) {
    unsigned char *p = buffer;
    size_t received = 0;
    while (received < length) {
        ssize_t got = recv(fd, p + received, length - received, 0);
        if (got < 0) {
            if (errno == EINTR) continue;
            if (received_out) *received_out = received;
            return -1;
        }
        if (got == 0) break;
        received += (size_t)got;
    }
    if (received_out) *received_out = received;
    return received == length ? 0 : 1;
}

/* Send a 4-byte big-endian length then the payload; 0 on success, -1 on error. */
int send_frame(int fd, const void *payload, uint32_t length) {
    unsigned char header[4] = {(unsigned char)(length >> 24), (unsigned char)(length >> 16),
                               (unsigned char)(length >> 8), (unsigned char)length};
    if (send_all_local(fd, header, sizeof header) != 0) return -1;
    if (length == 0) return 0;
    return send_all_local(fd, payload, length);
}

/* Receive one frame: payload length, -3 on clean EOF, -2 if too big, -1 on error. */
ptrdiff_t recv_frame(int fd, void *buffer, size_t capacity) {
    unsigned char header[4];
    size_t received = 0;
    int status = recv_exact_local(fd, header, sizeof header, &received);
    if (status < 0) return -1;
    if (status == 1) return received == 0 ? -3 : -1; /* clean EOF vs truncated header */

    uint32_t length = ((uint32_t)header[0] << 24) | ((uint32_t)header[1] << 16) |
                      ((uint32_t)header[2] << 8) | (uint32_t)header[3];
    if (length > capacity) return -2;
    if (length == 0) return 0;
    if (recv_exact_local(fd, buffer, length, NULL) != 0) return -1;
    return (ptrdiff_t)length;
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
