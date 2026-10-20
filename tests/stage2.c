#include "support.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_2_keep_translation_unit_nonempty;

#if EXERCISE == 11
void run_tests(void) {
    CASE("x = 1, y = 2");
    {
        int x = 1, y = 2;
        swap_int(&x, &y);
        INT(2, x);
        INT(1, y);
    }
    CASE("INT_MIN and INT_MAX");
    {
        int x = INT_MIN, y = INT_MAX;
        swap_int(&x, &y);
        INT(INT_MAX, x);
        INT(INT_MIN, y);
    }
    CASE("same pointer twice (XOR swap would zero it)");
    {
        int x = 5;
        swap_int(&x, &x);
        INT(5, x);
    }
    CASE("array elements v[0] and v[2] of {1, 2, 3}");
    {
        int v[] = {1, 2, 3};
        int expected[] = {3, 2, 1};
        swap_int(&v[0], &v[2]);
        ARRAY(expected, v, 3);
    }
}
#elif EXERCISE == 12
void run_tests(void) {
    CASE("{3, 9, 2, 9}: first occurrence of the max");
    {
        int v[] = {3, 9, 2, 9};
        UINT(1, array_max_index(v, 4));
    }
    CASE("{-5, -2, -9}: all negative (best initialised to 0 fails)");
    {
        int v[] = {-5, -2, -9};
        UINT(1, array_max_index(v, 3));
    }
    CASE("{7}: single element");
    {
        int v[] = {7};
        UINT(0, array_max_index(v, 1));
    }
    CASE("{-1, -1, -1}: all equal");
    {
        int v[] = {-1, -1, -1};
        UINT(0, array_max_index(v, 3));
    }
    CASE("max at the last index, {1, 2, 3, INT_MAX}");
    {
        int v[] = {1, 2, 3, INT_MAX};
        UINT(3, array_max_index(v, 4));
    }
    CASE("count 0 with NULL");
    UINT(0, array_max_index(NULL, 0));
}
#elif EXERCISE == 13
void run_tests(void) {
    CASE("{1, 2, 3, 4}: even length");
    {
        int v[] = {1, 2, 3, 4};
        int expected[] = {4, 3, 2, 1};
        array_reverse(v, 4);
        ARRAY(expected, v, 4);
    }
    CASE("{1, 2, 3}: odd length, middle stays");
    {
        int v[] = {1, 2, 3};
        int expected[] = {3, 2, 1};
        array_reverse(v, 3);
        ARRAY(expected, v, 3);
    }
    CASE("{7}: single element");
    {
        int v[] = {7};
        int expected[] = {7};
        array_reverse(v, 1);
        ARRAY(expected, v, 1);
    }
    CASE("count 0 with NULL (count - 1 would be SIZE_MAX)");
    array_reverse(NULL, 0);
    CASE("{INT_MIN, 0, INT_MAX, 0, 5, -5}: swapping each pair twice restores the input");
    {
        int v[] = {INT_MIN, 0, INT_MAX, 0, 5, -5};
        int expected[] = {-5, 5, 0, INT_MAX, 0, INT_MIN};
        array_reverse(v, 6);
        ARRAY(expected, v, 6);
    }
}
#elif EXERCISE == 14
void run_tests(void) {
    CASE("{1, 2, 3, 4, 5} by 2");
    {
        int v[] = {1, 2, 3, 4, 5};
        int expected[] = {3, 4, 5, 1, 2};
        array_rotate_left(v, 5, 2);
        ARRAY(expected, v, 5);
    }
    CASE("{1, 2, 3, 4, 5} by 7 (k >= count)");
    {
        int v[] = {1, 2, 3, 4, 5};
        int expected[] = {3, 4, 5, 1, 2};
        array_rotate_left(v, 5, 7);
        ARRAY(expected, v, 5);
    }
    CASE("{1, 2, 3} by 3 and by 0: unchanged");
    {
        int v[] = {1, 2, 3};
        int expected[] = {1, 2, 3};
        array_rotate_left(v, 3, 3);
        ARRAY(expected, v, 3);
        array_rotate_left(v, 3, 0);
        ARRAY(expected, v, 3);
    }
    CASE("{1, 2, 3, 4} by 1 and {1, 2, 3, 4} by 3");
    {
        int v[] = {1, 2, 3, 4};
        int expected[] = {2, 3, 4, 1};
        array_rotate_left(v, 4, 1);
        ARRAY(expected, v, 4);
        int w[] = {1, 2, 3, 4};
        int expected_w[] = {4, 1, 2, 3};
        array_rotate_left(w, 4, 3);
        ARRAY(expected_w, w, 4);
    }
    CASE("single element by 5, count 0 with NULL (k % 0 must not happen)");
    {
        int v[] = {9};
        int expected[] = {9};
        array_rotate_left(v, 1, 5);
        ARRAY(expected, v, 1);
        array_rotate_left(NULL, 0, 3);
    }
    CASE("1000 elements by 999 must finish quickly");
    {
        enum { N = 1000 };
        int *v = malloc(N * sizeof *v);
        int *expected = malloc(N * sizeof *expected);
        NOT_NULL(v);
        NOT_NULL(expected);
        for (int i = 0; i < N; ++i) v[i] = i;
        expected[0] = N - 1;
        for (int i = 1; i < N; ++i) expected[i] = i - 1;
        array_rotate_left(v, N, N - 1);
        ARRAY(expected, v, N);
        free(v);
        free(expected);
    }
}
#elif EXERCISE == 15
void run_tests(void) {
    int v[] = {4, 8, 15, 16, 23, 42};
    CASE("{4, 8, 15, 16, 23, 42} target 15");
    INT(2, find_index(v, 6, 15));
    CASE("first and last element");
    INT(0, find_index(v, 6, 4));
    INT(5, find_index(v, 6, 42));
    CASE("target 7 is absent");
    INT(-1, find_index(v, 6, 7));
    CASE("{5, 5, 5} target 5: first index");
    {
        int w[] = {5, 5, 5};
        INT(0, find_index(w, 3, 5));
    }
    CASE("count 0 with NULL, and count limits the scan");
    INT(-1, find_index(NULL, 0, 4));
    INT(-1, find_index(v, 2, 15));
    CASE("INT_MIN and INT_MAX as targets");
    {
        int w[] = {INT_MAX, 0, INT_MIN};
        INT(0, find_index(w, 3, INT_MAX));
        INT(2, find_index(w, 3, INT_MIN));
    }
}
#elif EXERCISE == 16
void run_tests(void) {
    int v[8] = {0};
    CASE("v, v + 5");
    INT(5, pointer_distance(v, v + 5));
    CASE("v + 5, v (negative)");
    INT(-5, pointer_distance(v + 5, v));
    CASE("same element");
    INT(0, pointer_distance(&v[3], &v[3]));
    CASE("v, v + 8 (one past the end)");
    INT(8, pointer_distance(v, v + 8));
    CASE("adjacent elements (byte distance would be sizeof(int))");
    INT(1, pointer_distance(&v[2], &v[3]));
    INT(-1, pointer_distance(&v[3], &v[2]));
}
#elif EXERCISE == 17
void run_tests(void) {
    CASE("2 x 2");
    {
        int m[2][2] = {{1, 2}, {3, 4}};
        int expected[] = {1, 3, 2, 4};
        matrix_transpose(2, m);
        ARRAY(expected, &m[0][0], 4);
    }
    CASE("3 x 3 (swapping every pair twice restores the input)");
    {
        int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        int expected[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
        matrix_transpose(3, m);
        ARRAY(expected, &m[0][0], 9);
    }
    CASE("1 x 1 and 0 x 0");
    {
        int m[1][1] = {{5}};
        int expected[] = {5};
        matrix_transpose(1, m);
        ARRAY(expected, &m[0][0], 1);
        matrix_transpose(0, NULL);
    }
    CASE("symmetric 3 x 3 is unchanged");
    {
        int m[3][3] = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};
        int expected[] = {1, 2, 3, 2, 4, 5, 3, 5, 6};
        matrix_transpose(3, m);
        ARRAY(expected, &m[0][0], 9);
    }
    CASE("4 x 4 from a flat heap block");
    {
        int *block = malloc(16 * sizeof *block);
        int *expected = malloc(16 * sizeof *expected);
        NOT_NULL(block);
        NOT_NULL(expected);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                block[i * 4 + j] = i * 10 + j;
                expected[i * 4 + j] = j * 10 + i;
            }
        matrix_transpose(4, (int (*)[4])block);
        ARRAY(expected, block, 16);
        free(block);
        free(expected);
    }
}
#elif EXERCISE == 18
static int square(int x) { return x * x; }
static int negate(int x) { return -x; }
static int identity(int x) { return x; }
static int call_count;
static int counting_increment(int x) {
    ++call_count;
    return x + 1;
}

