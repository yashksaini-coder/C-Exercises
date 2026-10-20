#include "support.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_8_keep_translation_unit_nonempty;

#if EXERCISE == 69
void run_tests(void) {
    CASE("push 1, 2, 3 then pop until empty");
    Stack s = {0};
    int v = -1;
    INT(0, stack_push(&s, 1));
    INT(0, stack_push(&s, 2));
    INT(0, stack_push(&s, 3));
    UINT(3, s.count);
    INT(0, stack_pop(&s, &v));
    INT(3, v);
    INT(0, stack_pop(&s, &v));
    INT(2, v);
    INT(0, stack_pop(&s, &v));
    INT(1, v);
    INT(-1, stack_pop(&s, &v));
    INT(1, v); /* untouched */
    UINT(0, s.count);

    CASE("pop on a fresh stack leaves *out alone");
    Stack empty = {0};
    v = 77;
    INT(-1, stack_pop(&empty, &v));
    INT(77, v);

    CASE("64 pushes succeed, the 65th fails");
    Stack full = {0};
    int ok = 0;
    for (int i = 0; i < 64; ++i) ok += stack_push(&full, i) == 0;
    INT(64, ok);
    UINT(64, full.count);
    INT(-1, stack_push(&full, 999));
    UINT(64, full.count);
    INT(0, stack_pop(&full, &v));
    INT(63, v);

    CASE("pop then push reuses the slot; INT_MIN/INT_MAX");
    Stack r = {0};
    stack_push(&r, INT_MIN);
    stack_push(&r, 5);
    stack_pop(&r, &v);
    stack_push(&r, INT_MAX);
    UINT(2, r.count);
    INT(0, stack_pop(&r, &v));
    INT(INT_MAX, v);
    INT(0, stack_pop(&r, &v));
    INT(INT_MIN, v);
}

#elif EXERCISE == 70
void run_tests(void) {
    CASE("enqueue 1, 2, 3; dequeue; enqueue 4; drain");
    Queue q = {0};
    int v = -1;
    INT(0, queue_enqueue(&q, 1));
    INT(0, queue_enqueue(&q, 2));
    INT(0, queue_enqueue(&q, 3));
    INT(0, queue_dequeue(&q, &v));
    INT(1, v);
    INT(0, queue_enqueue(&q, 4));
    INT(0, queue_dequeue(&q, &v));
    INT(2, v);
    INT(0, queue_dequeue(&q, &v));
    INT(3, v);
    INT(0, queue_dequeue(&q, &v));
    INT(4, v);
    INT(-1, queue_dequeue(&q, &v));
    INT(4, v);
    UINT(0, q.count);

    CASE("8 enqueues succeed, the 9th fails");
    Queue full = {0};
    int ok = 0;
    for (int i = 0; i < 8; ++i) ok += queue_enqueue(&full, i) == 0;
    INT(8, ok);
    INT(-1, queue_enqueue(&full, 99));
    UINT(8, full.count);
    INT(0, queue_dequeue(&full, &v));
    INT(0, v);

    CASE("wraparound: fill, drain 5, refill 5, drain all in order");
    Queue w = {0};
    for (int i = 0; i < 8; ++i) queue_enqueue(&w, i);
    for (int i = 0; i < 5; ++i) {
        INT(0, queue_dequeue(&w, &v));
        INT(i, v);
    }
    for (int i = 8; i < 13; ++i) INT(0, queue_enqueue(&w, i)); /* indexes wrap past 7 */
    UINT(8, w.count);
    bool in_order = true;
    for (int i = 5; i < 13; ++i) {
        if (queue_dequeue(&w, &v) != 0 || v != i) in_order = false;
    }
    TRUE(in_order);
    INT(-1, queue_dequeue(&w, &v));

    CASE("many cycles never move the array; head stays within bounds");
    Queue c = {0};
    bool consistent = true;
    for (int round = 0; round < 100; ++round) {
        if (queue_enqueue(&c, round) != 0) consistent = false;
        if (queue_dequeue(&c, &v) != 0 || v != round) consistent = false;
        if (c.head >= 8) consistent = false;
    }
    TRUE(consistent);
    UINT(0, c.count);

    CASE("dequeue on empty leaves *out alone");
    Queue e = {0};
    v = 42;
    INT(-1, queue_dequeue(&e, &v));
    INT(42, v);
}

