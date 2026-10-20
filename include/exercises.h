#ifndef C_PRACTICE_TRACK_EXERCISES_H
#define C_PRACTICE_TRACK_EXERCISES_H

/* The contract. Every exercise implements exactly the prototype declared
 * here; the tests call these names. Do not change signatures. */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* ---------- Stage 1: Foundations (001-010) ---------- */
int sign(int value);
int max_of_three(int a, int b, int c);
bool is_leap_year(int year);
int gcd(int a, int b);
bool is_prime(unsigned value);
int digit_sum(int value);
uint64_t fibonacci(unsigned n);
bool add_overflows(int a, int b);
double average(const int *values, size_t count);
int collatz_steps(uint64_t n);

/* ---------- Stage 2: Pointers and arrays (011-020) ---------- */
void swap_int(int *a, int *b);
size_t array_max_index(const int *values, size_t count);
void array_reverse(int *values, size_t count);
void array_rotate_left(int *values, size_t count, size_t k);
ptrdiff_t find_index(const int *values, size_t count, int target);
ptrdiff_t pointer_distance(const int *first, const int *second);
void matrix_transpose(size_t n, int matrix[n][n]);
void apply_each(int *values, size_t count, int (*transform)(int));
size_t count_matching(const int *values, size_t count, bool (*predicate)(int));
size_t remove_duplicates_sorted(int *values, size_t count);

/* ---------- Stage 3: Strings (021-032) ---------- */
size_t my_strlen(const char *s);
char *my_strcpy(char *destination, const char *source);
int my_strcmp(const char *a, const char *b);
char *my_strchr(const char *s, int c);
char *my_strstr(const char *haystack, const char *needle);
void reverse_string(char *s);
bool is_palindrome(const char *s);
char *trim(char *s);
size_t count_words(const char *s);
int my_atoi(const char *s);
int int_to_string(int value, char *destination, size_t capacity);
int compress_runs(const char *s, char *destination, size_t capacity);

/* ---------- Stage 4: Structs, enums, unions, bit-fields (033-040) ---------- */
typedef struct { double x, y; } Point;
double point_distance(Point a, Point b);

typedef struct { Point origin; double width, height; } Rect;
double rect_area(Rect r);
bool rect_contains(Rect r, Point p);

typedef struct { char name[32]; int score; } Student;
int compare_students(const void *a, const void *b); /* qsort order: score desc, then name asc */

typedef enum { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, DAY_COUNT } Day;
const char *day_name(Day day);
Day next_day(Day day);

typedef struct { int id; char tag[8]; double weight; } Record;
#define CONTAINER_OF(pointer, Type, member) ((Type *)((char *)(pointer) - offsetof(Type, member)))
Record *record_from_weight(double *weight_pointer);

uint32_t float_bits(float value);
float bits_to_float(uint32_t bits);

typedef struct { unsigned read : 1, write : 1, execute : 1, level : 5; } Permissions;
uint8_t encode_permissions(Permissions p);
Permissions decode_permissions(uint8_t byte);

typedef struct { size_t length; char data[]; } OwnedString;
OwnedString *owned_string_new(const char *s);

/* ---------- Stage 5: Memory (041-050) ---------- */
char *my_strdup(const char *s);
int *array_clone(const int *values, size_t count);

typedef struct { int *data; size_t length, capacity; } IntVector;
int vector_push(IntVector *vector, int value);
void vector_free(IntVector *vector);

char *string_join(const char *const *parts, size_t count, const char *separator);
char *read_line(FILE *stream);

typedef struct { unsigned char *base; size_t capacity, used; } Arena;
int arena_init(Arena *arena, size_t capacity);
void *arena_alloc(Arena *arena, size_t size, size_t alignment);
void arena_free(Arena *arena);

int **matrix_alloc(size_t rows, size_t columns);
void matrix_free(int **matrix);

void *my_calloc(size_t count, size_t size);

typedef struct { char *data; size_t length, capacity; } StringBuilder;
int sb_append(StringBuilder *sb, const char *s);
char *sb_finish(StringBuilder *sb);

typedef struct { unsigned char *storage; void *free_list; size_t block_size, block_count; } Pool;
int pool_init(Pool *pool, size_t block_size, size_t block_count);
void *pool_get(Pool *pool);
void pool_put(Pool *pool, void *block);
void pool_free(Pool *pool);

#endif
