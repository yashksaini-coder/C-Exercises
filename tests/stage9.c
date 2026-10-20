#include "support.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int stage_9_keep_translation_unit_nonempty;

#if EXERCISE == 81 || EXERCISE == 83 || EXERCISE == 88
/* Create a unique temporary file under build/ (created if missing). The
 * template buffer must be writable and ends up holding the real path. */
static FILE *make_temp(char *template_path) {
    mkdir("build", 0777); /* ignore failure: it usually already exists */
    strcpy(template_path, "build/testXXXXXX");
    int fd = mkstemp(template_path);
    if (fd < 0) return NULL;
    FILE *f = fdopen(fd, "wb");
    if (!f) close(fd);
    return f;
}

static bool __attribute__((unused)) write_temp(char *template_path, const void *data, size_t length) {
    FILE *f = make_temp(template_path);
    if (!f) return false;
    bool ok = fwrite(data, 1, length, f) == length;
    return fclose(f) == 0 && ok;
}

static long __attribute__((unused)) read_whole(const char *path, unsigned char *out, size_t capacity) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    size_t n = fread(out, 1, capacity, f);
    int extra = fgetc(f); /* make sure nothing is left over */
    fclose(f);
    return extra == EOF ? (long)n : -2;
}
#endif

#if EXERCISE == 80
void run_tests(void) {
    Options o = {-99, true, "unset"}; /* sentinel: a stub that writes nothing fails cleanly */

    CASE("-n 3 -v");
    char *a1[] = {"prog", "-n", "3", "-v", NULL};
    INT(0, parse_args(4, a1, &o));
    INT(3, o.count);
    TRUE(o.verbose);
    IS_NULL(o.output);

    CASE("no arguments gives the defaults");
    char *a2[] = {"prog", NULL};
    INT(0, parse_args(1, a2, &o));
    INT(1, o.count);
    FALSE(o.verbose);
    IS_NULL(o.output);

    CASE("-o out.txt -n 7, and -n -5 (negative value)");
    char *a3[] = {"prog", "-o", "out.txt", "-n", "7", NULL};
    INT(0, parse_args(5, a3, &o));
    INT(7, o.count);
    FALSE(o.verbose);
    STRING("out.txt", o.output);
    POINTER(a3[2], o.output); /* points into argv, not a copy */
    char *a4[] = {"prog", "-n", "-5", NULL};
    INT(0, parse_args(3, a4, &o));
    INT(-5, o.count);

    CASE("later flag wins: -n 1 -n 2 -v");
    char *a5[] = {"prog", "-n", "1", "-n", "2", "-v", NULL};
    INT(0, parse_args(6, a5, &o));
    INT(2, o.count);
    TRUE(o.verbose);

    CASE("unknown flag and stray word");
    char *a6[] = {"prog", "-x", NULL};
    INT(-1, parse_args(2, a6, &o));
    char *a7[] = {"prog", "-v", "extra", NULL};
    INT(-1, parse_args(3, a7, &o));

    CASE("missing value and malformed numbers");
    char *a8[] = {"prog", "-n", NULL};
    INT(-1, parse_args(2, a8, &o));
    char *a9[] = {"prog", "-v", "-o", NULL};
    INT(-1, parse_args(3, a9, &o));
    char *a10[] = {"prog", "-n", "12x", NULL};
    INT(-1, parse_args(3, a10, &o));
    char *a11[] = {"prog", "-n", "", NULL};
    INT(-1, parse_args(3, a11, &o));
}

