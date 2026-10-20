#include "support.h"
#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef int stage_10_keep_translation_unit_nonempty;

#if EXERCISE >= 89 && EXERCISE <= 102
/* ---- shared helpers for the socket tests (test-side only) ---- */

/* Every test-side read/write carries a 3 s timeout so a stub that never
 * services the other end makes the test FAIL quickly instead of hanging. */
static void test_arm_timeout(int fd) {
    struct timeval limit = {1, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &limit, sizeof limit);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &limit, sizeof limit);
}

/* Write every byte with plain write(); test-side helper, not the exercise. */
static int test_write_all(int fd, const void *buffer, size_t length) {
    test_arm_timeout(fd);
    const unsigned char *p = buffer;
    while (length > 0) {
        ssize_t n = write(fd, p, length);
        if (n < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        p += n;
        length -= (size_t)n;
    }
    return 0;
}

/* Read until length bytes or EOF; returns bytes read. */
static size_t test_read_upto(int fd, void *buffer, size_t length) {
    test_arm_timeout(fd);
    unsigned char *p = buffer;
    size_t total = 0;
    while (total < length) {
        ssize_t n = read(fd, p + total, length - total);
        if (n < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (n == 0) break;
        total += (size_t)n;
    }
    return total;
}

/* Listening IPv4 socket on 127.0.0.1 with a kernel-chosen port; writes the port. */
static int test_listen_loopback(uint16_t *port_out) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    struct sockaddr_in address;
    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = 0;
    if (bind(fd, (struct sockaddr *)&address, sizeof address) != 0 || listen(fd, 4) != 0) {
        close(fd);
        return -1;
    }
    socklen_t length = sizeof address;
    if (getsockname(fd, (struct sockaddr *)&address, &length) != 0) {
        close(fd);
        return -1;
    }
    *port_out = ntohs(address.sin_port);
    return fd;
}

static uint16_t test_local_port(int fd) {
    struct sockaddr_in address;
    socklen_t length = sizeof address;
    if (getsockname(fd, (struct sockaddr *)&address, &length) != 0) return 0;
    return ntohs(address.sin_port);
}

static int test_connect_loopback(uint16_t port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    struct sockaddr_in address;
    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(port);
    if (connect(fd, (struct sockaddr *)&address, sizeof address) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

static void test_fill_pattern(unsigned char *buffer, size_t length) {
    for (size_t i = 0; i < length; ++i) buffer[i] = (unsigned char)(i * 31 + (i >> 8));
}

typedef struct {
    int fd;
    unsigned char *buffer;
    size_t length;
    size_t received;
} DrainJob;

static void *drain_thread(void *argument) {
    DrainJob *job = argument;
    job->received = test_read_upto(job->fd, job->buffer, job->length);
    return NULL;
}

typedef struct {
    int fd;
    const unsigned char *buffer;
    size_t length;
    int status;
} FeedJob;

static void *feed_thread(void *argument) {
    FeedJob *job = argument;
    job->status = test_write_all(job->fd, job->buffer, job->length);
    return NULL;
}

/* Cast away the unused warning in stages that do not use every helper. */
static void test_helpers_unused(void) {
    (void)test_write_all;
    (void)test_read_upto;
    (void)test_listen_loopback;
    (void)test_local_port;
    (void)test_connect_loopback;
    (void)test_fill_pattern;
    (void)drain_thread;
    (void)feed_thread;
}
#endif

#if EXERCISE == 89
void run_tests(void) {
    test_helpers_unused();
    uint8_t out[4];
    CASE("192.168.1.10");
    TRUE(parse_ipv4("192.168.1.10", out));
    BYTES("\xC0\xA8\x01\x0A", out, 4);
    CASE("boundaries: 0.0.0.0, 255.255.255.255, leading zeros 010.0.0.1");
    TRUE(parse_ipv4("0.0.0.0", out));
    BYTES("\0\0\0\0", out, 4);
    TRUE(parse_ipv4("255.255.255.255", out));
    BYTES("\xFF\xFF\xFF\xFF", out, 4);
    TRUE(parse_ipv4("010.0.0.1", out));
    BYTES("\x0A\0\0\x01", out, 4);
    CASE("octet > 255 and overflow of the accumulator");
    FALSE(parse_ipv4("256.1.1.1", out));
    FALSE(parse_ipv4("1.1.1.999", out));
    FALSE(parse_ipv4("1.1.1.4294967297", out));
    CASE("missing, empty and extra octets");
    FALSE(parse_ipv4("1.2.3", out));
    FALSE(parse_ipv4("1..2.3", out));
    FALSE(parse_ipv4("1.2.3.", out));
    FALSE(parse_ipv4(".1.2.3", out));
    FALSE(parse_ipv4("1.2.3.4.5", out));
    FALSE(parse_ipv4("", out));
    CASE("non-digits and trailing garbage");
    FALSE(parse_ipv4("1.2.3.4x", out));
    FALSE(parse_ipv4("1.2.3.4 ", out));
    FALSE(parse_ipv4("a.b.c.d", out));
    FALSE(parse_ipv4("1.2.3.-4", out));
}
#elif EXERCISE == 90
void run_tests(void) {
    test_helpers_unused();
    char text[16];
    CASE("{192,168,1,10} into 16 bytes");
    memset(text, 'X', sizeof text);
    INT(12, format_ipv4((uint8_t[]){192, 168, 1, 10}, text, sizeof text));
    STRING("192.168.1.10", text);
    CASE("shortest and longest: 0.0.0.0, 255.255.255.255");
    INT(7, format_ipv4((uint8_t[]){0, 0, 0, 0}, text, sizeof text));
    STRING("0.0.0.0", text);
    INT(15, format_ipv4((uint8_t[]){255, 255, 255, 255}, text, sizeof text));
    STRING("255.255.255.255", text);
    CASE("exact fit: 7 chars + NUL in 8 bytes; 7 bytes is too small");
    INT(7, format_ipv4((uint8_t[]){0, 0, 0, 0}, text, 8));
    STRING("0.0.0.0", text);
    memcpy(text, "untouched", 10);
    INT(-1, format_ipv4((uint8_t[]){0, 0, 0, 0}, text, 7));
    STRING("untouched", text);
    CASE("capacity 0 and NULL destination");
    INT(-1, format_ipv4((uint8_t[]){1, 2, 3, 4}, text, 0));
    INT(-1, format_ipv4((uint8_t[]){1, 2, 3, 4}, NULL, 16));
    CASE("mixed widths: 10.0.200.5, no zero padding");
    INT(10, format_ipv4((uint8_t[]){10, 0, 200, 5}, text, sizeof text));
    STRING("10.0.200.5", text);
}
#elif EXERCISE == 91
void run_tests(void) {
    test_helpers_unused();
    CASE("10.1.2.3 in 10.0.0.0/8; 11.0.0.0 not");
    TRUE(ipv4_in_subnet((uint8_t[]){10, 1, 2, 3}, (uint8_t[]){10, 0, 0, 0}, 8));
    FALSE(ipv4_in_subnet((uint8_t[]){11, 0, 0, 0}, (uint8_t[]){10, 0, 0, 0}, 8));
    CASE("192.168.x.x /16 and host bits in the network argument");
    TRUE(ipv4_in_subnet((uint8_t[]){192, 168, 1, 10}, (uint8_t[]){192, 168, 0, 0}, 16));
    FALSE(ipv4_in_subnet((uint8_t[]){192, 169, 1, 10}, (uint8_t[]){192, 168, 0, 0}, 16));
    TRUE(ipv4_in_subnet((uint8_t[]){192, 168, 1, 10}, (uint8_t[]){192, 168, 77, 77}, 16));
    CASE("/0 matches everything (the shift-by-32 trap)");
    TRUE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 4}, (uint8_t[]){200, 200, 200, 200}, 0));
    TRUE(ipv4_in_subnet((uint8_t[]){255, 255, 255, 255}, (uint8_t[]){0, 0, 0, 0}, 0));
    CASE("/32 is exact match only; /31 pairs");
    TRUE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 4}, (uint8_t[]){1, 2, 3, 4}, 32));
    FALSE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 4}, (uint8_t[]){1, 2, 3, 5}, 32));
    TRUE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 4}, (uint8_t[]){1, 2, 3, 5}, 31));
    FALSE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 6}, (uint8_t[]){1, 2, 3, 5}, 31));
    CASE("prefix in the middle of a byte: /20, and prefix > 32");
    TRUE(ipv4_in_subnet((uint8_t[]){172, 16, 15, 255}, (uint8_t[]){172, 16, 0, 0}, 20));
    FALSE(ipv4_in_subnet((uint8_t[]){172, 16, 16, 0}, (uint8_t[]){172, 16, 0, 0}, 20));
    FALSE(ipv4_in_subnet((uint8_t[]){1, 2, 3, 4}, (uint8_t[]){1, 2, 3, 4}, 33));
}
#elif EXERCISE == 92
void run_tests(void) {
    test_helpers_unused();
    char host[64];
    uint16_t port = 1;
    CASE("example.com:8080");
    INT(0, parse_host_port("example.com:8080", host, sizeof host, &port));
    STRING("example.com", host);
    UINT(8080, port);
    CASE("[::1]:443 and 127.0.0.1:80");
    INT(0, parse_host_port("[::1]:443", host, sizeof host, &port));
    STRING("::1", host);
    UINT(443, port);
    INT(0, parse_host_port("127.0.0.1:80", host, sizeof host, &port));
    STRING("127.0.0.1", host);
    UINT(80, port);
    CASE("port boundaries: 0, 65535, 65536, huge");
    INT(0, parse_host_port("h:0", host, sizeof host, &port));
    UINT(0, port);
    INT(0, parse_host_port("h:65535", host, sizeof host, &port));
    UINT(65535, port);
    INT(-1, parse_host_port("h:65536", host, sizeof host, &port));
    INT(-1, parse_host_port("h:99999999999999999999", host, sizeof host, &port));
    CASE("missing port, empty host, bad digits, unclosed bracket");
    INT(-1, parse_host_port("example.com", host, sizeof host, &port));
    INT(-1, parse_host_port("example.com:", host, sizeof host, &port));
    INT(-1, parse_host_port(":80", host, sizeof host, &port));
    INT(-1, parse_host_port("[]:80", host, sizeof host, &port));
    INT(-1, parse_host_port("host:80a", host, sizeof host, &port));
    INT(-1, parse_host_port("host:-1", host, sizeof host, &port));
    INT(-1, parse_host_port("[::1:443", host, sizeof host, &port));
    INT(-1, parse_host_port("[::1]443", host, sizeof host, &port));
    CASE("host capacity: 'example.com' needs 12 bytes");
    INT(0, parse_host_port("example.com:80", host, 12, &port));
    STRING("example.com", host);
    INT(-1, parse_host_port("example.com:80", host, 11, &port));
    INT(-1, parse_host_port("example.com:80", host, 8, &port));
}
#elif EXERCISE == 93
void run_tests(void) {
    test_helpers_unused();
    char text[64];
    struct sockaddr_in v4;
    memset(&v4, 0, sizeof v4);
    v4.sin_family = AF_INET;
    v4.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &v4.sin_addr);
    CASE("sockaddr_in 127.0.0.1:8080");
    INT(0, sockaddr_to_string((struct sockaddr *)&v4, text, sizeof text));
    STRING("127.0.0.1:8080", text);
    CASE("sockaddr_in6 [::1]:443");
    struct sockaddr_in6 v6;
    memset(&v6, 0, sizeof v6);
    v6.sin6_family = AF_INET6;
    v6.sin6_port = htons(443);
    inet_pton(AF_INET6, "::1", &v6.sin6_addr);
    INT(0, sockaddr_to_string((struct sockaddr *)&v6, text, sizeof text));
    STRING("[::1]:443", text);
    CASE("sockaddr_in6 [2001:db8::1]:65535 (port byte order matters)");
    v6.sin6_port = htons(65535);
    inet_pton(AF_INET6, "2001:db8::1", &v6.sin6_addr);
    INT(0, sockaddr_to_string((struct sockaddr *)&v6, text, sizeof text));
    STRING("[2001:db8::1]:65535", text);
    CASE("unknown family and NULL");
    struct sockaddr generic;
    memset(&generic, 0, sizeof generic);
    generic.sa_family = AF_UNIX;
    INT(-1, sockaddr_to_string(&generic, text, sizeof text));
    INT(-1, sockaddr_to_string(NULL, text, sizeof text));
    CASE("too small: '127.0.0.1:8080' needs 15 bytes");
    INT(0, sockaddr_to_string((struct sockaddr *)&v4, text, 15));
    STRING("127.0.0.1:8080", text);
    INT(-1, sockaddr_to_string((struct sockaddr *)&v4, text, 14));
    INT(-1, sockaddr_to_string((struct sockaddr *)&v4, text, 10));
}
#elif EXERCISE == 94
void run_tests(void) {
    test_helpers_unused();
    int pair[2];
    CASE("\"hello\" over a socketpair");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    INT(0, send_all(pair[0], "hello", 5));
    char small[6] = {0};
    UINT(5, test_read_upto(pair[1], small, 5));
    STRING("hello", small);
    CASE("length 0 sends nothing");
    INT(0, send_all(pair[0], "ignored", 0));
    close(pair[0]);
    close(pair[1]);

    CASE("1 MiB with a tiny send buffer and a concurrent reader (partial sends)");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    int small_buffer = 4096;
    setsockopt(pair[0], SOL_SOCKET, SO_SNDBUF, &small_buffer, sizeof small_buffer);
    setsockopt(pair[1], SOL_SOCKET, SO_RCVBUF, &small_buffer, sizeof small_buffer);
    size_t big = 1u << 20;
    unsigned char *source = malloc(big), *sink = malloc(big + 1);
    NOT_NULL(source);
    NOT_NULL(sink);
    test_fill_pattern(source, big);
    DrainJob job = {pair[1], sink, big + 1, 0};
    pthread_t reader;
    INT(0, pthread_create(&reader, NULL, drain_thread, &job));
    INT(0, send_all(pair[0], source, big));
    close(pair[0]); /* EOF lets the reader finish */
    pthread_join(reader, NULL);
    UINT(big, job.received);
    BYTES(source, sink, big);
    close(pair[1]);
    free(source);
    free(sink);

    CASE("invalid descriptor");
    INT(-1, send_all(-1, "x", 1));
    CASE("peer closed: send fails instead of looping forever");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    close(pair[1]);
    signal(SIGPIPE, SIG_IGN);
    unsigned char junk[64] = {0};
    INT(-1, send_all(pair[0], junk, sizeof junk));
    close(pair[0]);
}
#elif EXERCISE == 95
void run_tests(void) {
    test_helpers_unused();
    int pair[2];
    char text[8];
    CASE("\"abcdef\" available, ask for 4: leaves \"ef\"");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    INT(0, test_write_all(pair[0], "abcdef", 6));
    memset(text, 0, sizeof text);
    INT(0, recv_exact(pair[1], text, 4));
    STRING("abcd", text);
    memset(text, 0, sizeof text);
    INT(0, recv_exact(pair[1], text, 2));
    STRING("ef", text);
    CASE("length 0 is a no-op");
    INT(0, recv_exact(pair[1], text, 0));
    CASE("\"ab\" then EOF, ask for 4 -> 1");
    INT(0, test_write_all(pair[0], "ab", 2));
    close(pair[0]);
    INT(1, recv_exact(pair[1], text, 4));
    CASE("EOF with nothing pending -> 1");
    INT(1, recv_exact(pair[1], text, 1));
    close(pair[1]);

    CASE("65536 bytes fed in pieces by another thread");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    int small_buffer = 4096;
    setsockopt(pair[0], SOL_SOCKET, SO_SNDBUF, &small_buffer, sizeof small_buffer);
    size_t big = 65536;
    unsigned char *source = malloc(big), *sink = malloc(big);
    NOT_NULL(source);
    NOT_NULL(sink);
    test_fill_pattern(source, big);
    memset(sink, 0, big);
    FeedJob job = {pair[0], source, big, -1};
    pthread_t writer;
    INT(0, pthread_create(&writer, NULL, feed_thread, &job));
    INT(0, recv_exact(pair[1], sink, big));
    pthread_join(writer, NULL);
    INT(0, job.status);
    BYTES(source, sink, big);
    close(pair[0]);
    close(pair[1]);
    free(source);
    free(sink);

    CASE("invalid descriptor -> -1");
    INT(-1, recv_exact(-1, text, 1));
}
#elif EXERCISE == 96
typedef struct { int fd; const unsigned char *data; size_t length; int status; } FrameJob;
static void *frame_thread(void *argument) {
    FrameJob *job = argument;
    job->status = send_frame(job->fd, job->data, (uint32_t)job->length);
    return NULL;
}
void run_tests(void) {
    test_helpers_unused();
    int pair[2];
    unsigned char buffer[64];
    CASE("send_frame(\"hello\") wire format");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    INT(0, send_frame(pair[0], "hello", 5));
    UINT(9, test_read_upto(pair[1], buffer, 9));
    BYTES("\0\0\0\x05hello", buffer, 9);
    CASE("round trip several frames, including an empty one");
    INT(0, send_frame(pair[0], "one", 3));
    INT(0, send_frame(pair[0], "", 0));
    INT(0, send_frame(pair[0], "three!", 6));
    memset(buffer, 0, sizeof buffer);
    INT(3, recv_frame(pair[1], buffer, sizeof buffer));
    BYTES("one", buffer, 3);
    INT(0, recv_frame(pair[1], buffer, sizeof buffer));
    memset(buffer, 0, sizeof buffer);
    INT(6, recv_frame(pair[1], buffer, sizeof buffer));
    BYTES("three!", buffer, 6);
    CASE("frame bigger than capacity -> -2");
    INT(0, test_write_all(pair[0], "\0\0\x10\0", 4)); /* length 4096 */
    INT(-2, recv_frame(pair[1], buffer, sizeof buffer));
    close(pair[0]);
    close(pair[1]);

    CASE("clean EOF before any header -> -3");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    close(pair[0]);
    INT(-3, recv_frame(pair[1], buffer, sizeof buffer));
    close(pair[1]);
    CASE("truncated payload: header says 5, only \"hi\" arrives -> -1");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    INT(0, test_write_all(pair[0], "\0\0\0\x05hi", 6));
    close(pair[0]);
    INT(-1, recv_frame(pair[1], buffer, sizeof buffer));
    close(pair[1]);
    CASE("truncated header: 2 bytes then EOF -> -1");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    INT(0, test_write_all(pair[0], "\0\0", 2));
    close(pair[0]);
    INT(-1, recv_frame(pair[1], buffer, sizeof buffer));
    close(pair[1]);

    CASE("large frame (200000 bytes) through a small socket buffer");
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    int small_buffer = 4096;
    setsockopt(pair[0], SOL_SOCKET, SO_SNDBUF, &small_buffer, sizeof small_buffer);
    size_t big = 200000;
    unsigned char *source = malloc(big), *sink = malloc(big);
    NOT_NULL(source);
    NOT_NULL(sink);
    test_fill_pattern(source, big);
    /* send_frame in a thread: the socket cannot hold it all at once. */
    FrameJob job = {pair[0], source, big, -1};
    pthread_t sender;
    INT(0, pthread_create(&sender, NULL, frame_thread, &job));
    INT((intmax_t)big, recv_frame(pair[1], sink, big));
    pthread_join(sender, NULL);
    INT(0, job.status);
    BYTES(source, sink, big);
    close(pair[0]);
    close(pair[1]);
    free(source);
    free(sink);
}
#elif EXERCISE == 97
void run_tests(void) {
    test_helpers_unused();
    CASE("tcp_listen(\"0\"): kernel picks a port; a client can connect and be accepted");
    int listener = tcp_listen("0");
    TRUE(listener >= 0);
    uint16_t port = test_local_port(listener);
    TRUE(port != 0);
    int client = test_connect_loopback(port);
    TRUE(client >= 0);
    int served = accept(listener, NULL, NULL);
    TRUE(served >= 0);
    INT(0, test_write_all(client, "ping", 4));
    char text[5] = {0};
    UINT(4, test_read_upto(served, text, 4));
    STRING("ping", text);
    close(served);
    close(client);
    CASE("a second listener gets a different port");
    int second = tcp_listen("0");
    TRUE(second >= 0);
    TRUE(second != listener);
    TRUE(test_local_port(second) != port);
    close(second);
    CASE("port already in use -> -1 (bind fails)");
    char taken[8];
    snprintf(taken, sizeof taken, "%u", (unsigned)port);
    INT(-1, tcp_listen(taken));
    close(listener);
    CASE("bad port strings and NULL -> -1");
    INT(-1, tcp_listen("notaport"));
    INT(-1, tcp_listen(NULL));
    CASE("after close the port is free again (SO_REUSEADDR)");
    int third = tcp_listen(taken);
    TRUE(third >= 0);
    close(third);
}
#elif EXERCISE == 98
void run_tests(void) {
    test_helpers_unused();
    uint16_t port = 0;
    int listener = test_listen_loopback(&port);
    TRUE(listener >= 0);
    char port_text[8];
    snprintf(port_text, sizeof port_text, "%u", (unsigned)port);
    CASE("connect to the test's loopback listener and exchange bytes");
    int client = tcp_connect("127.0.0.1", port_text);
    TRUE(client >= 0);
    if (client >= 0) {
        int served = accept(listener, NULL, NULL);
        TRUE(served >= 0);
        INT(0, test_write_all(client, "hi", 2));
        char text[4] = {0};
        UINT(2, test_read_upto(served, text, 2));
        STRING("hi", text);
        INT(0, test_write_all(served, "yo", 2));
        memset(text, 0, sizeof text);
        UINT(2, test_read_upto(client, text, 2));
        STRING("yo", text);
        close(served);
        close(client);
    }
    CASE("\"localhost\" also resolves to the listener");
    client = tcp_connect("localhost", port_text);
    TRUE(client >= 0);
    if (client >= 0) {
        int served = accept(listener, NULL, NULL);
        TRUE(served >= 0);
        close(served);
        close(client);
    }
    CASE("nothing listening -> -1");
    close(listener);
    INT(-1, tcp_connect("127.0.0.1", port_text));
    CASE("unparseable address and NULL -> -1");
    INT(-1, tcp_connect("256.256.256.256", "80"));
    INT(-1, tcp_connect(NULL, "80"));
    INT(-1, tcp_connect("127.0.0.1", NULL));
}
#elif EXERCISE == 99
typedef struct { int listen_fd; int status; } ServeJob;
static void *serve_thread(void *argument) {
    ServeJob *job = argument;
    job->status = echo_serve_one(job->listen_fd);
    return NULL;
}
void run_tests(void) {
    test_helpers_unused();
    uint16_t port = 0;
    int listener = test_listen_loopback(&port);
    TRUE(listener >= 0);

    CASE("one message, then three in turn, each echoed in order");
    ServeJob job = {listener, -99};
    pthread_t server;
    INT(0, pthread_create(&server, NULL, serve_thread, &job));
    int client = test_connect_loopback(port);
    TRUE(client >= 0);
    char text[16];
    INT(0, test_write_all(client, "hello", 5));
    memset(text, 0, sizeof text);
    size_t echoed = test_read_upto(client, text, 5);
    UINT(5, echoed);
    STRING("hello", text);
    const char *messages[] = {"one", "two", "three"};
    for (int i = 0; i < 3 && echoed == 5; ++i) { /* skip when the server is not echoing */
        size_t length = strlen(messages[i]);
        INT(0, test_write_all(client, messages[i], length));
        memset(text, 0, sizeof text);
        UINT(length, test_read_upto(client, text, length));
        STRING(messages[i], text);
    }
    CASE("client shuts down writing: server returns 0 and no extra bytes arrive");
    shutdown(client, SHUT_WR);
    UINT(0, test_read_upto(client, text, 1)); /* EOF: server closed */
    pthread_join(server, NULL);
    INT(0, job.status);
    close(client);

    CASE("100000 bytes written then SHUT_WR; all echoed byte-for-byte");
    if (echoed != 5) {
        close(listener);
        puts("    (skipped: the server did not echo in the first case)");
        return;
    }
    job.status = -99;
    INT(0, pthread_create(&server, NULL, serve_thread, &job));
    client = test_connect_loopback(port);
    TRUE(client >= 0);
    size_t big = 100000;
    unsigned char *source = malloc(big), *sink = malloc(big + 1);
    NOT_NULL(source);
    NOT_NULL(sink);
    test_fill_pattern(source, big);
    /* Drain concurrently: the echo would otherwise fill both socket buffers. */
    DrainJob drain = {client, sink, big + 1, 0};
    pthread_t reader;
    INT(0, pthread_create(&reader, NULL, drain_thread, &drain));
    INT(0, test_write_all(client, source, big));
    shutdown(client, SHUT_WR);
    pthread_join(reader, NULL);
    pthread_join(server, NULL);
    INT(0, job.status);
    UINT(big, drain.received);
    BYTES(source, sink, big);
    close(client);
    free(source);
    free(sink);

    CASE("the listening socket is still open afterwards; -1 as listener -> -1");
    client = test_connect_loopback(port);
    TRUE(client >= 0);
    close(client);
    int pending = accept(listener, NULL, NULL);
    TRUE(pending >= 0);
    close(pending);
    close(listener);
    INT(-1, echo_serve_one(-1));
}
#elif EXERCISE == 100
static long elapsed_ms(const struct timespec *start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec - start->tv_sec) * 1000 + (now.tv_nsec - start->tv_nsec) / 1000000;
}
void run_tests(void) {
    test_helpers_unused();
    int pair[2];
    bool ready[2] = {true, true};
    INT(0, socketpair(AF_UNIX, SOCK_STREAM, 0, pair));
    CASE("nothing ready, 50 ms timeout -> 0, both false, waited ~50 ms");
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    INT(0, wait_readable(pair, 2, 50, ready));
    long waited = elapsed_ms(&start);
    TRUE(waited >= 40 && waited < 1000);
    FALSE(ready[0]);
    FALSE(ready[1]);
    CASE("write to pair[0]: pair[1] becomes readable -> 1");
    INT(0, test_write_all(pair[0], "x", 1));
    INT(1, wait_readable(pair, 2, 50, ready));
    FALSE(ready[0]);
    TRUE(ready[1]);
    CASE("both have data -> 2; timeout 0 still reports them");
    INT(0, test_write_all(pair[1], "y", 1));
    INT(2, wait_readable(pair, 2, 0, ready));
    TRUE(ready[0]);
    TRUE(ready[1]);
    CASE("count 0 -> 0");
    INT(0, wait_readable(pair, 0, 50, ready));
    CASE("peer closed counts as readable (recv would return 0 at once)");
    char sink[4];
    UINT(1, test_read_upto(pair[1], sink, 1));
    UINT(1, test_read_upto(pair[0], sink, 1));
    close(pair[0]);
    int single[1] = {pair[1]};
    bool one[1] = {false};
    INT(1, wait_readable(single, 1, 50, one));
    TRUE(one[0]);
    close(pair[1]);
    CASE("fd -1 is ignored by poll: 0 ready");
    int none[1] = {-1};
    one[0] = true;
    INT(0, wait_readable(none, 1, 10, one));
    FALSE(one[0]);
}
#elif EXERCISE == 101
void run_tests(void) {
    test_helpers_unused();
    char text[INET_ADDRSTRLEN];
    CASE("127.0.0.1 (numeric, no DNS)");
    memset(text, 'X', sizeof text);
    INT(0, resolve_ipv4("127.0.0.1", text, sizeof text));
    STRING("127.0.0.1", text);
    CASE("localhost -> something in 127.0.0.0/8");
    memset(text, 'X', sizeof text);
    INT(0, resolve_ipv4("localhost", text, sizeof text));
    TRUE(strncmp(text, "127.", 4) == 0);
    CASE("destination too small -> -1");
    INT(-1, resolve_ipv4("127.0.0.1", text, 8));
    CASE("NULL arguments -> -1");
    INT(-1, resolve_ipv4(NULL, text, sizeof text));
    INT(-1, resolve_ipv4("127.0.0.1", NULL, sizeof text));
    CASE("unparseable numeric host -> -1 (no DNS needed)");
    INT(-1, resolve_ipv4("256.256.256.256", text, sizeof text));
    INT(-1, resolve_ipv4("", text, sizeof text));
}
#elif EXERCISE == 102
void run_tests(void) {
    test_helpers_unused();
    RequestLine request;
    CASE("GET /index.html HTTP/1.1");
    memset(&request, 'X', sizeof request);
    TRUE(parse_request_line("GET /index.html HTTP/1.1", &request));
    STRING("GET", request.method);
    STRING("/index.html", request.path);
    STRING("HTTP/1.1", request.version);
    CASE("POST / HTTP/1.0 and an unusual but well-formed method");
    TRUE(parse_request_line("POST / HTTP/1.0", &request));
    STRING("POST", request.method);
    STRING("/", request.path);
    STRING("HTTP/1.0", request.version);
    TRUE(parse_request_line("BREW /pot-1 HTCPCP/1.0", &request));
    STRING("BREW", request.method);
    STRING("HTCPCP/1.0", request.version);
    CASE("missing parts, empty tokens, trailing text, CRLF");
    FALSE(parse_request_line("GET /", &request));
    FALSE(parse_request_line("GET", &request));
    FALSE(parse_request_line("", &request));
    FALSE(parse_request_line("GET  / HTTP/1.1", &request));
    FALSE(parse_request_line(" GET / HTTP/1.1", &request));
    FALSE(parse_request_line("GET / HTTP/1.1 ", &request));
    FALSE(parse_request_line("GET / HTTP/1.1 extra", &request));
    FALSE(parse_request_line("GET / HTTP/1.1\r\n", &request));
    FALSE(parse_request_line("GET /a\rb HTTP/1.1", &request));
    CASE("method length: 7 fits, 8 does not");
    TRUE(parse_request_line("OPTIONS / HTTP/1.1", &request));
    STRING("OPTIONS", request.method);
    FALSE(parse_request_line("OPTIONSX / HTTP/1.1", &request));
    CASE("path length: 255 fits, 256 does not");
    char line[300];
    memset(line, 0, sizeof line);
    strcpy(line, "GET /");
    memset(line + 5, 'a', 254); /* path = "/" + 254 a's = 255 chars */
    strcpy(line + 259, " HTTP/1.1");
    TRUE(parse_request_line(line, &request));
    UINT(255, strlen(request.path));
    memset(line + 5, 'a', 255);
    strcpy(line + 260, " HTTP/1.1");
    FALSE(parse_request_line(line, &request));
    CASE("version length: 15 fits, 16 does not");
    TRUE(parse_request_line("GET / ABCDEFGHIJKLMNO", &request));
    STRING("ABCDEFGHIJKLMNO", request.version);
    FALSE(parse_request_line("GET / ABCDEFGHIJKLMNOP", &request));
}
#endif
