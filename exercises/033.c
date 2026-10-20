#include "exercises.h"
#include "lib.h"
#include <math.h>

/* Euclidean distance between two points. */
double point_distance(Point a, Point b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return 0.0;
}

#ifndef EXERCISE_TEST
int main(void) {
    Point origin = {0.0, 0.0};
    Point p = {3.0, 4.0};
    printf("distance = %g\n", point_distance(origin, p));
    return 0;
}
#endif
