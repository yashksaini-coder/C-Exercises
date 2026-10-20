#include "support.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_5_keep_translation_unit_nonempty;

#if EXERCISE == 41
void run_tests(void) {
    STRING_CASE("hello");
    const char *literal = "hello";
    char *copy = my_strdup(literal);
    NOT_NULL(copy);
    if (copy) {
        STRING("hello", copy);
        TRUE(copy != literal);
        free(copy);
    }
    STRING_CASE("");
    char *empty = my_strdup("");
    NOT_NULL(empty);
    if (empty) {
        STRING("", empty);
        free(empty);
    }
    CASE("NULL");
    IS_NULL(my_strdup(NULL));
    CASE("copy is independent and NUL-terminated (the +1)");
    char source[] = "abcdefghijklmnop"; /* 16 chars: a 16-byte malloc would miss the NUL */
    char *dup = my_strdup(source);
    NOT_NULL(dup);
    source[0] = 'Z';
    if (dup) {
        STRING("abcdefghijklmnop", dup);
        INT(0, dup[16]);
        free(dup);
    }
}
#elif EXERCISE == 42
void run_tests(void) {
    CASE("{1,2,3}");
    int a[] = {1, 2, 3};
    int *copy = array_clone(a, 3);
    NOT_NULL(copy);
    if (copy) {
        ARRAY(a, copy, 3);
        TRUE(copy != a);
        free(copy);
    }
    CASE("independent of the source");
    int b[] = {10, 20, 30, 40};
    int *c = array_clone(b, 4);
    NOT_NULL(c);
    b[1] = -1;
    if (c) {
        INT(20, c[1]);
        INT(40, c[3]);
        free(c);
    }
    CASE("INT_MIN and INT_MAX");
    int extremes[] = {INT_MIN, INT_MAX};
    int *e = array_clone(extremes, 2);
    NOT_NULL(e);
    if (e) {
        ARRAY(extremes, e, 2);
        free(e);
    }
    CASE("NULL source with count 5");
    IS_NULL(array_clone(NULL, 5));
    CASE("100 elements (malloc(count) would be too small)");
    int big[100];
    for (int i = 0; i < 100; ++i) big[i] = i * 7;
    int *bc = array_clone(big, 100);
    NOT_NULL(bc);
    if (bc) {
        ARRAY(big, bc, 100);
        free(bc);
    }
}
#elif EXERCISE == 43
void run_tests(void) {
    CASE("three pushes into a zeroed vector");
    IntVector v = {0};
    INT(0, vector_push(&v, 1));
    INT(0, vector_push(&v, 2));
    INT(0, vector_push(&v, 3));
    UINT(3u, v.length);
    UINT(4u, v.capacity);
    NOT_NULL(v.data);
    if (v.data) {
        int expected[] = {1, 2, 3};
        ARRAY(expected, v.data, 3);
    }
    CASE("fifth push doubles to 8 and preserves data");
    vector_push(&v, 4);
    vector_push(&v, 5);
    UINT(5u, v.length);
    UINT(8u, v.capacity);
    if (v.data) {
        int expected[] = {1, 2, 3, 4, 5};
        ARRAY(expected, v.data, 5);
    }
    CASE("100 pushes -> capacity 128");
    for (int i = 6; i <= 100; ++i) INT(0, vector_push(&v, i));
    UINT(100u, v.length);
    UINT(128u, v.capacity);
    bool all_match = v.data != NULL;
    for (size_t i = 0; all_match && i < 100; ++i)
        if (v.data[i] != (int)i + 1) all_match = false;
    TRUE(all_match);
    CASE("vector_free zeroes the fields and is idempotent");
    vector_free(&v);
    IS_NULL(v.data);
    UINT(0u, v.length);
    UINT(0u, v.capacity);
    vector_free(&v);
    IS_NULL(v.data);
    CASE("reuse after free, NULL vector rejected");
    INT(0, vector_push(&v, 42));
    UINT(1u, v.length);
    UINT(4u, v.capacity);
    if (v.data) INT(42, v.data[0]);
    INT(-1, vector_push(NULL, 1));
    vector_free(&v);
    vector_free(NULL);
}
#elif EXERCISE == 44
void run_tests(void) {
    CASE("{a,b,c} with \", \"");
    const char *const abc[] = {"a", "b", "c"};
    char *s = string_join(abc, 3, ", ");
    NOT_NULL(s);
    if (s) {
        STRING("a, b, c", s);
        free(s);
    }
    CASE("single part has no separator");
    const char *const x[] = {"x"};
    char *one = string_join(x, 1, "-");
    NOT_NULL(one);
    if (one) {
        STRING("x", one);
        free(one);
    }
    CASE("empty separator");
    const char *const ab[] = {"ab", "cd"};
    char *joined = string_join(ab, 2, "");
    NOT_NULL(joined);
    if (joined) {
        STRING("abcd", joined);
        free(joined);
    }
    CASE("count 0 -> allocated \"\"");
    char *empty = string_join(NULL, 0, "+");
    NOT_NULL(empty);
    if (empty) {
        STRING("", empty);
        free(empty);
    }
    CASE("empty parts still get separators");
    const char *const blanks[] = {"", "", ""};
    char *slashes = string_join(blanks, 3, "/");
    NOT_NULL(slashes);
    if (slashes) {
        STRING("//", slashes);
        free(slashes);
    }
    CASE("multi-character separator, exact length");
    const char *const words[] = {"one", "two", "three"};
    char *w = string_join(words, 3, " and ");
    NOT_NULL(w);
    if (w) {
        STRING("one and two and three", w);
        UINT(21u, strlen(w));
        free(w);
    }
}
#elif EXERCISE == 45
static FILE *stream_with(const char *content) {
    FILE *f = tmpfile();
    if (!f) return NULL;
    fputs(content, f);
    rewind(f);
    return f;
}
void run_tests(void) {
    CASE("\"alpha\\n\\nlast\" line by line");
    FILE *f = stream_with("alpha\n\nlast");
    NOT_NULL(f);
    if (f) {
        char *l1 = read_line(f);
        char *l2 = read_line(f);
        char *l3 = read_line(f);
        char *l4 = read_line(f);
        STRING("alpha", l1);
        STRING("", l2);
        STRING("last", l3);
        IS_NULL(l4);
        free(l1);
        free(l2);
        free(l3);
        free(l4);
        fclose(f);
    }
    CASE("empty stream -> NULL immediately");
    FILE *e = stream_with("");
    NOT_NULL(e);
    if (e) {
        IS_NULL(read_line(e));
        fclose(e);
    }
    CASE("single newline -> \"\" then NULL");
    FILE *n = stream_with("\n");
    NOT_NULL(n);
    if (n) {
        char *l = read_line(n);
        STRING("", l);
        free(l);
        IS_NULL(read_line(n));
        fclose(n);
    }
    CASE("5000-character line longer than any fixed buffer");
    FILE *big = tmpfile();
    NOT_NULL(big);
    if (big) {
        for (int i = 0; i < 5000; ++i) fputc('a' + (i % 26), big);
        fputs("\nshort\n", big);
        rewind(big);
        char *l = read_line(big);
        NOT_NULL(l);
        if (l) {
            UINT(5000u, strlen(l));
            INT('a', l[0]);
            INT('a' + (4999 % 26), l[4999]);
            free(l);
        }
        char *s = read_line(big);
        STRING("short", s);
        free(s);
        IS_NULL(read_line(big));
        fclose(big);
    }
    CASE("NULL stream");
    IS_NULL(read_line(NULL));
}
#elif EXERCISE == 46
void run_tests(void) {
    CASE("init 64 bytes");
    Arena a = {0};
    INT(0, arena_init(&a, 64));
    NOT_NULL(a.base);
    UINT(64u, a.capacity);
    UINT(0u, a.used);
    CASE("alloc 1 byte align 1, then 4 bytes align 8");
    void *p = arena_alloc(&a, 1, 1);
    POINTER(a.base, p);
    UINT(1u, a.used);
    void *q = arena_alloc(&a, 4, 8);
    POINTER(a.base + 8, q);
    UINT(12u, a.used);
    CASE("too large does not fit and leaves used unchanged");
    IS_NULL(arena_alloc(&a, 100, 1));
    UINT(12u, a.used);
    IS_NULL(arena_alloc(&a, SIZE_MAX, 1));
    UINT(12u, a.used);
    CASE("exact fit to the end, then full");
    void *r = arena_alloc(&a, 52, 4);
    POINTER(a.base + 12, r);
    UINT(64u, a.used);
    IS_NULL(arena_alloc(&a, 1, 1));
    UINT(64u, a.used);
    CASE("memory is writable across the whole range");
    if (p && q && r) {
        memset(p, 0xAA, 1);
        memset(q, 0xBB, 4);
        memset(r, 0xCC, 52);
        INT(0xAA, a.base[0]);
        INT(0xBB, a.base[11]);
        INT(0xCC, a.base[63]);
    }
    arena_free(&a);
    IS_NULL(a.base);
    UINT(0u, a.capacity);
    UINT(0u, a.used);
    CASE("alignment 16 from offset 1, alignment 0 treated as 1, size 0");
    Arena b = {0};
    INT(0, arena_init(&b, 40));
    arena_alloc(&b, 1, 1);
    void *s = arena_alloc(&b, 8, 16);
    POINTER(b.base + 16, s);
    UINT(24u, b.used);
    void *t = arena_alloc(&b, 3, 0);
    POINTER(b.base + 24, t);
    UINT(27u, b.used);
    void *u = arena_alloc(&b, 0, 8);
    POINTER(b.base + 32, u);
    UINT(32u, b.used);
    arena_free(&b);
    arena_free(&b); /* double free of a zeroed arena is a no-op */
    arena_free(NULL);
    INT(-1, arena_init(NULL, 8));
}
#elif EXERCISE == 47
void run_tests(void) {
    CASE("3x4 matrix is zeroed");
    int **m = matrix_alloc(3, 4);
    NOT_NULL(m);
    if (m) {
        bool zero = true;
        for (size_t r = 0; r < 3; ++r)
            for (size_t c = 0; c < 4; ++c)
                if (m[r][c] != 0) zero = false;
        TRUE(zero);
        CASE("write one cell, others untouched; rows contiguous");
        m[1][2] = 7;
        INT(7, m[1][2]);
        INT(0, m[0][2]);
        INT(0, m[2][2]);
        INT(0, m[1][1]);
        POINTER(m[0] + 4, m[1]);
        POINTER(m[0] + 8, m[2]);
        CASE("fill every cell and read it back through the row pointers");
        for (size_t r = 0; r < 3; ++r)
            for (size_t c = 0; c < 4; ++c) m[r][c] = (int)(r * 10 + c);
        INT(23, m[2][3]);
        INT(0, m[0][0]);
        INT(21, m[0][9]); /* contiguous: row 0 index 9 is m[2][1] */
        matrix_free(m);
    }
    CASE("1x1 and 1x1000");
    int **one = matrix_alloc(1, 1);
    NOT_NULL(one);
    if (one) {
        INT(0, one[0][0]);
        one[0][0] = 5;
        INT(5, one[0][0]);
        matrix_free(one);
    }
    int **wide = matrix_alloc(1, 1000);
    NOT_NULL(wide);
    if (wide) {
        wide[0][999] = 9;
        INT(9, wide[0][999]);
        matrix_free(wide);
    }
    CASE("zero rows or columns -> NULL; free(NULL) is a no-op");
    IS_NULL(matrix_alloc(0, 5));
    IS_NULL(matrix_alloc(5, 0));
    IS_NULL(matrix_alloc(0, 0));
    matrix_free(NULL);
}
#elif EXERCISE == 48
void run_tests(void) {
    CASE("10 ints are zeroed");
    int *p = my_calloc(10, sizeof(int));
    NOT_NULL(p);
    if (p) {
        bool zero = true;
        for (int i = 0; i < 10; ++i)
            if (p[i] != 0) zero = false;
        TRUE(zero);
        p[9] = 1;
        INT(1, p[9]);
        free(p);
    }
    CASE("SIZE_MAX/2 * 4 overflows -> NULL");
    IS_NULL(my_calloc(SIZE_MAX / 2, 4));
    CASE("SIZE_MAX * 2 and the off-by-one boundary");
    IS_NULL(my_calloc(SIZE_MAX, 2));
    IS_NULL(my_calloc(SIZE_MAX / 4 + 1, 4));
    IS_NULL(my_calloc(4, SIZE_MAX / 4 + 1));
    CASE("byte buffer of 4096 is all zero");
    unsigned char *bytes = my_calloc(4096, 1);
    NOT_NULL(bytes);
    if (bytes) {
        bool zero = true;
        for (size_t i = 0; i < 4096; ++i)
            if (bytes[i]) zero = false;
        TRUE(zero);
        free(bytes);
    }
    CASE("zero count or size: NULL or a freeable pointer");
    void *z = my_calloc(0, 8);
    free(z);
    void *z2 = my_calloc(8, 0);
    free(z2);
    TRUE(true);
}
#elif EXERCISE == 49
void run_tests(void) {
    CASE("foo + bar + ! -> foobar!");
    StringBuilder sb = {0};
    INT(0, sb_append(&sb, "foo"));
    INT(0, sb_append(&sb, "bar"));
    INT(0, sb_append(&sb, "!"));
    UINT(7u, sb.length);
    TRUE(sb.capacity >= 8);
    NOT_NULL(sb.data);
    if (sb.data) STRING("foobar!", sb.data);
    char *s = sb_finish(&sb);
    STRING("foobar!", s);
    free(s);
    CASE("builder is reset to {0} after finish");
    IS_NULL(sb.data);
    UINT(0u, sb.length);
    UINT(0u, sb.capacity);
    CASE("finish on a fresh builder -> allocated \"\"");
    StringBuilder fresh = {0};
    char *empty = sb_finish(&fresh);
    NOT_NULL(empty);
    if (empty) STRING("", empty);
    free(empty);
    CASE("reuse after finish");
    INT(0, sb_append(&sb, "again"));
    char *again = sb_finish(&sb);
    STRING("again", again);
    free(again);
    CASE("1000 appends of \"ab\" -> 2000 chars, NUL-terminated throughout");
    for (int i = 0; i < 1000; ++i) INT(0, sb_append(&sb, "ab"));
    UINT(2000u, sb.length);
    if (sb.data) {
        UINT(2000u, strlen(sb.data));
        INT('a', sb.data[1998]);
        INT('b', sb.data[1999]);
    }
    char *big = sb_finish(&sb);
    NOT_NULL(big);
    if (big) UINT(2000u, strlen(big));
    free(big);
    CASE("append \"\" and NULL arguments");
    INT(0, sb_append(&sb, ""));
    UINT(0u, sb.length);
    INT(-1, sb_append(&sb, NULL));
    INT(-1, sb_append(NULL, "x"));
    IS_NULL(sb_finish(NULL));
    char *e = sb_finish(&sb);
    STRING("", e);
    free(e);
}
#elif EXERCISE == 50
static bool inside(const Pool *p, const void *block) {
    const unsigned char *b = block;
    return b >= p->storage && b < p->storage + p->block_size * p->block_count &&
           (size_t)(b - p->storage) % p->block_size == 0;
}
void run_tests(void) {
    CASE("init 12-byte blocks x 3: block_size rounds up to a pointer multiple");
    Pool p = {0};
    INT(0, pool_init(&p, 12, 3));
    NOT_NULL(p.storage);
    NOT_NULL(p.free_list);
    UINT(3u, p.block_count);
    TRUE(p.block_size >= 12);
    UINT(0u, p.block_size % sizeof(void *));
    CASE("get all three: distinct, inside storage; fourth is NULL");
    void *a = pool_get(&p), *b = pool_get(&p), *c = pool_get(&p);
    NOT_NULL(a);
    NOT_NULL(b);
    NOT_NULL(c);
    TRUE(a != b && b != c && a != c);
    TRUE(inside(&p, a) && inside(&p, b) && inside(&p, c));
    IS_NULL(pool_get(&p));
    IS_NULL(p.free_list);
    CASE("blocks are usable for their whole size");
    if (a && b && c) {
        memset(a, 0x11, p.block_size);
        memset(b, 0x22, p.block_size);
        memset(c, 0x33, p.block_size);
        INT(0x11, ((unsigned char *)a)[p.block_size - 1]);
        INT(0x22, ((unsigned char *)b)[0]);
    }
    CASE("put one back, get returns that same pointer (LIFO)");
    pool_put(&p, b);
    POINTER(b, pool_get(&p));
    IS_NULL(pool_get(&p));
    CASE("put two back, get returns them in reverse order, then NULL");
    pool_put(&p, a);
    pool_put(&p, c);
    POINTER(c, pool_get(&p));
    POINTER(a, pool_get(&p));
    IS_NULL(pool_get(&p));
    pool_put(&p, NULL); /* no-op */
    IS_NULL(pool_get(&p));
    pool_free(&p);
    IS_NULL(p.storage);
    IS_NULL(p.free_list);
    UINT(0u, p.block_size);
    UINT(0u, p.block_count);
    CASE("tiny block_size is raised to sizeof(void *); count 0 rejected");
    Pool q = {0};
    INT(0, pool_init(&q, 1, 4));
    UINT(sizeof(void *), q.block_size);
    void *blocks[4];
    for (int i = 0; i < 4; ++i) blocks[i] = pool_get(&q);
    TRUE(blocks[0] && blocks[1] && blocks[2] && blocks[3]);
    IS_NULL(pool_get(&q));
    for (int i = 0; i < 4; ++i) pool_put(&q, blocks[i]);
    POINTER(blocks[3], pool_get(&q));
    pool_free(&q);
    pool_free(&q);
    pool_free(NULL);
    Pool z = {0};
    INT(-1, pool_init(&z, 8, 0));
    INT(-1, pool_init(NULL, 8, 1));
}
#endif
