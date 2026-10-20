#include "exercises.h"
#include "lib.h"

/* Static English name of the day, or "?" for an invalid value. */
const char *day_name(Day day) {
    (void)day;
    /* TODO: implement. */
    return "?";
}

/* The next day, wrapping SUNDAY -> MONDAY. */
Day next_day(Day day) {
    (void)day;
    /* TODO: implement. */
    return MONDAY;
}

#ifndef EXERCISE_TEST
int main(void) {
    for (Day d = MONDAY; d < DAY_COUNT; d = (Day)(d + 1))
        printf("%s -> %s\n", day_name(d), day_name(next_day(d)));
    return 0;
}
#endif
