#include "exercises.h"
#include "lib.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/* Resolve hostname to its first IPv4 address as a dotted-quad; 0 on success, -1 on failure. */
int resolve_ipv4(const char *hostname, char *destination, size_t capacity) {
    if (!hostname || !destination) return -1;
    struct addrinfo hints, *results = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* one entry per address, not per protocol */
    if (getaddrinfo(hostname, NULL, &hints, &results) != 0) return -1;

    int status = -1;
    if (results && results->ai_family == AF_INET) {
        const struct sockaddr_in *v4 = (const struct sockaddr_in *)results->ai_addr;
        if (inet_ntop(AF_INET, &v4->sin_addr, destination, (socklen_t)capacity)) status = 0;
    }
    freeaddrinfo(results);
    return status;
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[INET_ADDRSTRLEN];
    if (resolve_ipv4("localhost", text, sizeof text) == 0) printf("localhost -> %s\n", text);
    else puts("resolve failed");
    return 0;
}
#endif
