#include "exercises.h"
#include "lib.h"

int emitter_connect(Emitter *emitter, EventHandler handler, void *context) {
    /* ARRAY_LENGTH comes from exercises.h: sizeof array / sizeof element. */
    if (!handler || emitter->count >= ARRAY_LENGTH(emitter->handlers)) return -1;
    emitter->handlers[emitter->count] = handler;
    emitter->contexts[emitter->count] = context;
    emitter->count++;
    return 0;
}

void emitter_emit(Emitter *emitter, int event) {
    for (size_t i = 0; i < emitter->count; ++i)
        emitter->handlers[i](emitter->contexts[i], event);
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
