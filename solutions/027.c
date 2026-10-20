#include "exercises.h"
#include "lib.h"
#include <ctype.h>

bool is_palindrome(const char *s) {
    size_t length = 0;
    while (s[length]) ++length;
    if (length < 2) return true;
    size_t left = 0, right = length - 1;
    while (left < right) {
        /* Cast to unsigned char: <ctype.h> is undefined for negative chars. */
        if (!isalnum((unsigned char)s[left])) {
            ++left;
            continue;
        }
        if (!isalnum((unsigned char)s[right])) {
            --right;
            continue;
        }
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) return false;
        ++left;
        --right;
    }
    return true;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *s = "A man, a plan, a canal: Panama";
    printf("is_palindrome(\"%s\") = %s\n", s, is_palindrome(s) ? "true" : "false");
    return 0;
}
#endif
