#include "exercises.h"
#include "lib.h"
#include <ctype.h>

/* True when s is a palindrome ignoring case and non-alphanumerics. */
bool is_palindrome(const char *s) {
    (void)s;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    const char *s = "A man, a plan, a canal: Panama";
    printf("is_palindrome(\"%s\") = %s\n", s, is_palindrome(s) ? "true" : "false");
    return 0;
}
#endif
