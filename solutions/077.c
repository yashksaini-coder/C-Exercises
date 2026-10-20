#include "exercises.h"
#include "lib.h"

size_t bst_height(const TreeNode *root) {
    if (!root) return 0;
    size_t left = bst_height(root->left), right = bst_height(root->right);
    return 1 + (left > right ? left : right);
}

static void in_order(const TreeNode *node, int *out, size_t capacity, size_t *written) {
    if (!node || *written >= capacity) return;
    in_order(node->left, out, capacity, written);
    if (*written < capacity) out[(*written)++] = node->value;
    in_order(node->right, out, capacity, written);
}

size_t bst_to_sorted_array(const TreeNode *root, int *out, size_t capacity) {
    size_t written = 0;
    in_order(root, out, capacity, &written);
    return written;
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
