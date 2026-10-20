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

#endif
