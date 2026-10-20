#include "exercises.h"
#include "lib.h"

bool is_leap_year(int year) {
    /* Divisible by 4, except centuries, except every fourth century. */
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    printf("is_leap_year(2000) = %s\n", is_leap_year(2000) ? "true" : "false");
    return 0;
}
#endif
