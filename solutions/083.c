#include "exercises.h"
#include "lib.h"
#include <stdio.h>

int write_records(const char *path, const Record *records, size_t count) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    size_t written = count ? fwrite(records, sizeof *records, count, f) : 0;
    int status = written == count ? 0 : -1;
    if (fclose(f) != 0) status = -1;
    return status;
}

ptrdiff_t read_records(const char *path, Record *out, size_t capacity) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    /* fread returns whole elements only; a trailing partial record is dropped. */
    size_t read = capacity ? fread(out, sizeof *out, capacity, f) : 0;
    fclose(f);
    return (ptrdiff_t)read;
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
