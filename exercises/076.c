#include "exercises.h"
#include "lib.h"
#include <stdlib.h>

/* Insert value; 0 inserted, 1 already present, -1 allocation failure. */
int bst_insert(TreeNode **root, int value) {
    (void)root;
    (void)value;
    /* TODO: implement. */
    return -1;
}

/* True if value is in the tree. */
bool bst_contains(const TreeNode *root, int value) {
    (void)root;
    (void)value;
    /* TODO: implement. */
    return false;
}

/* Free every node (post-order). */
void bst_free(TreeNode *root) {
    (void)root;
    /* TODO: implement. */
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
