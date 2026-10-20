#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

int compare_students(const void *a, const void *b) {
    const Student *x = a;
    const Student *y = b;
    /* Descending score: y before x. Compare, do not subtract (overflow). */
    if (x->score != y->score) return (y->score > x->score) - (y->score < x->score);
    return strcmp(x->name, y->name);
}

#ifndef EXERCISE_TEST
int main(void) {
    Student students[] = {{"cat", 70}, {"amy", 90}, {"bob", 90}, {"dan", 100}};
    size_t count = sizeof(students) / sizeof(students[0]);
    qsort(students, count, sizeof(Student), compare_students);
    for (size_t i = 0; i < count; ++i) printf("%s %d\n", students[i].name, students[i].score);
    return 0;
}
#endif
