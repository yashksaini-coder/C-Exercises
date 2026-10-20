#include "exercises.h"
#include "lib.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    Shape base; /* first member: &circle->base == (Shape *)circle */
    double radius;
} Circle;

typedef struct {
    Shape base;
    double width, height;
} Rectangle;

/* --- Circle methods --- */
static double circle_area(const Shape *self) {
    const Circle *c = (const Circle *)self;
    return M_PI * c->radius * c->radius;
}
static double circle_perimeter(const Shape *self) {
    const Circle *c = (const Circle *)self;
    return 2.0 * M_PI * c->radius;
}
static const char *circle_name(const Shape *self) {
    (void)self;
    return "circle";
}
static const ShapeVTable circle_vtable = {circle_area, circle_perimeter, circle_name};

/* --- Rectangle methods --- */
static double rectangle_area(const Shape *self) {
    const Rectangle *r = (const Rectangle *)self;
    return r->width * r->height;
}
static double rectangle_perimeter(const Shape *self) {
    const Rectangle *r = (const Rectangle *)self;
    return 2.0 * (r->width + r->height);
}
static const char *rectangle_name(const Shape *self) {
    (void)self;
    return "rectangle";
}
static const ShapeVTable rectangle_vtable = {rectangle_area, rectangle_perimeter, rectangle_name};

Shape *shape_new_circle(double radius) {
    Circle *c = malloc(sizeof *c);
    if (!c) return NULL;
    c->base.vtable = &circle_vtable;
    c->radius = radius;
    return &c->base;
}

Shape *shape_new_rectangle(double width, double height) {
    Rectangle *r = malloc(sizeof *r);
    if (!r) return NULL;
    r->base.vtable = &rectangle_vtable;
    r->width = width;
    r->height = height;
    return &r->base;
}

double shape_area(const Shape *shape) { return shape->vtable->area(shape); }
double shape_perimeter(const Shape *shape) { return shape->vtable->perimeter(shape); }
const char *shape_name(const Shape *shape) { return shape->vtable->name(shape); }

/* The base lives at offset 0 of one malloc block, so freeing the base pointer
 * frees the whole derived object. */
void shape_free(Shape *shape) { free(shape); }

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