#elif EXERCISE == 71
void run_tests(void) {
    CASE("push 1, 2, 3 onto an empty list");
    IntNode *head = NULL;
    INT(0, list_push_back(&head, 1));
    INT(0, list_push_back(&head, 2));
    INT(0, list_push_back(&head, 3));
    NOT_NULL(head);
    UINT(3, list_length(head));
    if (head) {
        INT(1, head->value);
        NOT_NULL(head->next);
        if (head->next) {
            INT(2, head->next->value);
            NOT_NULL(head->next->next);
            if (head->next->next) {
                INT(3, head->next->next->value);
                IS_NULL(head->next->next->next);
            }
        }
    }
    list_free(head);

    CASE("length of NULL and free(NULL)");
    UINT(0, list_length(NULL));
    list_free(NULL);
    TRUE(true);

    CASE("pushing keeps the original head node");
    head = NULL;
    list_push_back(&head, 10);
    IntNode *first = head;
    list_push_back(&head, 20);
    POINTER(first, head);
    UINT(2, list_length(head));
    list_free(head);

    CASE("100 pushes");
    head = NULL;
    int failures = 0;
    for (int i = 0; i < 100; ++i) failures += list_push_back(&head, i) != 0;
    INT(0, failures);
    UINT(100, list_length(head));
    int sum = 0;
    for (const IntNode *n = head; n; n = n->next) sum += n->value;
    INT(4950, sum);
    list_free(head);
}

#elif EXERCISE == 72
static void free_chain(IntNode *head) {
    while (head) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}
static IntNode *make_chain(const int *values, size_t count) {
    IntNode *head = NULL, **link = &head;
    for (size_t i = 0; i < count; ++i) {
        IntNode *n = malloc(sizeof *n);
        if (!n) break;
        n->value = values[i];
        n->next = NULL;
        *link = n;
        link = &n->next;
    }
    return head;
}

void run_tests(void) {
    CASE("1 -> 2 -> 3");
    int v123[] = {1, 2, 3};
    IntNode *head = make_chain(v123, 3);
    IntNode *old_head = head, *old_tail = head->next->next;
    IntNode *reversed = list_reverse(head);
    POINTER(old_tail, reversed);
    if (reversed == old_tail) {
        INT(3, reversed->value);
        INT(2, reversed->next->value);
        INT(1, reversed->next->next->value);
        IS_NULL(reversed->next->next->next);
        POINTER(old_head, reversed->next->next);
        free_chain(reversed);
    } else {
        free(old_tail); /* stub left the chain alone: free the three nodes */
        free(old_head->next);
        free(old_head);
    }

    CASE("NULL");
    IS_NULL(list_reverse(NULL));

    CASE("single node");
    IntNode one = {7, NULL};
    IntNode *r = list_reverse(&one);
    POINTER(&one, r);
    IS_NULL(one.next);
    one.next = NULL;

    CASE("two nodes: nodes keep their addresses");
    IntNode b = {2, NULL}, a = {1, &b};
    r = list_reverse(&a);
    POINTER(&b, r);
    POINTER(&a, b.next);
    IS_NULL(a.next);
    a.next = NULL; /* reset so nothing dangles whatever the result was */
    b.next = NULL;

    CASE("reverse twice restores the original order");
    int v[] = {5, 4, 3, 2, 1, 0};
    head = make_chain(v, 6);
    IntNode *original = head;
    head = list_reverse(list_reverse(head));
    if (!head) head = original; /* stub returns NULL; still free the nodes */
    bool same = true;
    size_t i = 0;
    for (const IntNode *n = head; n; n = n->next, ++i)
        if (i >= 6 || n->value != v[i]) same = false;
    TRUE(same && i == 6);
    free_chain(head);
}

