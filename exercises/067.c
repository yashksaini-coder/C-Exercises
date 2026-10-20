#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

/* TODO: write static dog_speak / cat_speak returning "Woof" / "Meow". */

/* Allocate a dog with a private copy of name; NULL on allocation failure. */
Animal *animal_new_dog(const char *name) {
    (void)name;
    /* TODO: implement. */
    return NULL;
}

/* Allocate a cat with a private copy of name; NULL on allocation failure. */
Animal *animal_new_cat(const char *name) {
    (void)name;
    /* TODO: implement. */
    return NULL;
}

/* Dispatch through the function pointer stored in the object. */
const char *animal_speak(const Animal *animal) {
    (void)animal;
    /* TODO: implement. */
    return NULL;
}

/* Free the name and the object; NULL is allowed. */
void animal_free(Animal *animal) {
    (void)animal;
    /* TODO: implement. */
}

#ifndef EXERCISE_TEST
int main(void) {
    Animal *pets[2] = {animal_new_dog("Rex"), animal_new_cat("Tom")};
    for (size_t i = 0; i < 2; ++i) {
        if (pets[i]) printf("%s says %s\n", pets[i]->name, animal_speak(pets[i]));
        animal_free(pets[i]);
    }
    return 0;
}
#endif