void run_tests(void) {
    CASE("{1, 2, 3} with square");
    {
        int v[] = {1, 2, 3};
        int expected[] = {1, 4, 9};
        apply_each(v, 3, square);
        ARRAY(expected, v, 3);
    }
    CASE("{1, -2, 3} with negate");
    {
        int v[] = {1, -2, 3};
        int expected[] = {-1, 2, -3};
        apply_each(v, 3, negate);
        ARRAY(expected, v, 3);
    }
    CASE("{5} with identity");
    {
        int v[] = {5};
        int expected[] = {5};
        apply_each(v, 1, identity);
        ARRAY(expected, v, 1);
    }
    CASE("transform is called exactly once per element, and never for count 0");
    {
        int v[] = {10, 20, 30, 40};
        int expected[] = {11, 21, 31, 41};
        call_count = 0;
        apply_each(v, 4, counting_increment);
        ARRAY(expected, v, 4);
        INT(4, call_count);
        call_count = 0;
        apply_each(NULL, 0, counting_increment);
        INT(0, call_count);
    }
}
#elif EXERCISE == 19
static bool is_even(int x) { return x % 2 == 0; }
static bool is_negative(int x) { return x < 0; }
static bool always(int x) {
    (void)x;
    return true;
}
static int seen;
static bool counting_positive(int x) {
    ++seen;
    return x > 0;
}

