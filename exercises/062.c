#include "exercises.h"
#include "lib.h"
#include <math.h>
#include <stdlib.h>

/* Derived types. `base` MUST be the first member so that a pointer to the
 * derived struct is also a valid pointer to its Shape. */
typedef struct {
    Shape base;
    double radius;
} Circle;

typedef struct {
    Shape base;
    double width, height;
} Rectangle;

/* TODO: write static circle_area/circle_perimeter/circle_name (and the
 * rectangle versions), then one `static const ShapeVTable` per class. */

/* Allocate a circle and return it as a Shape *; NULL on allocation failure. */
Shape *shape_new_circle(double radius) {
    (void)radius;
    /* TODO: implement. */
    return NULL;
}

/* Allocate a rectangle and return it as a Shape *; NULL on allocation failure. */
Shape *shape_new_rectangle(double width, double height) {
    (void)width;
    (void)height;
    /* TODO: implement. */
    return NULL;
}

/* Dispatch through the vtable. */
double shape_area(const Shape *shape) {
    (void)shape;
    /* TODO: implement. */
    return 0.0;
}

double shape_perimeter(const Shape *shape) {
    (void)shape;
    /* TODO: implement. */
    return 0.0;
}

const char *shape_name(const Shape *shape) {
    (void)shape;
    /* TODO: implement. */
    return NULL;
}

/* Free the object; NULL is allowed. */
void shape_free(Shape *shape) {
    (void)shape;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    Shape *shapes[2] = {shape_new_circle(1.0), shape_new_rectangle(3.0, 4.0)};
    for (size_t i = 0; i < 2; ++i) {
        if (!shapes[i]) continue;
        printf("%s: area %.3f perimeter %.3f\n", shape_name(shapes[i]), shape_area(shapes[i]),
               shape_perimeter(shapes[i]));
        shape_free(shapes[i]);
    }
    return 0;
}
#endif
