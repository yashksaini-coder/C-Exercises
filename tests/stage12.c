#include "support.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_12_keep_translation_unit_nonempty;

#if EXERCISE == 108
void run_tests(void) {
    size_t i = 77, j = 77;
    CASE("{2,7,11,15} target 9 -> 0,1");
    TRUE(two_sum((int[]){2, 7, 11, 15}, 4, 9, &i, &j));
    UINT(0, i);
    UINT(1, j);
    CASE("{3,2,4} target 6 -> 1,2 (not the same element twice)");
    TRUE(two_sum((int[]){3, 2, 4}, 3, 6, &i, &j));
    UINT(1, i);
    UINT(2, j);
    CASE("{3,3} target 6 -> 0,1; {3} target 6 -> false");
    TRUE(two_sum((int[]){3, 3}, 2, 6, &i, &j));
    UINT(0, i);
    UINT(1, j);
    i = j = 77;
    FALSE(two_sum((int[]){3}, 1, 6, &i, &j));
    UINT(77, i);
    UINT(77, j);
    CASE("no solution, count 0");
    FALSE(two_sum((int[]){1, 2, 3}, 3, 7, &i, &j));
    FALSE(two_sum(NULL, 0, 0, &i, &j));
    CASE("smallest i, then smallest j among several pairs: {1,4,2,3,0,5} target 5");
    TRUE(two_sum((int[]){1, 4, 2, 3, 0, 5}, 6, 5, &i, &j));
    UINT(0, i);
    UINT(1, j);
    CASE("negatives and overflow: {INT_MAX, 1} target INT_MIN is false; {-2, INT_MIN+2} target INT_MIN");
    FALSE(two_sum((int[]){INT_MAX, 1}, 2, INT_MIN, &i, &j));
    TRUE(two_sum((int[]){-2, INT_MIN + 2}, 2, INT_MIN, &i, &j));
    UINT(0, i);
    UINT(1, j);
}
#elif EXERCISE == 109
void run_tests(void) {
    CASE("simple balanced strings");
    TRUE(balanced_brackets("()"));
    TRUE(balanced_brackets("([]{})"));
    TRUE(balanced_brackets("{[()()]}"));
    TRUE(balanced_brackets("{ a[0] = (b + c); }"));
    CASE("empty and no brackets at all");
    TRUE(balanced_brackets(""));
    TRUE(balanced_brackets("plain text"));
    CASE("wrong order ([)] and mismatched types");
    FALSE(balanced_brackets("([)]"));
    FALSE(balanced_brackets("(]"));
    FALSE(balanced_brackets("{(})"));
    CASE("leftover openers and a closer with nothing open");
    FALSE(balanced_brackets("(("));
    FALSE(balanced_brackets("([]"));
    FALSE(balanced_brackets(")("));
    FALSE(balanced_brackets("())"));
    FALSE(balanced_brackets("]"));
    CASE("depth bound: 1024 nested is fine, 1025 is rejected");
    char deep[2100];
    memset(deep, '(', 1024);
    memset(deep + 1024, ')', 1024);
    deep[2048] = '\0';
    TRUE(balanced_brackets(deep));
    memset(deep, '(', 1025);
    memset(deep + 1025, ')', 1025);
    deep[2050] = '\0';
    FALSE(balanced_brackets(deep));
}
#elif EXERCISE == 110
void run_tests(void) {
    char text[64];
    CASE("hello world foo");
    strcpy(text, "hello world foo");
    reverse_words(text);
    STRING("foo world hello", text);
    CASE("two words, single letters");
    strcpy(text, "a b");
    reverse_words(text);
    STRING("b a", text);
    CASE("one word and the empty string stay as they are");
    strcpy(text, "single");
    reverse_words(text);
    STRING("single", text);
    strcpy(text, "");
    reverse_words(text);
    STRING("", text);
    CASE("characters inside words keep their order");
    strcpy(text, "ab cd ef gh");
    reverse_words(text);
    STRING("gh ef cd ab", text);
    CASE("words of different lengths; applying twice restores the input");
    strcpy(text, "the quick brown fox jumps");
    reverse_words(text);
    STRING("jumps fox brown quick the", text);
    reverse_words(text);
    STRING("the quick brown fox jumps", text);
    CASE("nothing written past the terminator");
    memset(text, 'Z', sizeof text);
    memcpy(text, "x y\0", 4);
    reverse_words(text);
    STRING("y x", text);
    INT('Z', text[4]);
}
#elif EXERCISE == 111
void run_tests(void) {
    char out[16];
    CASE("flower, flow, flight -> fl");
    const char *a[] = {"flower", "flow", "flight"};
    memset(out, 'X', sizeof out);
    UINT(2, longest_common_prefix(a, 3, out, sizeof out));
    STRING("fl", out);
    CASE("dog, racecar, car -> nothing");
    const char *b[] = {"dog", "racecar", "car"};
    UINT(0, longest_common_prefix(b, 3, out, sizeof out));
    STRING("", out);
    CASE("single string and identical strings");
    const char *c[] = {"interview"};
    UINT(9, longest_common_prefix(c, 1, out, sizeof out));
    STRING("interview", out);
    const char *d[] = {"abc", "abc", "abc"};
    UINT(3, longest_common_prefix(d, 3, out, sizeof out));
    STRING("abc", out);
    CASE("one string is a prefix of the others; an empty string kills it");
    const char *e[] = {"abcdef", "abc", "abcd"};
    UINT(3, longest_common_prefix(e, 3, out, sizeof out));
    STRING("abc", out);
    const char *f[] = {"abc", "", "abd"};
    UINT(0, longest_common_prefix(f, 3, out, sizeof out));
    STRING("", out);
    CASE("count 0 -> 0 and empty out");
    memset(out, 'X', sizeof out);
    UINT(0, longest_common_prefix(NULL, 0, out, sizeof out));
    STRING("", out);
    CASE("truncation: capacity 3 holds \"ab\" but returns the full length 3; capacity 0 writes nothing");
    const char *g[] = {"abcdef", "abcxyz"};
    memset(out, 'X', sizeof out);
    UINT(3, longest_common_prefix(g, 2, out, 3));
    STRING("ab", out);
    INT('X', out[3]);
    memset(out, 'X', sizeof out);
    UINT(3, longest_common_prefix(g, 2, out, 0));
    INT('X', out[0]);
    CASE("case-sensitive: Abc vs abc");
    const char *h[] = {"Abc", "abc"};
    UINT(0, longest_common_prefix(h, 2, out, sizeof out));
}
#elif EXERCISE == 112
void run_tests(void) {
    int out[16];
    CASE("{1,3,5} + {2,4,6}");
    merge_sorted_arrays((int[]){1, 3, 5}, 3, (int[]){2, 4, 6}, 3, out);
    ARRAY(((int[]){1, 2, 3, 4, 5, 6}), out, 6);
    CASE("one side empty, both sides empty");
    merge_sorted_arrays((int[]){1, 2, 3}, 3, NULL, 0, out);
    ARRAY(((int[]){1, 2, 3}), out, 3);
    merge_sorted_arrays(NULL, 0, (int[]){7, 8}, 2, out);
    ARRAY(((int[]){7, 8}), out, 2);
    out[0] = 99;
    merge_sorted_arrays(NULL, 0, NULL, 0, out);
    INT(99, out[0]);
    CASE("duplicates across both sides");
    merge_sorted_arrays((int[]){1, 1}, 2, (int[]){1}, 1, out);
    ARRAY(((int[]){1, 1, 1}), out, 3);
    merge_sorted_arrays((int[]){1, 2, 2, 5}, 4, (int[]){2, 3, 5, 5}, 4, out);
    ARRAY(((int[]){1, 2, 2, 2, 3, 5, 5, 5}), out, 8);
    CASE("one side exhausted early: tail copy");
    merge_sorted_arrays((int[]){1, 2}, 2, (int[]){3, 4, 5, 6}, 4, out);
    ARRAY(((int[]){1, 2, 3, 4, 5, 6}), out, 6);
    merge_sorted_arrays((int[]){10, 20, 30}, 3, (int[]){1}, 1, out);
    ARRAY(((int[]){1, 10, 20, 30}), out, 4);
    CASE("negatives and extremes");
    merge_sorted_arrays((int[]){-5, 10}, 2, (int[]){-10, 0, 20}, 3, out);
    ARRAY(((int[]){-10, -5, 0, 10, 20}), out, 5);
    merge_sorted_arrays((int[]){INT_MIN, INT_MAX}, 2, (int[]){0}, 1, out);
    ARRAY(((int[]){INT_MIN, 0, INT_MAX}), out, 3);
}
#elif EXERCISE == 113
void run_tests(void) {
    CASE("{3,2,1,5,6,4} k=2 -> 5; k=1 -> 6; k=6 -> 1");
    int a[] = {3, 2, 1, 5, 6, 4};
    INT(5, kth_largest(a, 6, 2));
    int a1[] = {3, 2, 1, 5, 6, 4};
    INT(6, kth_largest(a1, 6, 1));
    int a6[] = {3, 2, 1, 5, 6, 4};
    INT(1, kth_largest(a6, 6, 6));
    CASE("duplicates count separately: {3,2,3,1,2,4,5,5,6} k=4 -> 4; {3,3,1} k=2 -> 3");
    int b[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    INT(4, kth_largest(b, 9, 4));
    int c[] = {3, 3, 1};
    INT(3, kth_largest(c, 3, 2));
    CASE("single element; all equal (no infinite loop)");
    int d[] = {7};
    INT(7, kth_largest(d, 1, 1));
    int e[] = {5, 5, 5, 5};
    INT(5, kth_largest(e, 4, 3));
    INT(5, kth_largest(e, 4, 1));
    CASE("already sorted ascending and descending (pivot choice)");
    int f[1000], g[1000];
    for (int i = 0; i < 1000; ++i) {
        f[i] = i;
        g[i] = 999 - i;
    }
    INT(999, kth_largest(f, 1000, 1));
    INT(0, kth_largest(g, 1000, 1000));
    for (int i = 0; i < 1000; ++i) f[i] = i;
    INT(500, kth_largest(f, 1000, 500));
    CASE("INT_MIN and INT_MAX as values");
    int h[] = {INT_MIN, 0, INT_MAX, -1};
    INT(INT_MAX, kth_largest(h, 4, 1));
    int h2[] = {INT_MIN, 0, INT_MAX, -1};
    INT(INT_MIN, kth_largest(h2, 4, 4));
    CASE("k out of range -> INT_MIN");
    int k[] = {1, 2, 3};
    INT(INT_MIN, kth_largest(k, 3, 0));
    INT(INT_MIN, kth_largest(k, 3, 4));
    INT(INT_MIN, kth_largest(k, 0, 1));
    CASE("every k over a shuffled array matches sorted order");
    int base[] = {9, -3, 7, 7, 0, 12, -3, 5, 1, 8};
    int sorted[] = {12, 9, 8, 7, 7, 5, 1, 0, -3, -3};
    bool all_match = true;
    for (size_t kk = 1; kk <= 10; ++kk) {
        int copy[10];
        memcpy(copy, base, sizeof copy);
        if (kth_largest(copy, 10, kk) != sorted[kk - 1]) all_match = false;
    }
    TRUE(all_match);
}
#elif EXERCISE == 114
void run_tests(void) {
    char text[64];
    char *state = NULL;
    CASE("\"one two  three\" with \" \": no empty token for the double space");
    strcpy(text, "one two  three");
    STRING("one", next_token(text, " ", &state));
    STRING("two", next_token(NULL, " ", &state));
    STRING("three", next_token(NULL, " ", &state));
    IS_NULL(next_token(NULL, " ", &state));
    IS_NULL(next_token(NULL, " ", &state)); /* stays NULL once exhausted */
    CASE("leading and trailing delimiters are skipped: \",,a,,b,,\"");
    strcpy(text, ",,a,,b,,");
    state = NULL;
    STRING("a", next_token(text, ",", &state));
    STRING("b", next_token(NULL, ",", &state));
    IS_NULL(next_token(NULL, ",", &state));
    CASE("empty string and all-delimiters");
    strcpy(text, "");
    state = NULL;
    IS_NULL(next_token(text, " ", &state));
    strcpy(text, "   ");
    state = NULL;
    IS_NULL(next_token(text, " ", &state));
    CASE("delimiters change between calls: a=1;b=2");
    strcpy(text, "a=1;b=2");
    state = NULL;
    STRING("a", next_token(text, "=", &state));
    STRING("1", next_token(NULL, ";", &state));
    STRING("b", next_token(NULL, "=", &state));
    STRING("2", next_token(NULL, ";", &state));
    IS_NULL(next_token(NULL, ";", &state));
    CASE("tokens point into the original buffer and it is modified in place");
    strcpy(text, "x y");
    state = NULL;
    char *first = next_token(text, " ", &state);
    POINTER(text, first);
    INT('\0', text[1]);
    char *second = next_token(NULL, " ", &state);
    POINTER(text + 2, second);
    CASE("two tokenizers interleaved do not disturb each other (no static state)");
    char left[32] = "1 2 3", right[32] = "a b c";
    char *ls = NULL, *rs = NULL;
    STRING("1", next_token(left, " ", &ls));
    STRING("a", next_token(right, " ", &rs));
    STRING("2", next_token(NULL, " ", &ls));
    STRING("b", next_token(NULL, " ", &rs));
    STRING("3", next_token(NULL, " ", &ls));
    STRING("c", next_token(NULL, " ", &rs));
    IS_NULL(next_token(NULL, " ", &ls));
    IS_NULL(next_token(NULL, " ", &rs));
    CASE("multiple delimiter characters at once: \"k1=v1, k2=v2\" with \"=, \"");
    strcpy(text, "k1=v1, k2=v2");
    state = NULL;
    STRING("k1", next_token(text, "=, ", &state));
    STRING("v1", next_token(NULL, "=, ", &state));
    STRING("k2", next_token(NULL, "=, ", &state));
    STRING("v2", next_token(NULL, "=, ", &state));
    IS_NULL(next_token(NULL, "=, ", &state));
}
#elif EXERCISE == 115
void run_tests(void) {
    char out[64];
    CASE("123 + 877 = 1000 (carry creates a new digit)");
    memset(out, 'X', sizeof out);
    INT(4, bigint_add("123", "877", out, sizeof out));
    STRING("1000", out);
    CASE("99999999999999999999 + 1 (beyond uint64_t)");
    INT(21, bigint_add("99999999999999999999", "1", out, sizeof out));
    STRING("100000000000000000000", out);
    CASE("different lengths, no carry out: 999 + 1 = 1000, 1 + 999, 12345 + 55");
    INT(4, bigint_add("999", "1", out, sizeof out));
    STRING("1000", out);
    INT(4, bigint_add("1", "999", out, sizeof out));
    STRING("1000", out);
    INT(5, bigint_add("12345", "55", out, sizeof out));
    STRING("12400", out);
    CASE("zeros: 0 + 0 = 0; 0 + 5 = 5; leading zeros in input are dropped");
    INT(1, bigint_add("0", "0", out, sizeof out));
    STRING("0", out);
    INT(1, bigint_add("0", "5", out, sizeof out));
    STRING("5", out);
    INT(1, bigint_add("007", "1", out, sizeof out));
    STRING("8", out);
    INT(1, bigint_add("000", "0000", out, sizeof out));
    STRING("0", out);
    CASE("capacity: 5 + 5 = \"10\" needs 3 bytes; 2 is -1; exact fit without carry");
    INT(2, bigint_add("5", "5", out, 3));
    STRING("10", out);
    memcpy(out, "keep", 5);
    INT(-1, bigint_add("5", "5", out, 2));
    STRING("keep", out);
    INT(3, bigint_add("123", "321", out, 4)); /* 444: max_len + 1 bytes suffices */
    STRING("444", out);
    INT(-1, bigint_add("123", "321", out, 3));
    CASE("bad input: non-digit, empty, sign");
    INT(-1, bigint_add("12a", "1", out, sizeof out));
    INT(-1, bigint_add("", "1", out, sizeof out));
    INT(-1, bigint_add("1", "", out, sizeof out));
    INT(-1, bigint_add("-1", "1", out, sizeof out));
    INT(-1, bigint_add("1 2", "1", out, sizeof out));
    CASE("a long chain of carries: 40 nines + 1");
    char nines[41];
    memset(nines, '9', 40);
    nines[40] = '\0';
    INT(41, bigint_add(nines, "1", out, sizeof out));
    INT('1', out[0]);
    char expected[42];
    expected[0] = '1';
    memset(expected + 1, '0', 40);
    expected[41] = '\0';
    STRING(expected, out);
}
#elif EXERCISE == 116
void run_tests(void) {
    long result = -1;
    CASE("3 4 + 2 * = 14; 5 1 2 + 4 * + 3 - = 14; 2 3 4 * + = 14");
    TRUE(evaluate_rpn("3 4 + 2 *", &result));
    INT(14, result);
    TRUE(evaluate_rpn("5 1 2 + 4 * + 3 -", &result));
    INT(14, result);
    TRUE(evaluate_rpn("2 3 4 * +", &result));
    INT(14, result);
    CASE("operand order for - and /: 10 3 - = 7; 7 2 / = 3; -7 2 / = -3 (toward zero)");
    TRUE(evaluate_rpn("10 3 -", &result));
    INT(7, result);
    TRUE(evaluate_rpn("7 2 /", &result));
    INT(3, result);
    TRUE(evaluate_rpn("-7 2 /", &result));
    INT(-3, result);
    TRUE(evaluate_rpn("7 -2 /", &result));
    INT(-3, result);
    CASE("single number, negative numbers, extra spaces");
    TRUE(evaluate_rpn("42", &result));
    INT(42, result);
    TRUE(evaluate_rpn("-5", &result));
    INT(-5, result);
    TRUE(evaluate_rpn("  1   2  +  ", &result));
    INT(3, result);
    CASE("stack underflow and leftover operands");
    FALSE(evaluate_rpn("1 +", &result));
    FALSE(evaluate_rpn("+", &result));
    FALSE(evaluate_rpn("1 2", &result));
    FALSE(evaluate_rpn("1 2 + 3", &result));
    CASE("empty expression, malformed tokens, division by zero");
    FALSE(evaluate_rpn("", &result));
    FALSE(evaluate_rpn("   ", &result));
    FALSE(evaluate_rpn("3 x +", &result));
    FALSE(evaluate_rpn("3.5 1 +", &result));
    FALSE(evaluate_rpn("1 2 +-", &result));
    FALSE(evaluate_rpn("- 1 2", &result));
    FALSE(evaluate_rpn("1 0 /", &result));
    FALSE(evaluate_rpn("1 2 2 - /", &result));
    CASE("stack bound: 256 numbers then 255 '+' is fine; 257 numbers is rejected");
    char big[2048];
    size_t at = 0;
    for (int i = 0; i < 256; ++i) at += (size_t)sprintf(big + at, "1 ");
    for (int i = 0; i < 255; ++i) at += (size_t)sprintf(big + at, "+ ");
    big[at] = '\0';
    TRUE(evaluate_rpn(big, &result));
    INT(256, result);
    at = 0;
    for (int i = 0; i < 257; ++i) at += (size_t)sprintf(big + at, "1 ");
    for (int i = 0; i < 256; ++i) at += (size_t)sprintf(big + at, "+ ");
    big[at] = '\0';
    FALSE(evaluate_rpn(big, &result));
}
#endif
