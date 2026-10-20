#include "support.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static size_t checks, failures, cases;

void test_case(const char *input) {
    printf("\n  Case %zu | input: %s\n", ++cases, input);
    fflush(stdout);
}

static void quoted(const char *s) {
    if (!s) {
        fputs("NULL", stdout);
        return;
    }
    putchar('"');
    size_t i = 0;
    for (; i < 128 && s[i]; ++i) {
        unsigned char c = (unsigned char)s[i];
        switch (c) {
        case '\n': fputs("\\n", stdout); break;
        case '\t': fputs("\\t", stdout); break;
        case '\r': fputs("\\r", stdout); break;
        case '\\': fputs("\\\\", stdout); break;
        case '"': fputs("\\\"", stdout); break;
        default:
            if (c >= 32 && c <= 126) putchar(c);
            else printf("\\x%02X", (unsigned)c);
        }
    }
    putchar('"');
    if (i == 128) fputs("... (display limited to 128 bytes)", stdout);
}

void test_string_case(const char *input) {
    printf("\n  Case %zu | input: ", ++cases);
    quoted(input);
    putchar('\n');
    fflush(stdout);
}

static void failure(const char *expression, int line) {
    ++failures;
    printf("    FAIL line %d: %s\n", line, expression);
}

void expect_bool(bool expected, bool actual, const char *expression, int line) {
    ++checks;
    if (expected == actual) return;
    failure(expression, line);
    printf("      expected: %s\n      actual:   %s\n", expected ? "true" : "false",
           actual ? "true" : "false");
}

void expect_int(intmax_t expected, intmax_t actual, const char *expression, int line) {
    ++checks;
    if (expected == actual) return;
    failure(expression, line);
    printf("      expected: %" PRIdMAX "\n      actual:   %" PRIdMAX "\n", expected, actual);
}

void expect_uint(uintmax_t expected, uintmax_t actual, const char *expression, int line) {
    ++checks;
    if (expected == actual) return;
    failure(expression, line);
    printf("      expected: %" PRIuMAX " (0x%" PRIXMAX ")\n      actual:   %" PRIuMAX
           " (0x%" PRIXMAX ")\n",
           expected, expected, actual, actual);
}

void expect_double(double expected, double actual, double tolerance, const char *expression,
                   int line) {
    ++checks;
    if (fabs(expected - actual) <= tolerance) return;
    failure(expression, line);
    printf("      expected: %.9g\n      actual:   %.9g\n", expected, actual);
}

void expect_string(const char *expected, const char *actual, const char *expression, int line) {
    ++checks;
    if ((!expected && !actual) || (expected && actual && strcmp(expected, actual) == 0)) return;
    failure(expression, line);
    fputs("      expected: ", stdout);
    quoted(expected);
    fputs("\n      actual:   ", stdout);
    quoted(actual);
    putchar('\n');
}

static void byte_dump(const void *memory, size_t count) {
    if (!memory) {
        puts("NULL");
        return;
    }
    const unsigned char *bytes = memory;
    size_t shown = count < 64 ? count : 64;
    for (size_t i = 0; i < shown; ++i) printf("%02X%s", (unsigned)bytes[i], i + 1 == shown ? "" : " ");
    puts(count > shown ? " ... (display limited to 64 bytes)" : "");
}

void expect_bytes(const void *expected, const void *actual, size_t count, const char *expression,
                  int line) {
    ++checks;
    if (!count || (expected && actual && memcmp(expected, actual, count) == 0)) return;
    failure(expression, line);
    fputs("      expected: ", stdout);
    byte_dump(expected, count);
    fputs("      actual:   ", stdout);
    byte_dump(actual, count);
}

static void array_dump(const int *values, size_t count) {
    if (!values) {
        puts("NULL");
        return;
    }
    putchar('[');
    size_t shown = count < 32 ? count : 32;
    for (size_t i = 0; i < shown; ++i) printf("%s%d", i ? ", " : "", values[i]);
    puts(count > shown ? ", ...]" : "]");
}

void expect_array(const int *expected, const int *actual, size_t count, const char *expression,
                  int line) {
    ++checks;
    if (!count) return;
    size_t i = 0;
    if (expected && actual) {
        while (i < count && expected[i] == actual[i]) ++i;
        if (i == count) return;
    }
    failure(expression, line);
    fputs("      expected: ", stdout);
    array_dump(expected, count);
    fputs("      actual:   ", stdout);
    array_dump(actual, count);
    if (expected && actual)
        printf("      first differing index: %zu (expected %d, actual %d)\n", i, expected[i],
               actual[i]);
}

void expect_pointer(const void *expected, const void *actual, const char *expression, int line) {
    ++checks;
    if (expected == actual) return;
    failure(expression, line);
    printf("      expected: %p\n      actual:   %p\n", expected, actual);
}

void expect_not_null(const void *actual, const char *expression, int line) {
    ++checks;
    if (actual) return;
    failure(expression, line);
    puts("      expected: non-NULL pointer\n      actual:   NULL");
}

int test_summary(void) {
    printf("\n%s: %zu/%zu checks passed across %zu cases.\n", failures ? "FAIL" : "PASS",
           checks - failures, checks, cases);
    return failures ? 1 : 0;
}