#elif EXERCISE == 81
void run_tests(void) {
    char source[32], destination[32];
    unsigned char back[16384];

    CASE("7-byte text file");
    TRUE(write_temp(source, "hello!\n", 7));
    FILE *d = make_temp(destination);
    if (d) fclose(d);
    INT(0, copy_file(source, destination));
    INT(7, read_whole(destination, back, sizeof back));
    BYTES("hello!\n", back, 7);
    unlink(source);
    unlink(destination);

    CASE("10000 bytes with 0x00 and 0xFF (spans three buffers)");
    static unsigned char big[10000];
    for (size_t i = 0; i < sizeof big; ++i) big[i] = (unsigned char)(i * 7);
    big[0] = 0x00;
    big[4095] = 0xFF;
    big[4096] = 0x00;
    big[9999] = 0xFF;
    big[5000] = 0x1A; /* Ctrl-Z: text mode on Windows would stop here */
    TRUE(write_temp(source, big, sizeof big));
    d = make_temp(destination);
    if (d) fclose(d);
    INT(0, copy_file(source, destination));
    INT(10000, read_whole(destination, back, sizeof back));
    BYTES(big, back, sizeof big);
    unlink(source);
    unlink(destination);

    CASE("empty source gives an empty destination");
    TRUE(write_temp(source, "", 0));
    d = make_temp(destination);
    if (d) {
        fputs("stale content", d); /* must be truncated */
        fclose(d);
    }
    INT(0, copy_file(source, destination));
    INT(0, read_whole(destination, back, sizeof back));
    unlink(source);
    unlink(destination);

    CASE("missing source and unwritable destination");
    INT(-1, copy_file("build/definitely-missing-081", "build/081-should-not-exist"));
    unlink("build/081-should-not-exist");
    TRUE(write_temp(source, "x", 1));
    INT(-1, copy_file(source, "build/no-such-dir-081/out"));
    unlink(source);
}

#elif EXERCISE == 82
static size_t count_in(const char *data, size_t length) {
    FILE *f = tmpfile();
    if (!f) return (size_t)-1;
    fwrite(data, 1, length, f);
    rewind(f);
    size_t n = count_lines(f);
    fclose(f);
    return n;
}

void run_tests(void) {
    CASE("three terminated lines");
    UINT(3, count_in("a\nb\nc\n", 6));

    CASE("last line without newline");
    UINT(2, count_in("a\nb", 3));
    UINT(1, count_in("abc", 3));

    CASE("empty stream");
    UINT(0, count_in("", 0));

    CASE("only newlines");
    UINT(1, count_in("\n", 1));
    UINT(2, count_in("\n\n", 2));

    CASE("byte 0xFF must not be mistaken for EOF");
    UINT(1, count_in("x\xFFy\n", 4));
    UINT(3, count_in("\xFF\n\xFF\n\xFF", 5));

    CASE("counts from the current position, not the start");
    FILE *f = tmpfile();
    NOT_NULL(f);
    if (f) {
        fputs("skip\nme\nthen\ncount\n", f);
        rewind(f);
        fgetc(f);
        fgetc(f);
        fgetc(f);
        fgetc(f);
        fgetc(f); /* consumed "skip\n" */
        UINT(3, count_lines(f));
        fclose(f);
    }
}

#elif EXERCISE == 83
static bool records_equal(const Record *a, const Record *b) {
    return a->id == b->id && strncmp(a->tag, b->tag, sizeof a->tag) == 0 && a->weight == b->weight;
}

void run_tests(void) {
    char path[32];
    Record records[3] = {{1, "alpha", 1.5}, {-2, "b", -0.25}, {INT_MAX, "seven77", 1e300}};
    Record back[8];

    CASE("write 3, read with capacity 8");
    FILE *f = make_temp(path);
    if (f) fclose(f);
    INT(0, write_records(path, records, 3));
    memset(back, 0, sizeof back);
    INT(3, read_records(path, back, 8));
    TRUE(records_equal(&records[0], &back[0]));
    TRUE(records_equal(&records[1], &back[1]));
    TRUE(records_equal(&records[2], &back[2]));
    INT(0, back[3].id); /* nothing written past the count */

    CASE("file size is count * sizeof(Record)");
    unsigned char raw[256];
    INT((long)(3 * sizeof(Record)), read_whole(path, raw, sizeof raw));

    CASE("read with capacity 2 returns 2; capacity 0 returns 0");
    INT(2, read_records(path, back, 2));
    TRUE(records_equal(&records[1], &back[1]));
    INT(0, read_records(path, back, 0));

    CASE("write 0 records: empty file, read returns 0");
    INT(0, write_records(path, records, 0));
    INT(0, read_whole(path, raw, sizeof raw));
    INT(0, read_records(path, back, 8));
    unlink(path);

    CASE("trailing partial record is not counted");
    f = make_temp(path);
    if (f) {
        fwrite(&records[0], sizeof records[0], 1, f);
        fwrite(&records[1], 1, sizeof records[1] / 2, f); /* half a record */
        fclose(f);
    }
    INT(1, read_records(path, back, 8));
    TRUE(records_equal(&records[0], &back[0]));
    unlink(path);

    CASE("missing file: read -1, write to an impossible path -1");
    INT(-1, read_records("build/definitely-missing-083", back, 8));
    INT(-1, write_records("build/no-such-dir-083/records", records, 1));
}

