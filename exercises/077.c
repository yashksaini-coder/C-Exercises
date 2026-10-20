#include "exercises.h"
#include "lib.h"

/* Nodes on the longest root-to-leaf path; NULL is 0. */
size_t bst_height(const TreeNode *root) {
    (void)root;
    /* TODO: implement. */
    return 0;
}

/* In-order traversal into out, at most capacity values; returns the number written. */
size_t bst_to_sorted_array(const TreeNode *root, int *out, size_t capacity) {
    (void)root;
    (void)out;
    (void)capacity;
    /* TODO: implement (a static helper carrying a size_t *written is the usual shape). */
    return 0;
}

#ifndef EXERCISE_TEST
int main(void) {
    TreeNode n1 = {1, NULL, NULL}, n4 = {4, NULL, NULL}, n8 = {8, NULL, NULL};
    TreeNode n3 = {3, &n1, &n4}, n5 = {5, &n3, &n8};
    int sorted[8];
    size_t n = bst_to_sorted_array(&n5, sorted, 8);
    printf("height %zu, sorted:", bst_height(&n5));
    for (size_t i = 0; i < n; ++i) printf(" %d", sorted[i]);
    putchar('\n');
    return 0;
}
#endif