void run_tests(void) {
    CASE("{1, 2, 3, 4, 5, 6} with is_even");
    {
        int v[] = {1, 2, 3, 4, 5, 6};
        UINT(3, count_matching(v, 6, is_even));
    }
    CASE("{-3, -1, 0, 2} with is_negative");
    {
        int v[] = {-3, -1, 0, 2};
        UINT(2, count_matching(v, 4, is_negative));
    }
    CASE("{1, 3, 5} with is_even: no matches");
    {
        int v[] = {1, 3, 5};
        UINT(0, count_matching(v, 3, is_even));
    }
    CASE("{INT_MIN, INT_MAX} with always: every element matches");
    {
        int v[] = {INT_MIN, INT_MAX};
        UINT(2, count_matching(v, 2, always));
    }
    CASE("predicate called once per element (no early break); count 0 never calls it");
    {
        int v[] = {1, -1, 2, -2, 3};
        seen = 0;
        UINT(3, count_matching(v, 5, counting_positive));
        INT(5, seen);
        seen = 0;
        UINT(0, count_matching(NULL, 0, counting_positive));
        INT(0, seen);
    }
}
#elif EXERCISE == 20
void run_tests(void) {
    CASE("{1, 1, 2, 3, 3, 3, 4}");
    {
        int v[] = {1, 1, 2, 3, 3, 3, 4};
        int expected[] = {1, 2, 3, 4};
        UINT(4, remove_duplicates_sorted(v, 7));
        ARRAY(expected, v, 4);
    }
    CASE("{2, 2, 2}: all the same");
    {
        int v[] = {2, 2, 2};
        int expected[] = {2};
        UINT(1, remove_duplicates_sorted(v, 3));
        ARRAY(expected, v, 1);
    }
    CASE("{1, 2, 3}: already distinct");
    {
        int v[] = {1, 2, 3};
        int expected[] = {1, 2, 3};
        UINT(3, remove_duplicates_sorted(v, 3));
        ARRAY(expected, v, 3);
    }
    CASE("count 0 with NULL and a single element");
    {
        int v[] = {9};
        int expected[] = {9};
        UINT(0, remove_duplicates_sorted(NULL, 0));
        UINT(1, remove_duplicates_sorted(v, 1));
        ARRAY(expected, v, 1);
    }
    CASE("{INT_MIN, INT_MIN, INT_MAX}");
    {
        int v[] = {INT_MIN, INT_MIN, INT_MAX};
        int expected[] = {INT_MIN, INT_MAX};
        UINT(2, remove_duplicates_sorted(v, 3));
        ARRAY(expected, v, 2);
    }
    CASE("{1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 5, 5}: long runs (compare with last written)");
    {
        int v[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 5, 5};
        int expected[] = {1, 2, 3, 4, 5};
        UINT(5, remove_duplicates_sorted(v, 12));
        ARRAY(expected, v, 5);
    }
}
#endif
