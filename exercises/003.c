#include "exercises.h"
#include "lib.h"

/* Return true when year is a leap year under the Gregorian rule. */
bool is_leap_year(int year) {
    (void)year;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    int years[] = {1996, 1900, 2000, 2023};
    for (size_t i = 0; i < sizeof years / sizeof years[0]; ++i)
        printf("is_leap_year(%d) = %s\n", years[i], is_leap_year(years[i]) ? "true" : "false");
    return 0;
}
#endif
