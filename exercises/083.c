#include "exercises.h"
#include "lib.h"
#include <stdio.h>

/* fwrite the whole array; 0 on success, -1 on failure. */
int write_records(const char *path, const Record *records, size_t count) {
    (void)path;
    (void)records;
    (void)count;
    /* TODO: implement. */
    return -1;
}

/* fread up to capacity records; returns the number read, or -1 if the file cannot be opened. */
ptrdiff_t read_records(const char *path, Record *out, size_t capacity) {
    (void)path;
    (void)out;
    (void)capacity;
    /* TODO: implement. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    Record records[2] = {{1, "alpha", 1.5}, {2, "beta", 2.5}};
    write_records("build/083-records.bin", records, 2);
    Record back[4];
    ptrdiff_t n = read_records("build/083-records.bin", back, 4);
    printf("read %td records (sizeof(Record) = %zu)\n", n, sizeof(Record));
    return 0;
}
#endif