#elif EXERCISE == 84
void run_tests(void) {
    CASE("sum_ints(3, 1, 2, 3)");
    INT(6, sum_ints(3, 1, 2, 3));

    CASE("count 0");
    INT(0, sum_ints(0));

    CASE("one negative argument");
    INT(-7, sum_ints(1, -7));

    CASE("INT_MAX + INT_MAX fits in long; INT_MIN + INT_MIN too");
    INT(2L * INT_MAX, sum_ints(2, INT_MAX, INT_MAX));
    INT(2L * INT_MIN, sum_ints(2, INT_MIN, INT_MIN));

    CASE("ten arguments");
    INT(55, sum_ints(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    INT(0, sum_ints(4, 10, -10, 5, -5));
}

#elif EXERCISE == 85
void run_tests(void) {
    char buffer[64];

    CASE("[INFO] x=5 with plenty of room");
    memset(buffer, 'Z', sizeof buffer);
    buffer[sizeof buffer - 1] = '\0';
    INT(10, log_message(buffer, sizeof buffer, "INFO", "x=%d", 5));
    STRING("[INFO] x=5", buffer);

    CASE("truncated to capacity 6: still reports the full length");
    memset(buffer, 'Z', sizeof buffer);
    buffer[sizeof buffer - 1] = '\0';
    INT(10, log_message(buffer, 6, "INFO", "x=%d", 5));
    STRING("[INFO", buffer);
    INT('Z', buffer[6]); /* nothing written past capacity */

    CASE("capacity exactly length + 1 fits; exactly length truncates one char");
    INT(10, log_message(buffer, 11, "INFO", "x=%d", 5));
    STRING("[INFO] x=5", buffer);
    INT(10, log_message(buffer, 10, "INFO", "x=%d", 5));
    STRING("[INFO] x=", buffer);

    CASE("capacity 0 with NULL buffer writes nothing");
    INT(10, log_message(NULL, 0, "INFO", "x=%d", 5));
    memset(buffer, 'Z', sizeof buffer);
    buffer[sizeof buffer - 1] = '\0';
    INT(10, log_message(buffer, 0, "INFO", "x=%d", 5));
    INT('Z', buffer[0]);

    CASE("prefix alone overflows the buffer (capacity 3)");
    memset(buffer, 'Z', sizeof buffer);
    buffer[sizeof buffer - 1] = '\0';
    INT(15, log_message(buffer, 3, "WARN", "%s!", "careful"));
    STRING("[W", buffer);
    INT('Z', buffer[3]);

    CASE("several conversions and an empty message");
    INT(15, log_message(buffer, sizeof buffer, "WARN", "%s!", "careful"));
    STRING("[WARN] careful!", buffer);
    INT(17, log_message(buffer, sizeof buffer, "DEBUG", "%d-%s-%.1f", 1, "two", 3.0));
    STRING("[DEBUG] 1-two-3.0", buffer);
    INT(8, log_message(buffer, sizeof buffer, "ERROR", "%s", ""));
    STRING("[ERROR] ", buffer);
}

#elif EXERCISE == 86
void run_tests(void) {
    CASE("MIN(tick(), 100) evaluates tick() twice");
    UINT(2, safe_min_calls());

    CASE("the counter is reset on every call");
    UINT(2, safe_min_calls());
    UINT(2, safe_min_calls());

    CASE("the macro itself, for the record");
    int i = 1, j = 5;
    int m = MIN(i++, j);
    INT(2, m); /* the comparison saw 1, the result branch re-ran i++ and yielded 2 */
    INT(3, i); /* i++ ran twice */
    INT(5, MAX(2, 5));
}

#elif EXERCISE == 87
void run_tests(void) {
    int q;

    CASE("7 / 2 and -7 / 2 (truncation toward zero)");
    q = 0;
    INT(ERR_OK, safe_divide(7, 2, &q));
    INT(3, q);
    INT(ERR_OK, safe_divide(-7, 2, &q));
    INT(-3, q);

    CASE("divide by zero leaves *out untouched");
    q = 123;
    INT(ERR_DIVIDE_BY_ZERO, safe_divide(1, 0, &q));
    INT(123, q);
    INT(ERR_DIVIDE_BY_ZERO, safe_divide(0, 0, &q));

    CASE("INT_MIN / -1 overflows; INT_MIN / 1 and INT_MAX / -1 do not");
    q = 123;
    INT(ERR_OVERFLOW, safe_divide(INT_MIN, -1, &q));
    INT(123, q);
    INT(ERR_OK, safe_divide(INT_MIN, 1, &q));
    INT(INT_MIN, q);
    INT(ERR_OK, safe_divide(INT_MAX, -1, &q));
    INT(-INT_MAX, q);
    INT(ERR_OK, safe_divide(INT_MIN, 2, &q));
    INT(INT_MIN / 2, q);

    CASE("NULL out is invalid, even when b is 0");
    INT(ERR_INVALID, safe_divide(1, 0, NULL));
    INT(ERR_INVALID, safe_divide(4, 2, NULL));

    CASE("error_string");
    STRING("ok", error_string(ERR_OK));
    STRING("divide by zero", error_string(ERR_DIVIDE_BY_ZERO));
    STRING("overflow", error_string(ERR_OVERFLOW));
    STRING("invalid", error_string(ERR_INVALID));
    STRING("invalid", error_string((Error)42));
    INT(0, ERR_OK); /* zero means success */
}

#elif EXERCISE == 88
static bool write_config(char *path, const char *text) {
    return write_temp(path, text, strlen(text));
}

void run_tests(void) {
    char path[32];
    Config c;

    CASE("name, value, numbers");
    TRUE(write_config(path, "name=demo\nvalue=hello world\nnumbers=1,2,3\n"));
    memset(&c, 0xAB, sizeof c);
    int r = load_config(path, &c);
    INT(0, r);
    if (r == 0) {
        STRING("demo", c.name);
        STRING("hello world", c.value);
        UINT(3, c.number_count);
        NOT_NULL(c.numbers);
        if (c.numbers && c.number_count == 3) {
            int expected[] = {1, 2, 3};
            ARRAY(expected, c.numbers, 3);
        }
        config_free(&c);
        IS_NULL(c.name);
        IS_NULL(c.numbers);
        UINT(0, c.number_count);
        config_free(&c); /* a second free must be safe */
    }
    unlink(path);

    CASE("keys in any order, blank lines, negative numbers, empty value");
    TRUE(write_config(path, "\nnumbers=-5,0,42\n\nvalue=\nname=x\n"));
    r = load_config(path, &c);
    INT(0, r);
    if (r == 0) {
        STRING("x", c.name);
        STRING("", c.value);
        UINT(3, c.number_count);
        if (c.numbers && c.number_count == 3) {
            int expected[] = {-5, 0, 42};
            ARRAY(expected, c.numbers, 3);
        }
        config_free(&c);
    }
    unlink(path);

    CASE("only numbers=42: other fields stay NULL");
    TRUE(write_config(path, "numbers=42\n"));
    r = load_config(path, &c);
    INT(0, r);
    if (r == 0) {
        IS_NULL(c.name);
        IS_NULL(c.value);
        UINT(1, c.number_count);
        if (c.numbers && c.number_count == 1) INT(42, c.numbers[0]);
        config_free(&c);
    }
    unlink(path);

    CASE("malformed number after name was allocated: -1, zeroed, no leak");
    TRUE(write_config(path, "name=x\nvalue=y\nnumbers=1,oops\n"));
    memset(&c, 0xAB, sizeof c);
    INT(-1, load_config(path, &c));
    IS_NULL(c.name);
    IS_NULL(c.value);
    IS_NULL(c.numbers);
    UINT(0, c.number_count);
    unlink(path);

    CASE("other malformed files: no '=', unknown key, duplicate key, empty or trailing-comma list");
    const char *bad[] = {"name=x\nvalue\n", "name=x\ncolor=red\n", "name=a\nname=b\n",
                         "numbers=\n", "numbers=1,2,\n", "numbers=1,,2\n", "numbers=1, 2\n"};
    int failures = 0;
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; ++i) {
        if (!write_config(path, bad[i])) continue;
        memset(&c, 0xAB, sizeof c);
        if (load_config(path, &c) != -1) {
            ++failures;
            config_free(&c); /* it "succeeded": release what it allocated */
        }
        if (c.name || c.value || c.numbers || c.number_count) ++failures;
        unlink(path);
    }
    INT(0, failures);

    CASE("missing file: -1 and zeroed");
    memset(&c, 0xAB, sizeof c);
    INT(-1, load_config("build/definitely-missing-088", &c));
    IS_NULL(c.name);
    IS_NULL(c.value);
    IS_NULL(c.numbers);
    UINT(0, c.number_count);
}
#endif
