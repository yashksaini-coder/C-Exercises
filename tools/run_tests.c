/* Runs one test executable in a child process with a timeout, so an infinite
 * loop or a crash in your implementation is reported instead of hanging the
 * terminal. Output is passed through unchanged. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static const char *signal_name(int number) {
    switch (number) {
    case SIGSEGV: return "SIGSEGV (invalid memory access)";
    case SIGABRT: return "SIGABRT (abort, often an assert or sanitizer report)";
    case SIGFPE: return "SIGFPE (arithmetic error, e.g. divide by zero)";
    case SIGBUS: return "SIGBUS (misaligned or invalid memory access)";
    case SIGKILL: return "SIGKILL";
    default: return strsignal(number);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Usage: test-runner EXECUTABLE\n", stderr);
        return 2;
    }
    double timeout = 10;
    const char *setting = getenv("TEST_TIMEOUT");
    if (setting && atof(setting) > 0) timeout = atof(setting);

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return 2;
    }
    if (child == 0) {
        execl(argv[1], argv[1], (char *)NULL);
        perror("exec");
        _exit(2);
    }

    struct timespec started, now;
    clock_gettime(CLOCK_MONOTONIC, &started);
    int status = 0;
    for (;;) {
        pid_t result = waitpid(child, &status, WNOHANG);
        if (result == child) break;
        if (result < 0 && errno != EINTR) {
            perror("waitpid");
            return 2;
        }
        clock_gettime(CLOCK_MONOTONIC, &now);
        double elapsed = (double)(now.tv_sec - started.tv_sec) +
                         (double)(now.tv_nsec - started.tv_nsec) / 1e9;
        if (elapsed > timeout) {
            kill(child, SIGKILL);
            waitpid(child, &status, 0);
            printf("\nFAIL: test timed out after %gs (possible infinite loop or deadlock).\n",
                   timeout);
            return 1;
        }
        struct timespec pause = {0, 20 * 1000 * 1000};
        nanosleep(&pause, NULL);
    }
    if (WIFSIGNALED(status)) {
        printf("\nFAIL: test process crashed: %s.\n", signal_name(WTERMSIG(status)));
        puts("The last case printed above is the one that was running.");
        puts("Try: make test N=... SANITIZE=1 for a precise diagnosis.");
        return 1;
    }
    return WIFEXITED(status) ? WEXITSTATUS(status) : 2;
}
