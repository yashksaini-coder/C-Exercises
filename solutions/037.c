#include "exercises.h"
#include "lib.h"
#include <stddef.h>

Record *record_from_weight(double *weight_pointer) {
    if (!weight_pointer) return NULL;
    return CONTAINER_OF(weight_pointer, Record, weight);
}

#ifndef EXERCISE_TEST
int main(void) {
    Record r = {7, "abc", 2.5};
    printf("offsetof(Record, weight) = %zu, sizeof(Record) = %zu\n", offsetof(Record, weight),
           sizeof(Record));
    Record *back = record_from_weight(&r.weight);
    printf("same record: %d\n", back == &r);
    return 0;
}
#endif
