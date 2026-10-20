#include "exercises.h"
#include "lib.h"
#include <stddef.h>

/* Recover the Record that owns this weight member; NULL for NULL. */
Record *record_from_weight(double *weight_pointer) {
    (void)weight_pointer;
    /* TODO: implement with offsetof / CONTAINER_OF. */
    return NULL;
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
