#include "support.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_3_keep_translation_unit_nonempty;

#if EXERCISE == 21
void run_tests(void) {
    STRING_CASE("");
    UINT(0, my_strlen(""));
    STRING_CASE("a");
    UINT(1, my_strlen("a"));
    STRING_CASE("hello");
    UINT(5, my_strlen("hello"));
    STRING_CASE("ab\0cd (embedded NUL stops the count)");
    UINT(2, my_strlen("ab\0cd"));
    CASE("1000 'x' bytes on the heap");
    {
        char *s = malloc(1001);
        NOT_NULL(s);
        memset(s, 'x', 1000);
        s[1000] = '\0';
        UINT(1000, my_strlen(s));
        free(s);
    }
}
#elif EXERCISE == 22
void run_tests(void) {
    char buffer[16];
    STRING_CASE("hello");
    memset(buffer, 'X', sizeof buffer);
    POINTER(buffer, my_strcpy(buffer, "hello"));
    STRING("hello", buffer);
    INT('X', buffer[6]); /* nothing beyond the NUL is touched */
    STRING_CASE("");
    memset(buffer, 'X', sizeof buffer);
    POINTER(buffer, my_strcpy(buffer, ""));
    STRING("", buffer);
    STRING_CASE("a into a 2-byte buffer");
    {
        char tiny[2] = {'X', 'X'};
        POINTER(tiny, my_strcpy(tiny, "a"));
        STRING("a", tiny);
    }
    STRING_CASE("exact fit: 15 chars into a 16-byte buffer");
    memset(buffer, 'X', sizeof buffer);
    my_strcpy(buffer, "123456789012345");
    STRING("123456789012345", buffer);
    CASE("source on the heap, copied into a heap destination");
    {
        char *source = malloc(6);
        char *destination = malloc(6);
        NOT_NULL(source);
        NOT_NULL(destination);
        memcpy(source, "abcde", 6);
        memset(destination, 'X', 6);
        STRING("abcde", my_strcpy(destination, source));
        free(source);
        free(destination);
    }
}
#elif EXERCISE == 23
static int sign_of(int r) { return (r > 0) - (r < 0); }

