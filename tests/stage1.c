#include "support.h"
#include <limits.h>

#if EXERCISE == 1
void run_tests(void) {
    CASE("-42, 0, 7");
    INT(-1, sign(-42));
    INT(0, sign(0));
    INT(1, sign(7));
    CASE("INT_MIN, INT_MAX, -1, 1");
    INT(-1, sign(INT_MIN));
    INT(1, sign(INT_MAX));
    INT(-1, sign(-1));
    INT(1, sign(1));
}
#elif EXERCISE == 2
void run_tests(void) {
    CASE("1, 2, 3 and permutations");
    INT(3, max_of_three(1, 2, 3));
    INT(3, max_of_three(3, 1, 2));
    INT(3, max_of_three(2, 3, 1));
    CASE("9, 4, 7");
    INT(9, max_of_three(9, 4, 7));
    CASE("all negative: -5, -2, -9");
    INT(-2, max_of_three(-5, -2, -9));
    CASE("ties: 4, 4, 1 and 7, 7, 7");
    INT(4, max_of_three(4, 4, 1));
    INT(7, max_of_three(7, 7, 7));
    CASE("INT_MAX, INT_MIN, 0 (arithmetic tricks overflow here)");
    INT(INT_MAX, max_of_three(INT_MAX, INT_MIN, 0));
    INT(0, max_of_three(INT_MIN, 0, INT_MIN));
    INT(INT_MIN, max_of_three(INT_MIN, INT_MIN, INT_MIN));
}
#elif EXERCISE == 3
void run_tests(void) {
    CASE("ordinary leap years 1996, 2024");
    TRUE(is_leap_year(1996));
    TRUE(is_leap_year(2024));
    CASE("ordinary non-leap years 2023, 2001");
    FALSE(is_leap_year(2023));
    FALSE(is_leap_year(2001));
    CASE("century years 1900, 2100 are not leap years");
    FALSE(is_leap_year(1900));
    FALSE(is_leap_year(2100));
    CASE("400-year centuries 2000, 1600, 2400 are leap years");
    TRUE(is_leap_year(2000));
    TRUE(is_leap_year(1600));
    TRUE(is_leap_year(2400));
    CASE("year 0 and negative years follow the same rule");
    TRUE(is_leap_year(0));
    TRUE(is_leap_year(-4));
    FALSE(is_leap_year(-100));
    TRUE(is_leap_year(-400));
}
#elif EXERCISE == 4
void run_tests(void) {
    CASE("48, 18 (both orders)");
    INT(6, gcd(48, 18));
    INT(6, gcd(18, 48));
    CASE("coprime 17, 5 and equal 12, 12");
    INT(1, gcd(17, 5));
    INT(12, gcd(12, 12));
    CASE("zeros: (0, 9), (9, 0), (0, 0)");
    INT(9, gcd(0, 9));
    INT(9, gcd(9, 0));
    INT(0, gcd(0, 0));
    CASE("negatives must give a non-negative result");
    INT(6, gcd(-12, 18));
    INT(6, gcd(12, -18));
    INT(6, gcd(-12, -18));
    INT(7, gcd(0, -7));
    CASE("INT_MAX with itself and with 1");
    INT(INT_MAX, gcd(INT_MAX, INT_MAX));
    INT(1, gcd(INT_MAX, 1));
}
#elif EXERCISE == 5
void run_tests(void) {
    CASE("0 and 1 are not prime");
    FALSE(is_prime(0));
    FALSE(is_prime(1));
    CASE("small primes 2, 3, 5, 7, 97");
    TRUE(is_prime(2));
    TRUE(is_prime(3));
    TRUE(is_prime(5));
    TRUE(is_prime(7));
    TRUE(is_prime(97));
    CASE("small composites 4, 9, 91 (7*13), 100");
    FALSE(is_prime(4));
    FALSE(is_prime(9));
    FALSE(is_prime(91));
    FALSE(is_prime(100));
    CASE("perfect square of a prime: 49, 121 (loop bound must be inclusive)");
    FALSE(is_prime(49));
    FALSE(is_prime(121));
    CASE("4294967291 = largest 32-bit prime (must be O(sqrt n))");
    TRUE(is_prime(4294967291u));
    CASE("4294967295 = 3*5*17*257*65537, and 4294967293 = 9241*464773");
    FALSE(is_prime(4294967295u));
    FALSE(is_prime(4294967293u));
}
#elif EXERCISE == 6
void run_tests(void) {
    CASE("0");
    INT(0, digit_sum(0));
    CASE("single digits 7 and -7");
    INT(7, digit_sum(7));
    INT(7, digit_sum(-7));
    CASE("1234 and 1000");
    INT(10, digit_sum(1234));
    INT(1, digit_sum(1000));
    CASE("negative: -123 (loop must not stop on value > 0)");
    INT(6, digit_sum(-123));
    CASE("INT_MAX = 2147483647");
    INT(46, digit_sum(INT_MAX));
    CASE("INT_MIN = -2147483648 (negating it is UB)");
    INT(47, digit_sum(INT_MIN));
}
#elif EXERCISE == 7
void run_tests(void) {
    CASE("base cases 0, 1, 2");
    UINT(0, fibonacci(0));
    UINT(1, fibonacci(1));
    UINT(1, fibonacci(2));
    CASE("10 and 20");
    UINT(55, fibonacci(10));
    UINT(6765, fibonacci(20));
    CASE("47 and 48 (overflow a 32-bit accumulator)");
    UINT(2971215073ull, fibonacci(47));
    UINT(4807526976ull, fibonacci(48));
    CASE("50");
    UINT(12586269025ull, fibonacci(50));
    CASE("92 and 93 (largest that fits in uint64_t)");
    UINT(7540113804746346429ull, fibonacci(92));
    UINT(12200160415121876738ull, fibonacci(93));
}
#elif EXERCISE == 8
void run_tests(void) {
    CASE("small sums never overflow");
    FALSE(add_overflows(1, 2));
    FALSE(add_overflows(-1, -2));
    FALSE(add_overflows(0, 0));
    CASE("INT_MAX + 1 and 1 + INT_MAX");
    TRUE(add_overflows(INT_MAX, 1));
    TRUE(add_overflows(1, INT_MAX));
    CASE("INT_MIN + -1 and -1 + INT_MIN");
    TRUE(add_overflows(INT_MIN, -1));
    TRUE(add_overflows(-1, INT_MIN));
    CASE("exactly at the limits is fine");
    FALSE(add_overflows(INT_MAX, 0));
    FALSE(add_overflows(INT_MIN, 0));
    FALSE(add_overflows(INT_MAX - 1, 1));
    FALSE(add_overflows(INT_MIN + 1, -1));
    CASE("opposite signs never overflow");
    FALSE(add_overflows(INT_MAX, INT_MIN));
    FALSE(add_overflows(INT_MIN, INT_MAX));
    FALSE(add_overflows(INT_MAX, -5));
    CASE("same-sign extremes");
    TRUE(add_overflows(INT_MAX, INT_MAX));
    TRUE(add_overflows(INT_MIN, INT_MIN));
    TRUE(add_overflows(INT_MAX / 2 + 1, INT_MAX / 2 + 1));
}
#elif EXERCISE == 9
void run_tests(void) {
    CASE("{1, 2, 3, 4}");
    {
        int values[] = {1, 2, 3, 4};
        DOUBLE_NEAR(2.5, average(values, 4), 1e-9);
    }
    CASE("{1, 2} (integer division would give 1)");
    {
        int values[] = {1, 2};
        DOUBLE_NEAR(1.5, average(values, 2), 1e-9);
    }
    CASE("single negative {-3}");
    {
        int values[] = {-3};
        DOUBLE_NEAR(-3.0, average(values, 1), 1e-9);
    }
    CASE("count 0 with NULL and with a real pointer");
    {
        int values[] = {42};
        DOUBLE_NEAR(0.0, average(NULL, 0), 1e-9);
        DOUBLE_NEAR(0.0, average(values, 0), 1e-9);
    }
    CASE("{INT_MAX, INT_MAX, INT_MAX} (int accumulator overflows)");
    {
        int values[] = {INT_MAX, INT_MAX, INT_MAX};
        DOUBLE_NEAR(2147483647.0, average(values, 3), 1e-9);
    }
    CASE("{INT_MIN, INT_MAX, INT_MIN, INT_MIN}");
    {
        int values[] = {INT_MIN, INT_MAX, INT_MIN, INT_MIN};
        DOUBLE_NEAR(-1073741824.25, average(values, 4), 1e-6);
    }
}
#elif EXERCISE == 10
void run_tests(void) {
    CASE("1 needs 0 steps");
    INT(0, collatz_steps(1));
    CASE("0 never reaches 1");
    INT(-1, collatz_steps(0));
    CASE("2, 3, 6");
    INT(1, collatz_steps(2));
    INT(7, collatz_steps(3));
    INT(8, collatz_steps(6));
    CASE("27 (peaks at 9232) and 97");
    INT(111, collatz_steps(27));
    INT(118, collatz_steps(97));
    CASE("159487 (peak above UINT32_MAX)");
    INT(183, collatz_steps(159487));
    CASE("1 << 40 and 1 << 63 (pure halvings; 32-bit arithmetic fails)");
    INT(40, collatz_steps((uint64_t)1 << 40));
    INT(63, collatz_steps((uint64_t)1 << 63));
}
#endif
