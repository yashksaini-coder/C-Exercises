#include "exercises.h"
#include "lib.h"
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>

/* Accept one client, echo until it closes, close it; 0 on success, -1 on error. */
int echo_serve_one(int listen_fd) {
    (void)listen_fd;
    /* TODO: accept -> loop { recv; if 0 break; send back all of it } -> close. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    puts("Run the tests: make test N=99 (they start a client for you).");
    return 0;
}
#endif
