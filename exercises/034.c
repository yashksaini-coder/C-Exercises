#include "exercises.h"
#include "lib.h"

/* Area of the rectangle (width * height). */
double rect_area(Rect r) {
    (void)r;
    /* TODO: implement. */
    return 0.0;
}

/* True when p is inside r or on its edge (inclusive). */
bool rect_contains(Rect r, Point p) {
    (void)r;
    (void)p;
    /* TODO: implement. */
    return false;
}

#ifndef EXERCISE_TEST
int main(void) {
    Rect r = {{0.0, 0.0}, 10.0, 5.0};
    Point p = {5.0, 2.5};
    printf("area = %g, contains = %d\n", rect_area(r), rect_contains(r, p));
    return 0;
}
#endif
