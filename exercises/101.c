#include "exercises.h"
#include "lib.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/* Resolve hostname to its first IPv4 address as a dotted-quad; 0 on success, -1 on failure. */
int resolve_ipv4(const char *hostname, char *destination, size_t capacity) {
    (void)hostname;
    (void)destination;
    (void)capacity;
    /* TODO: getaddrinfo(AF_INET) -> first result -> inet_ntop -> freeaddrinfo. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    char text[INET_ADDRSTRLEN];
    if (resolve_ipv4("localhost", text, sizeof text) == 0) printf("localhost -> %s\n", text);
    else puts("resolve failed");
    return 0;
}
#endif
