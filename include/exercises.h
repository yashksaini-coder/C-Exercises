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

/* ---------- Stage 6: Bits and bytes (051-060) ---------- */
unsigned bit_count(uint32_t value);
bool is_power_of_two(uint64_t value);
uint32_t reverse_bits(uint32_t value);
uint32_t bit_set(uint32_t value, unsigned index, bool on);
uint32_t read_u32_be(const unsigned char *bytes);
void write_u32_be(unsigned char *bytes, uint32_t value);
uint16_t my_htons(uint16_t value);
uint32_t my_htonl(uint32_t value);
size_t pack(unsigned char *buffer, const char *format, ...);
size_t unpack(const unsigned char *buffer, const char *format, ...);
uint16_t internet_checksum(const unsigned char *data, size_t length);

/* ---------- Stage 7: Object-oriented C (061-068) ---------- */
typedef struct Counter Counter; /* opaque: defined only in 061.c */
Counter *counter_new(int start);
void counter_increment(Counter *counter);
int counter_get(const Counter *counter);
void counter_free(Counter *counter);

typedef struct Shape Shape;
typedef struct {
    double (*area)(const Shape *self);
    double (*perimeter)(const Shape *self);
    const char *(*name)(const Shape *self);
} ShapeVTable;
struct Shape { const ShapeVTable *vtable; };
Shape *shape_new_circle(double radius);
Shape *shape_new_rectangle(double width, double height);
double shape_area(const Shape *shape);
double shape_perimeter(const Shape *shape);
const char *shape_name(const Shape *shape);
void shape_free(Shape *shape);

typedef int (*Comparator)(const void *a, const void *b);
const void *generic_max(const void *base, size_t count, size_t size, Comparator compare);
void my_qsort(void *base, size_t count, size_t size, Comparator compare);
void *my_bsearch(const void *key, const void *base, size_t count, size_t size, Comparator compare);

typedef void (*EventHandler)(void *context, int event);
typedef struct { EventHandler handlers[8]; void *contexts[8]; size_t count; } Emitter;
int emitter_connect(Emitter *emitter, EventHandler handler, void *context);
void emitter_emit(Emitter *emitter, int event);

typedef struct Animal Animal;
struct Animal { const char *(*speak)(const Animal *self); const char *name; };
Animal *animal_new_dog(const char *name);
Animal *animal_new_cat(const char *name);
const char *animal_speak(const Animal *animal);
void animal_free(Animal *animal);

#define TYPE_NAME(x) _Generic((x), int: "int", double: "double", char: "char", char *: "char *", const char *: "const char *", default: "unknown")
const char *describe_int(int value);
const char *describe_double(double value);
const char *describe_string(const char *value);

/* ---------- Stage 8: Data structures (069-079) ---------- */
typedef struct { int items[64]; size_t count; } Stack;
int stack_push(Stack *stack, int value);
int stack_pop(Stack *stack, int *out);

typedef struct { int items[8]; size_t head, count; } Queue;
int queue_enqueue(Queue *queue, int value);
int queue_dequeue(Queue *queue, int *out);

typedef struct IntNode { int value; struct IntNode *next; } IntNode;
int list_push_back(IntNode **head, int value);
size_t list_length(const IntNode *head);
void list_free(IntNode *head);
IntNode *list_reverse(IntNode *head);
bool list_has_cycle(const IntNode *head);
IntNode *list_merge_sorted(IntNode *a, IntNode *b);

uint64_t hash_djb2(const char *s);
typedef struct HashEntry { char *key; int value; struct HashEntry *next; } HashEntry;
typedef struct { HashEntry *buckets[64]; size_t count; } HashMap;
int hashmap_put(HashMap *map, const char *key, int value);
bool hashmap_get(const HashMap *map, const char *key, int *out);
void hashmap_free(HashMap *map);

typedef struct TreeNode { int value; struct TreeNode *left, *right; } TreeNode;
int bst_insert(TreeNode **root, int value);
bool bst_contains(const TreeNode *root, int value);
void bst_free(TreeNode *root);
size_t bst_height(const TreeNode *root);
size_t bst_to_sorted_array(const TreeNode *root, int *out, size_t capacity);

typedef struct { int items[64]; size_t count; } MinHeap;
int heap_push(MinHeap *heap, int value);
int heap_pop(MinHeap *heap, int *out);

typedef struct LruNode { int key, value; struct LruNode *prev, *next; } LruNode;
typedef struct { size_t capacity, count; LruNode *head, *tail; } LruCache;
void lru_init(LruCache *cache, size_t capacity);
bool lru_get(LruCache *cache, int key, int *out);
int lru_put(LruCache *cache, int key, int value);
void lru_free(LruCache *cache);

#endif
