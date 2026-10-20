#include "exercises.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void config_free(Config *config) {
    free(config->name);
    free(config->value);
    free(config->numbers);
    *config = (Config){0};
}

static char *copy_string(const char *s) {
    size_t length = strlen(s) + 1;
    char *copy = malloc(length);
    if (copy) memcpy(copy, s, length);
    return copy;
}

/* Parse "1,2,3" into a fresh int array; returns NULL on any malformed item. */
static int *parse_numbers(const char *text, size_t *count) {
    if (*text == '\0') return NULL; /* list must be non-empty */
    size_t items = 1;
    for (const char *p = text; *p; ++p) items += *p == ',';
    int *numbers = malloc(items * sizeof *numbers);
    if (!numbers) return NULL;
    const char *p = text;
    for (size_t i = 0; i < items; ++i) {
        char *end;
        /* strtol silently skips leading whitespace, so "1, 2" would pass; refuse it. */
        if (!(*p == '-' || *p == '+' || (*p >= '0' && *p <= '9'))) {
            free(numbers);
            return NULL;
        }
        long value = strtol(p, &end, 10);
        if (end == p || (*end != ',' && *end != '\0')) { /* empty token or junk */
            free(numbers);
            return NULL;
        }
        numbers[i] = (int)value;
        p = *end == ',' ? end + 1 : end;
    }
    *count = items;
    return numbers;
}

int load_config(const char *path, Config *out) {
    int status = -1;
    FILE *f = NULL;
    bool seen_name = false, seen_value = false, seen_numbers = false;
    char line[256];

    *out = (Config){0}; /* all pointers NULL: config_free is now always safe */

    f = fopen(path, "r");
    if (!f) goto fail;

    while (fgets(line, sizeof line, f)) {
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') line[--length] = '\0';
        else if (!feof(f)) goto fail; /* line longer than the buffer */
        if (length == 0) continue;     /* blank line */

        char *equals = strchr(line, '=');
        if (!equals) goto fail;
        *equals = '\0';
        const char *key = line, *text = equals + 1;

        if (strcmp(key, "name") == 0) {
            if (seen_name) goto fail;
            seen_name = true;
            if (!(out->name = copy_string(text))) goto fail;
        } else if (strcmp(key, "value") == 0) {
            if (seen_value) goto fail;
            seen_value = true;
            if (!(out->value = copy_string(text))) goto fail;
        } else if (strcmp(key, "numbers") == 0) {
            if (seen_numbers) goto fail;
            seen_numbers = true;
            if (!(out->numbers = parse_numbers(text, &out->number_count))) goto fail;
        } else {
            goto fail; /* unknown key */
        }
    }
    if (ferror(f)) goto fail;

    status = 0;
    goto done;

fail:
    config_free(out); /* frees whichever fields were allocated, zeroes the rest */
done:
    if (f) fclose(f);
    return status;
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
