#ifndef C_PRACTICE_TRACK_SUPPORT_H
#define C_PRACTICE_TRACK_SUPPORT_H

#include "exercises.h"
#include <inttypes.h>
#include <stdbool.h>

/* Every test file defines run_tests(). Inside it, open a case with CASE(...)
 * and then make checks with the macros below. A failing check prints the
 * expected and actual values plus the line number. */

void test_case(const char *input);
void test_string_case(const char *input);
void expect_bool(bool expected, bool actual, const char *expression, int line);
void expect_int(intmax_t expected, intmax_t actual, const char *expression, int line);
void expect_uint(uintmax_t expected, uintmax_t actual, const char *expression, int line);
void expect_double(double expected, double actual, double tolerance, const char *expression, int line);
void expect_string(const char *expected, const char *actual, const char *expression, int line);
void expect_bytes(const void *expected, const void *actual, size_t count, const char *expression, int line);
void expect_array(const int *expected, const int *actual, size_t count, const char *expression, int line);
void expect_pointer(const void *expected, const void *actual, const char *expression, int line);
void expect_not_null(const void *actual, const char *expression, int line);
int test_summary(void);
void run_tests(void);

#define CASE(input) test_case(input)
#define STRING_CASE(input) test_string_case(input)
#define BOOL(expected, actual) expect_bool((expected), (actual), #actual, __LINE__)
#define TRUE(actual) BOOL(true, actual)
#define FALSE(actual) BOOL(false, actual)
#define INT(expected, actual) expect_int((expected), (actual), #actual, __LINE__)
#define UINT(expected, actual) expect_uint((expected), (actual), #actual, __LINE__)
#define DOUBLE(expected, actual) expect_double((expected), (actual), 1e-9, #actual, __LINE__)
#define DOUBLE_NEAR(expected, actual, tolerance) expect_double((expected), (actual), (tolerance), #actual, __LINE__)
#define STRING(expected, actual) expect_string((expected), (actual), #actual, __LINE__)
#define BYTES(expected, actual, count) expect_bytes((expected), (actual), (count), #actual, __LINE__)
#define ARRAY(expected, actual, count) expect_array((expected), (actual), (count), #actual, __LINE__)
#define POINTER(expected, actual) expect_pointer((expected), (actual), #actual, __LINE__)
#define NOT_NULL(actual) expect_not_null((actual), #actual, __LINE__)
#define IS_NULL(actual) expect_pointer(NULL, (actual), #actual, __LINE__)

#endif
