#include "exercises.h"
#include "lib.h"
#include <string.h>

static int parse_port(const char *digits, uint16_t *port) {
    if (*digits == '\0') return -1;
    unsigned value = 0;
    for (; *digits; ++digits) {
        if (*digits < '0' || *digits > '9') return -1;
        value = value * 10 + (unsigned)(*digits - '0');
        if (value > 65535) return -1;
    }
    *port = (uint16_t)value;
    return 0;
}

/* Split "host:port" or "[v6]:port" into host and port; 0 on success, -1 on error. */
int parse_host_port(const char *s, char *host, size_t host_capacity, uint16_t *port) {
    if (!s || !host || !port) return -1;
    const char *host_start, *host_end, *port_text;

    if (s[0] == '[') {
        host_start = s + 1;
        host_end = strchr(host_start, ']');
        if (!host_end || host_end[1] != ':') return -1;
        port_text = host_end + 2;
    } else {
        host_start = s;
        host_end = strrchr(s, ':');
        if (!host_end) return -1;
        port_text = host_end + 1;
    }

    size_t host_length = (size_t)(host_end - host_start);
    if (host_length == 0 || host_length + 1 > host_capacity) return -1;

    uint16_t parsed;
    if (parse_port(port_text, &parsed) != 0) return -1;

    memcpy(host, host_start, host_length);
    host[host_length] = '\0';
    *port = parsed;
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    char host[64];
    uint16_t port;
    if (parse_host_port("[::1]:443", host, sizeof host, &port) == 0)
        printf("host=%s port=%u\n", host, (unsigned)port);
    return 0;
}
#endif
