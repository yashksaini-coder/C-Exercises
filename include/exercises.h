#ifndef C_PRACTICE_TRACK_EXERCISES_H
#define C_PRACTICE_TRACK_EXERCISES_H

/* The contract. Every exercise implements exactly the prototype declared
 * here; the tests call these names. Do not change signatures. */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* ---------- Stage 1: Foundations (001-010) ---------- */
int sign(int value);
int max_of_three(int a, int b, int c);
bool is_leap_year(int year);
int gcd(int a, int b);
bool is_prime(unsigned value);
int digit_sum(int value);
uint64_t fibonacci(unsigned n);
bool add_overflows(int a, int b);
double average(const int *values, size_t count);
int collatz_steps(uint64_t n);

/* ---------- Stage 2: Pointers and arrays (011-020) ---------- */
void swap_int(int *a, int *b);
size_t array_max_index(const int *values, size_t count);
void array_reverse(int *values, size_t count);
void array_rotate_left(int *values, size_t count, size_t k);
ptrdiff_t find_index(const int *values, size_t count, int target);
ptrdiff_t pointer_distance(const int *first, const int *second);
void matrix_transpose(size_t n, int matrix[n][n]);
void apply_each(int *values, size_t count, int (*transform)(int));
size_t count_matching(const int *values, size_t count, bool (*predicate)(int));
size_t remove_duplicates_sorted(int *values, size_t count);

#endif
