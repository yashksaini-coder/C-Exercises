#include "support.h"
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_4_keep_translation_unit_nonempty;

#if EXERCISE == 33
void run_tests(void) {
    Point origin = {0.0, 0.0};
    Point p34 = {3.0, 4.0};
    Point one = {1.0, 1.0};
    Point neg = {-1.0, -1.0};
    Point two3 = {2.0, 3.0};
    CASE("(0,0) to (3,4)");
    DOUBLE(5.0, point_distance(origin, p34));
    CASE("symmetry: (3,4) to (0,0)");
    DOUBLE(5.0, point_distance(p34, origin));
    CASE("same point (1,1)");
    DOUBLE(0.0, point_distance(one, one));
    CASE("negative coordinates (-1,-1) to (2,3)");
    DOUBLE(5.0, point_distance(neg, two3));
    CASE("(0,0) to (1,1) is sqrt(2)");
    DOUBLE_NEAR(1.4142135623730951, point_distance(origin, one), 1e-12);
}
#elif EXERCISE == 34
void run_tests(void) {
    Rect r = {{0.0, 0.0}, 10.0, 5.0};
    Rect shifted = {{-2.0, -2.0}, 4.0, 4.0};
    Rect flat = {{1.0, 1.0}, 3.0, 0.0};
    CASE("area 10x5 and 4x4");
    DOUBLE(50.0, rect_area(r));
    DOUBLE(16.0, rect_area(shifted));
    CASE("interior point (5,2.5)");
    Point inside = {5.0, 2.5};
    TRUE(rect_contains(r, inside));
    CASE("corners are inclusive");
    Point c0 = {0.0, 0.0}, c1 = {10.0, 5.0}, c2 = {10.0, 0.0}, c3 = {0.0, 5.0};
    TRUE(rect_contains(r, c0));
    TRUE(rect_contains(r, c1));
    TRUE(rect_contains(r, c2));
    TRUE(rect_contains(r, c3));
    CASE("just outside each edge");
    Point right = {10.0001, 5.0}, left = {-0.5, 2.0}, above = {5.0, 5.0001}, below = {5.0, -0.0001};
    FALSE(rect_contains(r, right));
    FALSE(rect_contains(r, left));
    FALSE(rect_contains(r, above));
    FALSE(rect_contains(r, below));
    CASE("rect with negative origin and zero-height rect");
    Point o = {0.0, 0.0}, far = {2.5, 0.0}, onflat = {2.0, 1.0}, offflat = {2.0, 1.1};
    TRUE(rect_contains(shifted, o));
    FALSE(rect_contains(shifted, far));
    DOUBLE(0.0, rect_area(flat));
    TRUE(rect_contains(flat, onflat));
    FALSE(rect_contains(flat, offflat));
}
#elif EXERCISE == 35
static bool sorted_names_match(const Student *s, size_t count, const char *const *names) {
    for (size_t i = 0; i < count; ++i)
        if (strcmp(s[i].name, names[i]) != 0) return false;
    return true;
}
void run_tests(void) {
    CASE("direct comparisons");
    Student bob90 = {"bob", 90}, amy80 = {"amy", 80}, amy90 = {"amy", 90};
    TRUE(compare_students(&bob90, &amy80) < 0);
    TRUE(compare_students(&amy80, &bob90) > 0);
    TRUE(compare_students(&bob90, &amy90) > 0);
    TRUE(compare_students(&amy90, &bob90) < 0);
    INT(0, compare_students(&amy90, &amy90));
    CASE("qsort four students");
    Student s[] = {{"cat", 70}, {"amy", 90}, {"bob", 90}, {"dan", 100}};
    qsort(s, 4, sizeof(Student), compare_students);
    const char *const expected[] = {"dan", "amy", "bob", "cat"};
    TRUE(sorted_names_match(s, 4, expected));
    INT(100, s[0].score);
    INT(70, s[3].score);
    CASE("all equal scores sort by name");
    Student t[] = {{"zed", 5}, {"ann", 5}, {"mia", 5}};
    qsort(t, 3, sizeof(Student), compare_students);
    const char *const expected2[] = {"ann", "mia", "zed"};
    TRUE(sorted_names_match(t, 3, expected2));
    CASE("INT_MIN vs INT_MAX must not overflow");
    Student lo = {"lo", INT_MIN}, hi = {"hi", INT_MAX};
    TRUE(compare_students(&hi, &lo) < 0);
    TRUE(compare_students(&lo, &hi) > 0);
    Student u[] = {{"lo", INT_MIN}, {"hi", INT_MAX}, {"mid", 0}};
    qsort(u, 3, sizeof(Student), compare_students);
    const char *const expected3[] = {"hi", "mid", "lo"};
    TRUE(sorted_names_match(u, 3, expected3));
}
#elif EXERCISE == 36
void run_tests(void) {
    CASE("names of all seven days");
    STRING("Monday", day_name(MONDAY));
    STRING("Tuesday", day_name(TUESDAY));
    STRING("Wednesday", day_name(WEDNESDAY));
    STRING("Thursday", day_name(THURSDAY));
    STRING("Friday", day_name(FRIDAY));
    STRING("Saturday", day_name(SATURDAY));
    STRING("Sunday", day_name(SUNDAY));
    CASE("invalid days give \"?\"");
    STRING("?", day_name(DAY_COUNT));
    STRING("?", day_name((Day)100));
    STRING("?", day_name((Day)-1));
    CASE("next_day in the middle of the week");
    INT(TUESDAY, next_day(MONDAY));
    INT(SATURDAY, next_day(FRIDAY));
    INT(SUNDAY, next_day(SATURDAY));
    CASE("SUNDAY wraps to MONDAY");
    INT(MONDAY, next_day(SUNDAY));
    CASE("seven steps return to the start");
    Day d = WEDNESDAY;
    for (int i = 0; i < DAY_COUNT; ++i) d = next_day(d);
    INT(WEDNESDAY, d);
}
#elif EXERCISE == 37
void run_tests(void) {
    CASE("single record on the stack");
    Record r = {7, "abc", 2.5};
    Record *back = record_from_weight(&r.weight);
    POINTER(&r, back);
    NOT_NULL(back);
    INT(7, back->id);
    STRING("abc", back->tag);
    DOUBLE(2.5, back->weight);
    CASE("NULL in, NULL out");
    IS_NULL(record_from_weight(NULL));
    CASE("element of an array");
    Record rs[3] = {{1, "a", 1.0}, {2, "b", 2.0}, {3, "c", 3.0}};
    POINTER(&rs[2], record_from_weight(&rs[2].weight));
    POINTER(&rs[0], record_from_weight(&rs[0].weight));
    INT(2, record_from_weight(&rs[1].weight)->id);
    CASE("heap record, and the offset is not hard-coded");
    Record *heap = malloc(sizeof *heap);
    NOT_NULL(heap);
    heap->id = 42;
    heap->weight = 9.0;
    POINTER(heap, record_from_weight(&heap->weight));
    UINT(offsetof(Record, weight), (size_t)((char *)&heap->weight - (char *)record_from_weight(&heap->weight)));
    free(heap);
}
#elif EXERCISE == 38
void run_tests(void) {
    CASE("1.0f -> 0x3F800000");
    UINT(0x3F800000u, float_bits(1.0f));
    CASE("-0.0f -> 0x80000000, 0.0f -> 0");
    UINT(0x80000000u, float_bits(-0.0f));
    UINT(0u, float_bits(0.0f));
    CASE("0x7F800000 -> +INFINITY, 0xFF800000 -> -INFINITY");
    TRUE(isinf(bits_to_float(0x7F800000u)));
    TRUE(bits_to_float(0x7F800000u) > 0.0f);
    TRUE(isinf(bits_to_float(0xFF800000u)));
    TRUE(bits_to_float(0xFF800000u) < 0.0f);
    CASE("pi: 0x40490FDB");
    DOUBLE_NEAR(3.14159274, (double)bits_to_float(0x40490FDBu), 1e-7);
    UINT(0x40490FDBu, float_bits(3.14159274f));
    CASE("conversion is not punning: 2.0f is 0x40000000 not 2");
    UINT(0x40000000u, float_bits(2.0f));
    UINT(0x3DCCCCCDu, float_bits(0.1f));
    CASE("round-trip of several values");
    const float values[] = {-1.5f, 123456.789f, 1e-30f, -3.0e38f, 0.5f};
    for (size_t i = 0; i < sizeof values / sizeof values[0]; ++i)
        TRUE(bits_to_float(float_bits(values[i])) == values[i]);
}
#elif EXERCISE == 39
void run_tests(void) {
    CASE("read + execute, level 0 -> 0x05");
    Permissions rx = {1, 0, 1, 0};
    UINT(0x05u, encode_permissions(rx));
    CASE("everything set -> 0xFF; nothing -> 0x00");
    Permissions all = {1, 1, 1, 31};
    Permissions none = {0, 0, 0, 0};
    UINT(0xFFu, encode_permissions(all));
    UINT(0x00u, encode_permissions(none));
    CASE("write + level 5 -> 0x2A");
    Permissions w5 = {0, 1, 0, 5};
    UINT(0x2Au, encode_permissions(w5));
    CASE("decode 0x2A");
    Permissions d = decode_permissions(0x2A);
    UINT(0u, d.read);
    UINT(1u, d.write);
    UINT(0u, d.execute);
    UINT(5u, d.level);
    CASE("decode 0xF9: level 31, read, no write/execute");
    Permissions e = decode_permissions(0xF9);
    UINT(1u, e.read);
    UINT(0u, e.write);
    UINT(0u, e.execute);
    UINT(31u, e.level);
    CASE("every byte round-trips");
    bool ok = true;
    for (unsigned b = 0; b < 256; ++b)
        if (encode_permissions(decode_permissions((uint8_t)b)) != b) ok = false;
    TRUE(ok);
}
#elif EXERCISE == 40
void run_tests(void) {
    CASE("\"hello\"");
    OwnedString *s = owned_string_new("hello");
    NOT_NULL(s);
    if (s) {
        UINT(5u, s->length);
        STRING("hello", s->data);
        POINTER((char *)s + offsetof(OwnedString, data), s->data);
        free(s);
    }
    CASE("empty string");
    OwnedString *e = owned_string_new("");
    NOT_NULL(e);
    if (e) {
        UINT(0u, e->length);
        STRING("", e->data);
        free(e);
    }
    CASE("NULL -> NULL");
    IS_NULL(owned_string_new(NULL));
    CASE("copy is independent of the source");
    char source[] = "mutable";
    OwnedString *c = owned_string_new(source);
    NOT_NULL(c);
    source[0] = 'X';
    if (c) {
        STRING("mutable", c->data);
        UINT(7u, c->length);
        free(c);
    }
    CASE("longer string with the NUL in place");
    const char *text = "the quick brown fox jumps over the lazy dog";
    OwnedString *l = owned_string_new(text);
    NOT_NULL(l);
    if (l) {
        UINT(strlen(text), l->length);
        INT(0, l->data[l->length]);
        STRING(text, l->data);
        free(l);
    }
}
#endif