#elif EXERCISE == 73
void run_tests(void) {
    CASE("1 -> 2 -> 3 -> NULL");
    IntNode c = {3, NULL}, b = {2, &c}, a = {1, &b};
    FALSE(list_has_cycle(&a));

    CASE("1 -> 2 -> 3 -> back to 1");
    c.next = &a;
    TRUE(list_has_cycle(&a));
    c.next = NULL; /* break the cycle */

    CASE("cycle into the middle: 1 -> 2 -> 3 -> 4 -> back to 2");
    IntNode d = {4, NULL};
    c.next = &d;
    d.next = &b;
    TRUE(list_has_cycle(&a));
    d.next = NULL;
    c.next = NULL;

    CASE("single node to itself, and single node to NULL");
    IntNode self = {9, NULL};
    FALSE(list_has_cycle(&self));
    self.next = &self;
    TRUE(list_has_cycle(&self));
    self.next = NULL;

    CASE("NULL and even/odd length straight lists");
    FALSE(list_has_cycle(NULL));
    IntNode two_b = {2, NULL}, two_a = {1, &two_b};
    FALSE(list_has_cycle(&two_a));
    FALSE(list_has_cycle(&two_b));
}

#elif EXERCISE == 74
static void free_chain(IntNode *head) {
    while (head) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}
static IntNode *make_chain(const int *values, size_t count) {
    IntNode *head = NULL, **link = &head;
    for (size_t i = 0; i < count; ++i) {
        IntNode *n = malloc(sizeof *n);
        if (!n) break;
        n->value = values[i];
        n->next = NULL;
        *link = n;
        link = &n->next;
    }
    return head;
}
static bool values_are(const IntNode *head, const int *expected, size_t count) {
    size_t i = 0;
    for (; head; head = head->next, ++i)
        if (i >= count || head->value != expected[i]) return false;
    return i == count;
}

void run_tests(void) {
    CASE("1->3->5 + 2->4");
    int va[] = {1, 3, 5}, vb[] = {2, 4};
    IntNode *a = make_chain(va, 3), *b = make_chain(vb, 2);
    IntNode *a_first = a, *b_first = b;
    IntNode *m = list_merge_sorted(a, b);
    int expected[] = {1, 2, 3, 4, 5};
    TRUE(values_are(m, expected, 5));
    POINTER(a_first, m);             /* same node, not a copy */
    if (m) {
        POINTER(b_first, m->next);
        free_chain(m);
    } else {
        free_chain(a_first); /* stub returned NULL: inputs are untouched */
        free_chain(b_first);
    }

    CASE("NULL + 7->9 and 7->9 + NULL return the same nodes");
    int v79[] = {7, 9};
    b = make_chain(v79, 2);
    POINTER(b, list_merge_sorted(NULL, b));
    POINTER(b, list_merge_sorted(b, NULL));
    TRUE(values_are(b, v79, 2));
    free_chain(b);

    CASE("NULL + NULL");
    IS_NULL(list_merge_sorted(NULL, NULL));

    CASE("stable on ties: a's nodes before b's");
    IntNode a2 = {1, NULL}, a1 = {1, &a2};
    IntNode b1 = {1, NULL};
    m = list_merge_sorted(&a1, &b1);
    POINTER(&a1, m);
    if (m) {
        POINTER(&a2, m->next);
        if (m->next) POINTER(&b1, m->next->next);
    }
    IS_NULL(b1.next);

    CASE("one list entirely before the other");
    int lo[] = {1, 2, 3}, hi[] = {10, 20};
    a = make_chain(lo, 3);
    b = make_chain(hi, 2);
    IntNode *lo_head = a, *hi_head = b;
    m = list_merge_sorted(b, a); /* b is the one with larger values */
    int expected2[] = {1, 2, 3, 10, 20};
    TRUE(values_are(m, expected2, 5));
    if (m) free_chain(m);
    else {
        free_chain(lo_head);
        free_chain(hi_head);
    }
}

