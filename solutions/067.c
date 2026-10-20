#include "exercises.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

static const char *dog_speak(const Animal *self) {
    (void)self;
    return "Woof";
}

static const char *cat_speak(const Animal *self) {
    (void)self;
    return "Meow";
}

/* Shared constructor: the only difference between a dog and a cat here is
 * which function pointer gets stored. */
static Animal *animal_new(const char *name, const char *(*speak)(const Animal *)) {
    Animal *animal = malloc(sizeof *animal);
    if (!animal) return NULL;
    size_t length = strlen(name) + 1;
    char *copy = malloc(length);
    if (!copy) {
        free(animal); /* do not leak the half-built object */
        return NULL;
    }
    memcpy(copy, name, length);
    animal->speak = speak;
    animal->name = copy;
    return animal;
}

Animal *animal_new_dog(const char *name) { return animal_new(name, dog_speak); }
Animal *animal_new_cat(const char *name) { return animal_new(name, cat_speak); }

const char *animal_speak(const Animal *animal) { return animal->speak(animal); }

void animal_free(Animal *animal) {
    if (!animal) return;
    /* name was allocated by us, so casting away const to free it is correct. */
    free((char *)animal->name);
    free(animal);
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
