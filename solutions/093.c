#include "exercises.h"
#include "lib.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/* Format "A.B.C.D:port" or "[v6]:port"; 0 on success, -1 on unknown family or no room. */
int sockaddr_to_string(const struct sockaddr *address, char *destination, size_t capacity) {
    if (!address || !destination) return -1;
    char text[INET6_ADDRSTRLEN];
    int written;

    switch (address->sa_family) {
    case AF_INET: {
        const struct sockaddr_in *v4 = (const struct sockaddr_in *)address;
        if (!inet_ntop(AF_INET, &v4->sin_addr, text, sizeof text)) return -1;
        written = snprintf(destination, capacity, "%s:%u", text, (unsigned)ntohs(v4->sin_port));
        break;
    }
    case AF_INET6: {
        const struct sockaddr_in6 *v6 = (const struct sockaddr_in6 *)address;
        if (!inet_ntop(AF_INET6, &v6->sin6_addr, text, sizeof text)) return -1;
        written = snprintf(destination, capacity, "[%s]:%u", text, (unsigned)ntohs(v6->sin6_port));
        break;
    }
    default:
        return -1;
    }
    /* snprintf returns the length it wanted; >= capacity means truncation. */
    return (written < 0 || (size_t)written >= capacity) ? -1 : 0;
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
