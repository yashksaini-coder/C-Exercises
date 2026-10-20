#include "exercises.h"
#include "lib.h"

/* Register handler+context; 0 on success, -1 if full or handler is NULL. */
int emitter_connect(Emitter *emitter, EventHandler handler, void *context) {
    (void)emitter;
    (void)handler;
    (void)context;
    /* TODO: implement. */
    return -1;
}

/* Call every handler in registration order with its own context. */
void emitter_emit(Emitter *emitter, int event) {
    (void)emitter;
    (void)event;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
static void print_event(void *context, int event) {
    printf("%s got event %d\n", (const char *)context, event);
}

int main(void) {
    Emitter e = {0};
    emitter_connect(&e, print_event, "first");
    emitter_connect(&e, print_event, "second");
    emitter_emit(&e, 42);
    return 0;
}
#endif
