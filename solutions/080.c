#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

int parse_args(int argc, char **argv, Options *out) {
    out->count = 1;
    out->verbose = false;
    out->output = NULL;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0) {
            out->verbose = true;
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) return -1; /* missing value */
            const char *text = argv[++i];
            char *end;
            long value = strtol(text, &end, 10);
            if (end == text || *end != '\0') return -1; /* empty or trailing junk */
            out->count = (int)value;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) return -1;
            out->output = argv[++i];
        } else {
            return -1; /* unknown flag or stray word */
        }
    }
    return 0;
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
