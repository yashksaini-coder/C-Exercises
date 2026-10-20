#include "exercises.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Free every field and zero the struct; safe on an already-zeroed Config. */
void config_free(Config *config) {
    (void)config;
    /* TODO: implement. */
}

/* Parse name=/value=/numbers= lines; 0 on success, -1 (with *out zeroed) on any failure. */
int load_config(const char *path, Config *out) {
    (void)path;
    (void)out;
    /* TODO: implement with a single `fail:` cleanup label. */
    return -1;
}

#ifndef EXERCISE_TEST
int main(void) {
    Config config;
    if (load_config("build/088-demo.cfg", &config) != 0) {
        puts("load_config failed (write build/088-demo.cfg to try it)");
        return 0;
    }
    printf("name=%s value=%s numbers:", config.name ? config.name : "(null)",
           config.value ? config.value : "(null)");
    for (size_t i = 0; i < config.number_count; ++i) printf(" %d", config.numbers[i]);
    putchar('\n');
    config_free(&config);
    return 0;
}
#endif
