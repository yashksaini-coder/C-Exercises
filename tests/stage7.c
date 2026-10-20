#include "support.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_7_keep_translation_unit_nonempty;

#if EXERCISE == 61
void run_tests(void) {
    CASE("counter_new(5) then get");
    Counter *c = counter_new(5);
    NOT_NULL(c);
    if (c) INT(5, counter_get(c));
    counter_free(c);

    CASE("start -2, increment three times");
    c = counter_new(-2);
    NOT_NULL(c);
    if (c) {
        counter_increment(c);
        counter_increment(c);
        counter_increment(c);
        INT(1, counter_get(c));
    }
    counter_free(c);

    CASE("two counters are independent");
    Counter *a = counter_new(0), *b = counter_new(100);
    NOT_NULL(a);
    NOT_NULL(b);
    if (a && b) {
        counter_increment(a);
        INT(1, counter_get(a));
        INT(100, counter_get(b));
    }
    counter_free(a);
    counter_free(b);

    CASE("counter_free(NULL) is a no-op");
    counter_free(NULL);
    TRUE(true);
}

#elif EXERCISE == 62
void run_tests(void) {
    const double pi = 3.14159265358979323846;

    CASE("circle radius 1");
    Shape *s = shape_new_circle(1.0);
    NOT_NULL(s);
    if (s) {
        STRING("circle", shape_name(s));
        DOUBLE_NEAR(pi, shape_area(s), 1e-9);
        DOUBLE_NEAR(2.0 * pi, shape_perimeter(s), 1e-9);
    }
    shape_free(s);

    CASE("rectangle 3 x 4");
    s = shape_new_rectangle(3.0, 4.0);
    NOT_NULL(s);
    if (s) {
        STRING("rectangle", shape_name(s));
        DOUBLE_NEAR(12.0, shape_area(s), 1e-9);
        DOUBLE_NEAR(14.0, shape_perimeter(s), 1e-9);
    }
    shape_free(s);

    CASE("circle radius 2.5 and radius 0");
    s = shape_new_circle(2.5);
    NOT_NULL(s);
    if (s) DOUBLE_NEAR(pi * 6.25, shape_area(s), 1e-9);
    shape_free(s);
    s = shape_new_circle(0.0);
    NOT_NULL(s);
    if (s) {
        DOUBLE_NEAR(0.0, shape_area(s), 1e-12);
        DOUBLE_NEAR(0.0, shape_perimeter(s), 1e-12);
    }
    shape_free(s);

    CASE("heterogeneous array dispatches per object");
    Shape *shapes[3] = {shape_new_rectangle(1.0, 1.0), shape_new_circle(1.0),
                        shape_new_rectangle(2.0, 0.5)};
    double total = 0.0;
    for (size_t i = 0; i < 3; ++i) {
        NOT_NULL(shapes[i]);
        if (shapes[i]) total += shape_area(shapes[i]);
    }
    DOUBLE_NEAR(1.0 + pi + 1.0, total, 1e-9);
    if (shapes[0] && shapes[1] && shapes[2]) {
        STRING("rectangle", shape_name(shapes[0]));
        STRING("circle", shape_name(shapes[1]));
        STRING("rectangle", shape_name(shapes[2]));
    }
    for (size_t i = 0; i < 3; ++i) shape_free(shapes[i]);

    CASE("shape_free(NULL) is a no-op");
    shape_free(NULL);
    TRUE(true);
}

