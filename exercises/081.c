#include "exercises.h"
#include "lib.h"
#include <stdio.h>

/* Copy source to destination in 4096-byte chunks; 0 on success, -1 on any failure. */
int copy_file(const char *source_path, const char *destination_path) {
    (void)source_path;
    (void)destination_path;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    int result = copy_file("exercises/081.md", "build/081-copy.md");
    printf("copy_file -> %d\n", result);
    return 0;
}
#endif
