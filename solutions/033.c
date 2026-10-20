#include "exercises.h"
#include "lib.h"
#include <math.h>

double point_distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

#ifndef EXERCISE_TEST
int main(void) {
    Point origin = {0.0, 0.0};
    Point p = {3.0, 4.0};
    printf("distance = %g\n", point_distance(origin, p));
    return 0;
}
#endif
