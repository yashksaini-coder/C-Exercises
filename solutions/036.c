#include "exercises.h"
#include "lib.h"

const char *day_name(Day day) {
    static const char *const names[DAY_COUNT] = {"Monday",   "Tuesday", "Wednesday", "Thursday",
                                                 "Friday",   "Saturday", "Sunday"};
    /* Casting to unsigned turns negative values into huge ones, so one
     * comparison rejects both negative and too-large days. */
    if ((unsigned)day >= DAY_COUNT) return "?";
    return names[day];
}

Day next_day(Day day) { return (Day)((day + 1) % DAY_COUNT); }

#ifndef EXERCISE_TEST
int main(void) {
    for (Day d = MONDAY; d < DAY_COUNT; d = (Day)(d + 1))
        printf("%s -> %s\n", day_name(d), day_name(next_day(d)));
    return 0;
}
#endif