#elif EXERCISE == 75
void run_tests(void) {
    CASE("hash_djb2 known values");
    UINT(5381u, hash_djb2(""));
    UINT(177670u, hash_djb2("a"));
    UINT(5863208u, hash_djb2("ab"));
    UINT(hash_djb2("hello"), hash_djb2("hello"));
    TRUE(hash_djb2("hello") != hash_djb2("hellp"));

    CASE("put two keys, get hits and a miss");
    HashMap m = {0};
    int v = -1;
    INT(0, hashmap_put(&m, "one", 1));
    INT(0, hashmap_put(&m, "two", 2));
    UINT(2, m.count);
    TRUE(hashmap_get(&m, "one", &v));
    INT(1, v);
    TRUE(hashmap_get(&m, "two", &v));
    INT(2, v);
    v = -1;
    FALSE(hashmap_get(&m, "three", &v));
    INT(-1, v);

    CASE("put existing key updates the value, count unchanged");
    INT(0, hashmap_put(&m, "one", 100));
    UINT(2, m.count);
    TRUE(hashmap_get(&m, "one", &v));
    INT(100, v);
    hashmap_free(&m);
    UINT(0, m.count);
    FALSE(hashmap_get(&m, "one", &v));

    CASE("key is copied, not aliased");
    HashMap k = {0};
    char buffer[8] = "abc";
    INT(0, hashmap_put(&k, buffer, 5));
    strcpy(buffer, "zzz");
    TRUE(hashmap_get(&k, "abc", &v));
    INT(5, v);
    FALSE(hashmap_get(&k, "zzz", &v));
    hashmap_free(&k);

    CASE("200 keys force collisions in 64 buckets");
    HashMap big = {0};
    char key[16];
    int failures = 0;
    for (int i = 0; i < 200; ++i) {
        snprintf(key, sizeof key, "k%d", i);
        failures += hashmap_put(&big, key, i * 3) != 0;
    }
    INT(0, failures);
    UINT(200, big.count);
    int wrong = 0;
    for (int i = 0; i < 200; ++i) {
        snprintf(key, sizeof key, "k%d", i);
        if (!hashmap_get(&big, key, &v) || v != i * 3) ++wrong;
    }
    INT(0, wrong);
    FALSE(hashmap_get(&big, "k200", &v));
    hashmap_free(&big);

    CASE("empty-string key and get on an empty map");
    HashMap e = {0};
    FALSE(hashmap_get(&e, "x", &v));
    INT(0, hashmap_put(&e, "", 9));
    TRUE(hashmap_get(&e, "", &v));
    INT(9, v);
    hashmap_free(&e);
}

#elif EXERCISE == 76
void run_tests(void) {
    CASE("insert 5, 3, 8, 1, 4");
    TreeNode *root = NULL;
    int values[] = {5, 3, 8, 1, 4};
    int inserted = 0;
    for (size_t i = 0; i < 5; ++i) inserted += bst_insert(&root, values[i]) == 0;
    INT(5, inserted);
    NOT_NULL(root);
    TRUE(bst_contains(root, 4));
    TRUE(bst_contains(root, 1));
    TRUE(bst_contains(root, 8));
    FALSE(bst_contains(root, 7));
    FALSE(bst_contains(root, 0));

    CASE("structure: root 5, left 3, right 8, 3's children 1 and 4");
    if (root) {
        INT(5, root->value);
        NOT_NULL(root->left);
        NOT_NULL(root->right);
        if (root->left && root->right) {
            INT(3, root->left->value);
            INT(8, root->right->value);
            if (root->left->left) INT(1, root->left->left->value);
            if (root->left->right) INT(4, root->left->right->value);
            IS_NULL(root->right->left);
            IS_NULL(root->right->right);
        }
    }

    CASE("duplicate insert returns 1 and changes nothing");
    INT(1, bst_insert(&root, 3));
    INT(1, bst_insert(&root, 5));
    if (root && root->left) IS_NULL(root->left->left ? root->left->left->left : NULL);
    bst_free(root);

    CASE("empty tree: contains false, free(NULL)");
    FALSE(bst_contains(NULL, 1));
    bst_free(NULL);
    TRUE(true);

    CASE("sorted input forms a chain; INT_MIN and INT_MAX");
    root = NULL;
    INT(0, bst_insert(&root, INT_MIN));
    INT(0, bst_insert(&root, 0));
    INT(0, bst_insert(&root, INT_MAX));
    TRUE(bst_contains(root, INT_MIN));
    TRUE(bst_contains(root, INT_MAX));
    FALSE(bst_contains(root, 1));
    if (root) {
        IS_NULL(root->left);
        NOT_NULL(root->right);
    }
    bst_free(root);
}