#elif EXERCISE == 63
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
static int compare_doubles(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}
static int compare_cstrings(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

void run_tests(void) {
    CASE("ints {3, 9, 2, 9}: first maximum wins");
    int values[] = {3, 9, 2, 9};
    const int *max = generic_max(values, 4, sizeof values[0], compare_ints);
    NOT_NULL(max);
    if (max) {
        INT(9, *max);
        POINTER(&values[1], max);
    }

    CASE("doubles {-1.5, -0.5, -2.0}");
    double d[] = {-1.5, -0.5, -2.0};
    const double *dm = generic_max(d, 3, sizeof d[0], compare_doubles);
    POINTER(&d[1], dm);

    CASE("strings {pear, apple, zoo} with strcmp");
    const char *words[] = {"pear", "apple", "zoo"};
    const char *const *wm = generic_max(words, 3, sizeof words[0], compare_cstrings);
    POINTER(&words[2], wm);

    CASE("single element and INT_MIN/INT_MAX");
    int one[] = {-7};
    POINTER(&one[0], generic_max(one, 1, sizeof one[0], compare_ints));
    int extremes[] = {INT_MAX, INT_MIN, 0};
    POINTER(&extremes[0], generic_max(extremes, 3, sizeof extremes[0], compare_ints));

    CASE("count 0 returns NULL");
    IS_NULL(generic_max(values, 0, sizeof values[0], compare_ints));
}

#elif EXERCISE == 64
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
static int compare_doubles(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}
/* Score descending, then name ascending (the 035 ordering). */
static int compare_students_desc(const void *a, const void *b) {
    const Student *x = a, *y = b;
    if (x->score != y->score) return x->score < y->score ? 1 : -1;
    return strcmp(x->name, y->name);
}

void run_tests(void) {
    CASE("ints {5, 1, 4, 2, 3}");
    int values[] = {5, 1, 4, 2, 3};
    my_qsort(values, 5, sizeof values[0], compare_ints);
    int expected[] = {1, 2, 3, 4, 5};
    ARRAY(expected, values, 5);

    CASE("doubles {2.5, -1.0, 0.0}");
    double d[] = {2.5, -1.0, 0.0};
    my_qsort(d, 3, sizeof d[0], compare_doubles);
    DOUBLE(-1.0, d[0]);
    DOUBLE(0.0, d[1]);
    DOUBLE(2.5, d[2]);

    CASE("structs: Student by score desc then name");
    Student students[4] = {{"zed", 50}, {"amy", 90}, {"bob", 50}, {"cat", 70}};
    my_qsort(students, 4, sizeof students[0], compare_students_desc);
    STRING("amy", students[0].name);
    STRING("cat", students[1].name);
    STRING("bob", students[2].name);
    STRING("zed", students[3].name);
    INT(90, students[0].score);
    INT(50, students[3].score);

    CASE("duplicates, already sorted, INT_MIN/INT_MAX");
    int dup[] = {3, 3, 1, INT_MAX, INT_MIN, 3, 1};
    my_qsort(dup, 7, sizeof dup[0], compare_ints);
    int dup_expected[] = {INT_MIN, 1, 1, 3, 3, 3, INT_MAX};
    ARRAY(dup_expected, dup, 7);
    int sorted[] = {1, 2, 3, 4};
    my_qsort(sorted, 4, sizeof sorted[0], compare_ints);
    int sorted_expected[] = {1, 2, 3, 4};
    ARRAY(sorted_expected, sorted, 4);

    CASE("count 0 and count 1 are no-ops");
    int single[] = {42};
    my_qsort(single, 1, sizeof single[0], compare_ints);
    INT(42, single[0]);
    my_qsort(single, 0, sizeof single[0], compare_ints);
    INT(42, single[0]);

    CASE("200 pseudo-random ints (deterministic LCG)");
    int big[200];
    unsigned seed = 12345u;
    for (size_t i = 0; i < 200; ++i) {
        seed = seed * 1103515245u + 12345u;
        big[i] = (int)(seed >> 8) % 1000 - 500;
    }
    my_qsort(big, 200, sizeof big[0], compare_ints);
    bool ascending = true;
    for (size_t i = 1; i < 200; ++i)
        if (big[i - 1] > big[i]) ascending = false;
    TRUE(ascending);
}

#elif EXERCISE == 65
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
static int compare_cstrings(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

void run_tests(void) {
    int values[] = {1, 3, 5, 7, 9};

    CASE("key 7 in {1, 3, 5, 7, 9}");
    int key = 7;
    POINTER(&values[3], my_bsearch(&key, values, 5, sizeof values[0], compare_ints));

    CASE("key 4 (absent, between elements)");
    key = 4;
    IS_NULL(my_bsearch(&key, values, 5, sizeof values[0], compare_ints));

    CASE("first and last elements, and keys outside the range");
    key = 1;
    POINTER(&values[0], my_bsearch(&key, values, 5, sizeof values[0], compare_ints));
    key = 9;
    POINTER(&values[4], my_bsearch(&key, values, 5, sizeof values[0], compare_ints));
    key = 0;
    IS_NULL(my_bsearch(&key, values, 5, sizeof values[0], compare_ints));
    key = 10;
    IS_NULL(my_bsearch(&key, values, 5, sizeof values[0], compare_ints));

    CASE("count 0 and count 1");
    key = 1;
    IS_NULL(my_bsearch(&key, values, 0, sizeof values[0], compare_ints));
    POINTER(&values[0], my_bsearch(&key, values, 1, sizeof values[0], compare_ints));
    key = 2;
    IS_NULL(my_bsearch(&key, values, 1, sizeof values[0], compare_ints));

    CASE("strings {apple, kiwi, pear}");
    const char *words[] = {"apple", "kiwi", "pear"};
    const char *needle = "kiwi";
    POINTER(&words[1], my_bsearch(&needle, words, 3, sizeof words[0], compare_cstrings));
    needle = "zebra";
    IS_NULL(my_bsearch(&needle, words, 3, sizeof words[0], compare_cstrings));

    CASE("even count with INT_MIN/INT_MAX endpoints");
    int wide[] = {INT_MIN, -5, 0, INT_MAX};
    key = INT_MIN;
    POINTER(&wide[0], my_bsearch(&key, wide, 4, sizeof wide[0], compare_ints));
    key = INT_MAX;
    POINTER(&wide[3], my_bsearch(&key, wide, 4, sizeof wide[0], compare_ints));
}

#elif EXERCISE == 66
static void add_to_int(void *context, int event) { *(int *)context += event; }
static void record_order(void *context, int event) {
    char *log = context;
    size_t n = strlen(log);
    log[n] = (char)('0' + event);
    log[n + 1] = '\0';
}
typedef struct { char *log; char tag; } Tagger;
static void push_tag(void *context, int event) {
    (void)event;
    Tagger *t = context;
    size_t n = strlen(t->log);
    t->log[n] = t->tag;
    t->log[n + 1] = '\0';
}

void run_tests(void) {
    CASE("one handler, emit 5 then 7");
    Emitter e = {0};
    int sum = 0;
    INT(0, emitter_connect(&e, add_to_int, &sum));
    UINT(1, e.count);
    emitter_emit(&e, 5);
    emitter_emit(&e, 7);
    INT(12, sum);

    CASE("same handler, two contexts");
    Emitter e2 = {0};
    int a = 0, b = 10;
    INT(0, emitter_connect(&e2, add_to_int, &a));
    INT(0, emitter_connect(&e2, add_to_int, &b));
    emitter_emit(&e2, 1);
    INT(1, a);
    INT(11, b);

    CASE("handlers run in registration order");
    Emitter e3 = {0};
    char log[16] = "";
    Tagger ctx_x = {log, 'x'}, ctx_y = {log, 'y'};
    INT(0, emitter_connect(&e3, push_tag, &ctx_x));
    INT(0, emitter_connect(&e3, record_order, log));
    INT(0, emitter_connect(&e3, push_tag, &ctx_y));
    emitter_emit(&e3, 3);
    STRING("x3y", log);

    CASE("emit with no handlers does nothing");
    Emitter e4 = {0};
    emitter_emit(&e4, 99);
    UINT(0, e4.count);

    CASE("ninth connect fails, count stays 8");
    Emitter e5 = {0};
    int counters[9] = {0};
    for (size_t i = 0; i < 8; ++i) INT(0, emitter_connect(&e5, add_to_int, &counters[i]));
    INT(-1, emitter_connect(&e5, add_to_int, &counters[8]));
    UINT(8, e5.count);
    emitter_emit(&e5, 2);
    INT(2, counters[0]);
    INT(2, counters[7]);
    INT(0, counters[8]);

    CASE("NULL handler is rejected");
    Emitter e6 = {0};
    INT(-1, emitter_connect(&e6, NULL, NULL));
    UINT(0, e6.count);
}

#elif EXERCISE == 67
void run_tests(void) {
    CASE("dog Rex");
    Animal *dog = animal_new_dog("Rex");
    NOT_NULL(dog);
    if (dog) {
        STRING("Woof", animal_speak(dog));
        STRING("Rex", dog->name);
    }
    animal_free(dog);

    CASE("cat Tom");
    Animal *cat = animal_new_cat("Tom");
    NOT_NULL(cat);
    if (cat) {
        STRING("Meow", animal_speak(cat));
        STRING("Tom", cat->name);
    }
    animal_free(cat);

    CASE("name is copied, not aliased");
    char buffer[16] = "Fido";
    dog = animal_new_dog(buffer);
    NOT_NULL(dog);
    strcpy(buffer, "CHANGED");
    if (dog) {
        STRING("Fido", dog->name);
        TRUE(dog->name != buffer);
    }
    animal_free(dog);

    CASE("heterogeneous array dispatches per object");
    Animal *zoo[3] = {animal_new_cat("a"), animal_new_dog("b"), animal_new_cat("")};
    const char *expected[3] = {"Meow", "Woof", "Meow"};
    for (size_t i = 0; i < 3; ++i) {
        NOT_NULL(zoo[i]);
        if (zoo[i]) STRING(expected[i], animal_speak(zoo[i]));
    }
    if (zoo[2]) STRING("", zoo[2]->name);
    for (size_t i = 0; i < 3; ++i) animal_free(zoo[i]);

    CASE("animal_free(NULL) is a no-op");
    animal_free(NULL);
    TRUE(true);
}

#elif EXERCISE == 68
void run_tests(void) {
    CASE("describe_int");
    STRING("int", describe_int(7));
    STRING("int", describe_int(INT_MIN));

    CASE("describe_double");
    STRING("double", describe_double(2.5));
    STRING("double", describe_double(-1e9));

    CASE("describe_string is exactly const char *");
    STRING("const char *", describe_string("hi"));
    STRING("const char *", describe_string(NULL));

    CASE("the macro itself on other types");
    char c = 'a';
    char *mutable_string = c == 'a' ? NULL : &c;
    STRING("char", TYPE_NAME(c));
    STRING("int", TYPE_NAME('a'));
    STRING("char *", TYPE_NAME(mutable_string));
    STRING("unknown", TYPE_NAME(1.0f));
}
#endif