void run_tests(void) {
    STRING_CASE("\"abc\" vs \"abc\"");
    INT(0, sign_of(my_strcmp("abc", "abc")));
    STRING_CASE("\"\" vs \"\"");
    INT(0, sign_of(my_strcmp("", "")));
    STRING_CASE("\"abc\" vs \"abd\" and reverse");
    INT(-1, sign_of(my_strcmp("abc", "abd")));
    INT(1, sign_of(my_strcmp("abd", "abc")));
    STRING_CASE("\"b\" vs \"a\"");
    INT(1, sign_of(my_strcmp("b", "a")));
    STRING_CASE("prefix: \"ab\" vs \"abc\" and \"\" vs \"a\"");
    INT(-1, sign_of(my_strcmp("ab", "abc")));
    INT(1, sign_of(my_strcmp("abc", "ab")));
    INT(-1, sign_of(my_strcmp("", "a")));
    STRING_CASE("\"\\xE9\" vs \"a\": high byte must compare as unsigned");
    INT(1, sign_of(my_strcmp("\xE9", "a")));
    INT(-1, sign_of(my_strcmp("a", "\xE9")));
}
#elif EXERCISE == 24
void run_tests(void) {
    const char *s = "hello";
    STRING_CASE("hello, 'l' (first occurrence)");
    POINTER(s + 2, my_strchr(s, 'l'));
    STRING_CASE("hello, 'h' and 'o' (ends)");
    POINTER(s, my_strchr(s, 'h'));
    POINTER(s + 4, my_strchr(s, 'o'));
    STRING_CASE("hello, 'z' is absent");
    IS_NULL(my_strchr(s, 'z'));
    STRING_CASE("hello, '\\0' finds the terminator");
    POINTER(s + 5, my_strchr(s, '\0'));
    STRING_CASE("\"\": 'a' absent, '\\0' found at index 0");
    {
        const char *empty = "";
        IS_NULL(my_strchr(empty, 'a'));
        POINTER(empty, my_strchr(empty, '\0'));
    }
    CASE("writable heap string: result points into it");
    {
        char *heap = malloc(4);
        NOT_NULL(heap);
        memcpy(heap, "abc", 4);
        char *found = my_strchr(heap, 'c');
        POINTER(heap + 2, found);
        if (found) *found = 'C';
        STRING("abC", heap);
        free(heap);
    }
}
#elif EXERCISE == 25
void run_tests(void) {
    const char *s = "hello world";
    STRING_CASE("hello world, \"o w\"");
    POINTER(s + 4, my_strstr(s, "o w"));
    STRING_CASE("hello world, \"hello\" (at start) and \"world\" (at end)");
    POINTER(s, my_strstr(s, "hello"));
    POINTER(s + 6, my_strstr(s, "world"));
    STRING_CASE("hello, \"xyz\" absent and \"hello!\" too long");
    IS_NULL(my_strstr("hello", "xyz"));
    IS_NULL(my_strstr("hello", "hello!"));
    STRING_CASE("empty needle returns haystack, even for an empty haystack");
    POINTER(s, my_strstr(s, ""));
    {
        const char *empty = "";
        POINTER(empty, my_strstr(empty, ""));
        IS_NULL(my_strstr(empty, "a"));
    }
    STRING_CASE("\"aaa\", \"aaaa\" (must not read past the terminator)");
    {
        char *heap = malloc(4);
        NOT_NULL(heap);
        memcpy(heap, "aaa", 4);
        IS_NULL(my_strstr(heap, "aaaa"));
        free(heap);
    }
    STRING_CASE("\"abcabc\", \"cab\": partial match then restart");
    {
        const char *t = "abcabc";
        POINTER(t + 2, my_strstr(t, "cab"));
        POINTER(t, my_strstr(t, "abc"));         /* first of two matches */
        POINTER(t + 3, my_strstr(t + 1, "abc")); /* searching from index 1 */
    }
}
#elif EXERCISE == 26
void run_tests(void) {
    STRING_CASE("hello");
    {
        char s[] = "hello";
        reverse_string(s);
        STRING("olleh", s);
    }
    STRING_CASE("ab (even length)");
    {
        char s[] = "ab";
        reverse_string(s);
        STRING("ba", s);
    }
    STRING_CASE("a and \"\" (length - 1 underflows for the empty string)");
    {
        char one[] = "a";
        char empty[] = "";
        reverse_string(one);
        reverse_string(empty);
        STRING("a", one);
        STRING("", empty);
    }
    STRING_CASE("racecar is its own reverse");
    {
        char s[] = "racecar";
        reverse_string(s);
        STRING("racecar", s);
    }
    STRING_CASE("the NUL must stay at the end: \"abc\" in a 4-byte heap buffer");
    {
        char *s = malloc(4);
        NOT_NULL(s);
        memcpy(s, "abc", 4);
        reverse_string(s);
        STRING("cba", s);
        INT(0, s[3]);
        free(s);
    }
}
#elif EXERCISE == 27
void run_tests(void) {
    STRING_CASE("A man, a plan, a canal: Panama");
    TRUE(is_palindrome("A man, a plan, a canal: Panama"));
    STRING_CASE("racecar, RaceCar, hello");
    TRUE(is_palindrome("racecar"));
    TRUE(is_palindrome("RaceCar"));
    FALSE(is_palindrome("hello"));
    STRING_CASE("\"\", \",,,\" and \"a\" are palindromes");
    TRUE(is_palindrome(""));
    TRUE(is_palindrome(",,,"));
    TRUE(is_palindrome("a"));
    STRING_CASE("0P (digits are not skipped) and ab");
    FALSE(is_palindrome("0P"));
    FALSE(is_palindrome("ab"));
    STRING_CASE("\"No 'x' in Nixon\" and \"Was it a car or a cat I saw?\"");
    TRUE(is_palindrome("No 'x' in Nixon"));
    TRUE(is_palindrome("Was it a car or a cat I saw?"));
    STRING_CASE("\"ab\\xE9ba\": a high byte must not break <ctype.h>");
    TRUE(is_palindrome("ab\xE9" "ba"));
}
#elif EXERCISE == 28
void run_tests(void) {
    STRING_CASE("  hello  ");
    {
        char s[] = "  hello  ";
        POINTER(s, trim(s));
        STRING("hello", s);
    }
    STRING_CASE("\\t\\n x y \\r\\n (interior space kept)");
    {
        char s[] = "\t\n x y \r\n";
        POINTER(s, trim(s));
        STRING("x y", s);
    }
    STRING_CASE("hello (nothing to trim)");
    {
        char s[] = "hello";
        POINTER(s, trim(s));
        STRING("hello", s);
    }
    STRING_CASE("only leading, only trailing");
    {
        char a[] = "   lead";
        char b[] = "trail   ";
        STRING("lead", trim(a));
        STRING("trail", trim(b));
    }
    STRING_CASE("\"   \" and \"\" become \"\"");
    {
        char spaces[] = "   ";
        char empty[] = "";
        POINTER(spaces, trim(spaces));
        STRING("", spaces);
        POINTER(empty, trim(empty));
        STRING("", empty);
    }
    CASE("heap buffer: the returned pointer must be the one we free");
    {
        char *s = malloc(8);
        NOT_NULL(s);
        memcpy(s, "  ab  ", 7);
        char *result = trim(s);
        POINTER(s, result);
        STRING("ab", s);
        free(result);
    }
}
#elif EXERCISE == 29
void run_tests(void) {
    STRING_CASE("hello world");
    UINT(2, count_words("hello world"));
    STRING_CASE("  leading and   trailing   (counting spaces + 1 gives 11)");
    UINT(3, count_words("  leading and   trailing  "));
    STRING_CASE("one");
    UINT(1, count_words("one"));
    STRING_CASE("\"\" and \" \\t\\n \"");
    UINT(0, count_words(""));
    UINT(0, count_words(" \t\n "));
    STRING_CASE("a,b c.d (punctuation is part of a word)");
    UINT(2, count_words("a,b c.d"));
    STRING_CASE("tabs and newlines as separators: a\\tb\\nc\\r\\nd");
    UINT(4, count_words("a\tb\nc\r\nd"));
}
#elif EXERCISE == 30
void run_tests(void) {
    STRING_CASE("42, +42, -42");
    INT(42, my_atoi("42"));
    INT(42, my_atoi("+42"));
    INT(-42, my_atoi("-42"));
    STRING_CASE("leading whitespace, trailing junk: \"   -42abc\", \"4193 with words\"");
    INT(-42, my_atoi("   -42abc"));
    INT(4193, my_atoi("4193 with words"));
    STRING_CASE("no digits: \"\", \"abc\", \"+\", \"-\", \"words and 987\", \"+-12\"");
    INT(0, my_atoi(""));
    INT(0, my_atoi("abc"));
    INT(0, my_atoi("+"));
    INT(0, my_atoi("-"));
    INT(0, my_atoi("words and 987"));
    INT(0, my_atoi("+-12"));
    STRING_CASE("exact limits 2147483647 and -2147483648");
    INT(INT_MAX, my_atoi("2147483647"));
    INT(INT_MIN, my_atoi("-2147483648"));
    STRING_CASE("one past the limits clamps: 2147483648, -2147483649");
    INT(INT_MAX, my_atoi("2147483648"));
    INT(INT_MIN, my_atoi("-2147483649"));
    STRING_CASE("far past: 99999999999, -91283472332, 0000000000000000042");
    INT(INT_MAX, my_atoi("99999999999"));
    INT(INT_MIN, my_atoi("-91283472332"));
    INT(42, my_atoi("0000000000000000042"));
}
#elif EXERCISE == 31
void run_tests(void) {
    char buffer[16];
    CASE("0");
    memset(buffer, 'X', sizeof buffer);
    INT(1, int_to_string(0, buffer, sizeof buffer));
    STRING("0", buffer);
    CASE("42 and -7");
    INT(2, int_to_string(42, buffer, sizeof buffer));
    STRING("42", buffer);
    INT(2, int_to_string(-7, buffer, sizeof buffer));
    STRING("-7", buffer);
    CASE("INT_MAX and INT_MIN (do not negate INT_MIN)");
    INT(10, int_to_string(INT_MAX, buffer, sizeof buffer));
    STRING("2147483647", buffer);
    INT(11, int_to_string(INT_MIN, buffer, sizeof buffer));
    STRING("-2147483648", buffer);
    CASE("123 with capacity 3 fails, with capacity 4 fits exactly");
    {
        char *small = malloc(4);
        NOT_NULL(small);
        memset(small, 'X', 4);
        INT(-1, int_to_string(123, small, 3));
        INT(0, small[0]);
        INT('X', small[3]); /* nothing written beyond the stated capacity */
        INT(3, int_to_string(123, small, 4));
        STRING("123", small);
        free(small);
    }
    CASE("-123 needs 5 bytes: capacity 4 fails, 5 fits");
    {
        char *small = malloc(5);
        NOT_NULL(small);
        INT(-1, int_to_string(-123, small, 4));
        INT(0, small[0]);
        INT(4, int_to_string(-123, small, 5));
        STRING("-123", small);
        free(small);
    }
    CASE("capacity 0 returns -1 and writes nothing");
    memset(buffer, 'X', sizeof buffer);
    INT(-1, int_to_string(5, buffer, 0));
    INT('X', buffer[0]);
}
#elif EXERCISE == 32
void run_tests(void) {
    char buffer[32];
    STRING_CASE("aaabccdddd");
    INT(7, compress_runs("aaabccdddd", buffer, sizeof buffer));
    STRING("a3bc2d4", buffer);
    STRING_CASE("abc (no runs) and a");
    INT(3, compress_runs("abc", buffer, sizeof buffer));
    STRING("abc", buffer);
    INT(1, compress_runs("a", buffer, sizeof buffer));
    STRING("a", buffer);
    STRING_CASE("\"\" -> \"\" returns 0 (capacity 1 suffices)");
    memset(buffer, 'X', sizeof buffer);
    INT(0, compress_runs("", buffer, 1));
    STRING("", buffer);
    STRING_CASE("aaaaaaaaaaaa (12) -> a12 and 111 -> 13");
    INT(3, compress_runs("aaaaaaaaaaaa", buffer, sizeof buffer));
    STRING("a12", buffer);
    INT(2, compress_runs("111", buffer, sizeof buffer));
    STRING("13", buffer);
    STRING_CASE("aaabccdddd with capacity 7 fails, 8 fits exactly");
    {
        char *small = malloc(8);
        NOT_NULL(small);
        INT(-1, compress_runs("aaabccdddd", small, 7));
        INT(0, small[0]);
        INT(7, compress_runs("aaabccdddd", small, 8));
        STRING("a3bc2d4", small);
        free(small);
    }
    STRING_CASE("aaab with capacity 3 (must check before writing) and capacity 0");
    {
        char *small = malloc(3);
        NOT_NULL(small);
        INT(-1, compress_runs("aaab", small, 3));
        INT(0, small[0]);
        free(small);
        INT(-1, compress_runs("aaab", buffer, 0));
    }
}
#endif
