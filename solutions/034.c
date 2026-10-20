#include "exercises.h"
#include "lib.h"

double rect_area(Rect r) { return r.width * r.height; }

bool rect_contains(Rect r, Point p) {
    return p.x >= r.origin.x && p.x <= r.origin.x + r.width && p.y >= r.origin.y &&
           p.y <= r.origin.y + r.height;
}

#ifndef EXERCISE_TEST
int main(void) {
    Rect r = {{0.0, 0.0}, 10.0, 5.0};
    Point p = {5.0, 2.5};
    printf("area = %g, contains = %d\n", rect_area(r), rect_contains(r, p));
    return 0;
}
#endif
