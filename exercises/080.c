#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* Parse -n <int>, -v, -o <path>; 0 on success, -1 on an unknown flag or missing value. */
int parse_args(int argc, char **argv, Options *out) {
    (void)argc;
    (void)argv;
    (void)out;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(int argc, char **argv) {
    Options options;
    if (parse_args(argc, argv, &options) != 0) {
        fprintf(stderr, "usage: %s [-n count] [-v] [-o path]\n", argv[0]);
        return 1;
    }
    printf("count=%d verbose=%d output=%s\n", options.count, options.verbose,
           options.output ? options.output : "(none)");
    return 0;
}
#endif
