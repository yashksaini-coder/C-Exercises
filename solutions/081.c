#include "exercises.h"
#include "lib.h"
#include <stdio.h>

int copy_file(const char *source_path, const char *destination_path) {
    FILE *in = fopen(source_path, "rb");
    if (!in) return -1;
    FILE *out = fopen(destination_path, "wb");
    if (!out) {
        fclose(in);
        return -1;
    }
    int status = 0;
    unsigned char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof buffer, in)) > 0) {
        if (fwrite(buffer, 1, n, out) != n) {
            status = -1;
            break;
        }
    }
    if (ferror(in)) status = -1; /* fread returned 0 because of an error, not EOF */
    if (fclose(out) != 0) status = -1; /* flushing can fail too */
    fclose(in);
    return status;
}

#ifndef EXERCISE_TEST
int main(void) {
    int result = copy_file("exercises/081.md", "build/081-copy.md");
    printf("copy_file -> %d\n", result);
    return 0;
}
#endif