#elif EXERCISE == 77
void run_tests(void) {
    /* 5(3(1, 4), 8) */
    TreeNode n1 = {1, NULL, NULL}, n4 = {4, NULL, NULL}, n8 = {8, NULL, NULL};
    TreeNode n3 = {3, &n1, &n4}, n5 = {5, &n3, &n8};

    CASE("height of 5(3(1,4),8), a leaf, and NULL");
    UINT(3, bst_height(&n5));
    UINT(1, bst_height(&n8));
    UINT(0, bst_height(NULL));

    CASE("right-leaning chain 1 -> 2 -> 3");
    TreeNode c3 = {3, NULL, NULL}, c2 = {2, NULL, &c3}, c1 = {1, NULL, &c2};
    UINT(3, bst_height(&c1));
    UINT(2, bst_height(&c2));

    CASE("in-order traversal with enough capacity");
    int out[8] = {0};
    UINT(5, bst_to_sorted_array(&n5, out, 8));
    int expected[] = {1, 3, 4, 5, 8};
    ARRAY(expected, out, 5);
    INT(0, out[5]); /* nothing written past the count */

    CASE("capacity 3 truncates and returns 3");
    int small[3] = {-1, -1, -1};
    UINT(3, bst_to_sorted_array(&n5, small, 3));
    int expected3[] = {1, 3, 4};
    ARRAY(expected3, small, 3);

    CASE("capacity 0, NULL tree, exact capacity");
    int guard[2] = {99, 99};
    UINT(0, bst_to_sorted_array(&n5, guard, 0));
    INT(99, guard[0]);
    UINT(0, bst_to_sorted_array(NULL, guard, 2));
    INT(99, guard[0]);
    int exact[5];
    UINT(5, bst_to_sorted_array(&n5, exact, 5));
    ARRAY(expected, exact, 5);
}

#elif EXERCISE == 78
void run_tests(void) {
    CASE("push 5, 3, 8, 1 then pop all");
    MinHeap h = {0};
    int v = -1;
    INT(0, heap_push(&h, 5));
    INT(0, heap_push(&h, 3));
    INT(0, heap_push(&h, 8));
    INT(0, heap_push(&h, 1));
    UINT(4, h.count);
    INT(1, h.items[0]);
    INT(0, heap_pop(&h, &v));
    INT(1, v);
    INT(0, heap_pop(&h, &v));
    INT(3, v);
    INT(0, heap_pop(&h, &v));
    INT(5, v);
    INT(0, heap_pop(&h, &v));
    INT(8, v);
    INT(-1, heap_pop(&h, &v));
    INT(8, v);

    CASE("pop on empty leaves *out alone");
    MinHeap e = {0};
    v = 42;
    INT(-1, heap_pop(&e, &v));
    INT(42, v);

    CASE("right child smaller than left (sift-down must pick the smaller child)");
    MinHeap r = {0};
    int seq[] = {1, 10, 2, 11, 12, 3};
    for (size_t i = 0; i < 6; ++i) heap_push(&r, seq[i]);
    bool ordered = true;
    int previous = INT_MIN;
    while (heap_pop(&r, &v) == 0) {
        if (v < previous) ordered = false;
        previous = v;
    }
    TRUE(ordered);
    INT(12, previous);

    CASE("duplicates {2, 2, 1, 2}");
    MinHeap d = {0};
    heap_push(&d, 2);
    heap_push(&d, 2);
    heap_push(&d, 1);
    heap_push(&d, 2);
    int got[4];
    for (size_t i = 0; i < 4; ++i) heap_pop(&d, &got[i]);
    int expected[] = {1, 2, 2, 2};
    ARRAY(expected, got, 4);

    CASE("64 pushes succeed, the 65th fails; everything comes out sorted");
    MinHeap full = {0};
    unsigned seed = 7u;
    int ok = 0;
    for (int i = 0; i < 64; ++i) {
        seed = seed * 1103515245u + 12345u;
        ok += heap_push(&full, (int)(seed >> 16) % 1000 - 500) == 0;
    }
    INT(64, ok);
    INT(-1, heap_push(&full, 0));
    UINT(64, full.count);
    ordered = true;
    previous = INT_MIN;
    size_t popped = 0;
    while (heap_pop(&full, &v) == 0) {
        if (v < previous) ordered = false;
        previous = v;
        ++popped;
    }
    TRUE(ordered);
    UINT(64, popped);

    CASE("INT_MIN and INT_MAX");
    MinHeap x = {0};
    heap_push(&x, INT_MAX);
    heap_push(&x, 0);
    heap_push(&x, INT_MIN);
    heap_pop(&x, &v);
    INT(INT_MIN, v);
    heap_pop(&x, &v);
    INT(0, v);
    heap_pop(&x, &v);
    INT(INT_MAX, v);
}

