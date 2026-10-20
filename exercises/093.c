#include "exercises.h"
#include "lib.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/* Format "A.B.C.D:port" or "[v6]:port"; 0 on success, -1 on unknown family or no room. */
int sockaddr_to_string(const struct sockaddr *address, char *destination, size_t capacity) {
    (void)address;
    (void)destination;
    (void)capacity;
    /* TODO: switch on address->sa_family, cast, inet_ntop + ntohs, snprintf. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    struct sockaddr_in v4;
    memset(&v4, 0, sizeof v4);
    v4.sin_family = AF_INET;
    v4.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &v4.sin_addr);
    char text[64];
    if (sockaddr_to_string((struct sockaddr *)&v4, text, sizeof text) == 0) puts(text);
    return 0;
}
#endif
