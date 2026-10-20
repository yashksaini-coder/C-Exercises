#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* qsort order: score descending, then name ascending. */
int compare_students(const void *a, const void *b) {
    (void)a;
    (void)b;
    /* TODO: implement. */
    return 0;
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