#elif EXERCISE == 79
void run_tests(void) {
    CASE("capacity 2: put 1, put 2, get 1, put 3 evicts 2");
    LruCache c = {99, 99, NULL, NULL};
    lru_init(&c, 2);
    UINT(2, c.capacity);
    UINT(0, c.count);
    int v = -1;
    INT(0, lru_put(&c, 1, 1));
    INT(0, lru_put(&c, 2, 2));
    UINT(2, c.count);
    TRUE(lru_get(&c, 1, &v));
    INT(1, v);
    INT(0, lru_put(&c, 3, 3));
    UINT(2, c.count);
    v = -1;
    FALSE(lru_get(&c, 2, &v));
    INT(-1, v);
    TRUE(lru_get(&c, 3, &v));
    INT(3, v);
    TRUE(lru_get(&c, 1, &v));
    INT(1, v);

    CASE("put on an existing key updates in place and refreshes it");
    INT(0, lru_put(&c, 1, 10));
    UINT(2, c.count);
    TRUE(lru_get(&c, 1, &v));
    INT(10, v);
    /* order is now 1 (front), 3 (tail): putting 4 must evict 3 */
    INT(0, lru_put(&c, 4, 4));
    FALSE(lru_get(&c, 3, &v));
    TRUE(lru_get(&c, 1, &v));
    TRUE(lru_get(&c, 4, &v));
    lru_free(&c);
    UINT(0, c.count);
    IS_NULL(c.head);
    IS_NULL(c.tail);

    CASE("a miss does not reorder: eviction still hits the real tail");
    LruCache m = {0};
    lru_init(&m, 2);
    lru_put(&m, 1, 1);
    lru_put(&m, 2, 2); /* order: 2, 1 */
    FALSE(lru_get(&m, 99, &v));
    NOT_NULL(m.head);
    NOT_NULL(m.tail);
    if (m.head && m.tail) {
        INT(2, m.head->key);
        INT(1, m.tail->key);
    }
    lru_put(&m, 3, 3); /* evicts 1 */
    FALSE(lru_get(&m, 1, &v));
    TRUE(lru_get(&m, 2, &v));
    lru_free(&m);

    CASE("capacity 1");
    LruCache one = {0};
    lru_init(&one, 1);
    lru_put(&one, 5, 50);
    lru_put(&one, 6, 60);
    UINT(1, one.count);
    FALSE(lru_get(&one, 5, &v));
    TRUE(lru_get(&one, 6, &v));
    INT(60, v);
    POINTER(one.head, one.tail);
    lru_free(&one);

    CASE("get on an empty cache; free on an empty cache; list links stay consistent");
    LruCache e = {0};
    lru_init(&e, 3);
    FALSE(lru_get(&e, 1, &v));
    lru_free(&e);
    lru_init(&e, 3);
    for (int i = 0; i < 10; ++i) lru_put(&e, i, i * i);
    UINT(3, e.count);
    bool links_ok = e.head && e.tail && e.head->prev == NULL && e.tail->next == NULL;
    NOT_NULL(e.head);
    size_t forward = 0;
    for (LruNode *n = e.head; n; n = n->next) {
        if (n->next && n->next->prev != n) links_ok = false;
        ++forward;
    }
    UINT(3, forward);
    TRUE(links_ok);
    TRUE(lru_get(&e, 9, &v));
    INT(81, v);
    TRUE(lru_get(&e, 7, &v)); /* 7 moves to the front, 8 becomes tail */
    if (e.tail) INT(8, e.tail->key);
    lru_free(&e);
}
#endif
