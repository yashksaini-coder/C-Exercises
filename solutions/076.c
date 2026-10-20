#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

int bst_insert(TreeNode **root, int value) {
    TreeNode **link = root; /* the pointer we will eventually overwrite */
    while (*link) {
        if (value == (*link)->value) return 1;
        link = value < (*link)->value ? &(*link)->left : &(*link)->right;
    }
    TreeNode *node = malloc(sizeof *node);
    if (!node) return -1;
    node->value = value;
    node->left = node->right = NULL;
    *link = node;
    return 0;
}

bool bst_contains(const TreeNode *root, int value) {
    while (root) {
        if (value == root->value) return true;
        root = value < root->value ? root->left : root->right;
    }
    return false;
}

void bst_free(TreeNode *root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root); /* children are gone; now the node itself */
}

#ifndef EXERCISE_TEST
int main(void) {
    TreeNode *root = NULL;
    int values[] = {5, 3, 8, 1, 4};
    for (size_t i = 0; i < 5; ++i) bst_insert(&root, values[i]);
    printf("contains 4: %d, contains 7: %d\n", bst_contains(root, 4), bst_contains(root, 7));
    bst_free(root);
    return 0;
}
#endif
