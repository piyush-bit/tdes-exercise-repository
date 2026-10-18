#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[FAIL] %s: Expected %d, got %d\n", msg, (int)(expected), (int)(actual)); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "[FAIL] %s: Expected non-NULL pointer\n", msg); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

#define ASSERT_NULL(ptr, msg) \
    do { \
        if ((ptr) != NULL) { \
            fprintf(stderr, "[FAIL] %s: Expected NULL pointer\n", msg); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

void test_public_create_and_insert(void) {
    printf("--- Running Public Create & Insert Test ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    ASSERT_NOT_NULL(root, "bst_insert creates root when inserting into empty tree");
    if (root) {
        ASSERT_EQ(root->data, 50, "root data is 50");
    }

    root = bst_insert(root, 30);
    root = bst_insert(root, 70);
    ASSERT_NOT_NULL(root->left, "left child created for 30");
    if (root->left) {
        ASSERT_EQ(root->left->data, 30, "left child data is 30");
    }
    ASSERT_NOT_NULL(root->right, "right child created for 70");
    if (root->right) {
        ASSERT_EQ(root->right->data, 70, "right child data is 70");
    }

    free_tree(root);
}

void test_public_search(void) {
    printf("--- Running Public Search Test ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = bst_insert(root, values[i]);
    }

    TreeNode *found = bst_search(root, 40);
    ASSERT_NOT_NULL(found, "bst_search finds existing node 40");
    if (found) {
        ASSERT_EQ(found->data, 40, "searched node data is 40");
    }

    TreeNode *not_found = bst_search(root, 99);
    ASSERT_NULL(not_found, "bst_search returns NULL for absent value 99");

    free_tree(root);
}

void test_public_traversals(void) {
    printf("--- Running Public Traversals Test ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++) {
        root = bst_insert(root, values[i]);
    }

    int in_arr[10] = {0};
    int in_idx = 0;
    inorder_traversal(root, in_arr, &in_idx);
    ASSERT_EQ(in_idx, 5, "inorder_traversal visits 5 nodes");
    ASSERT_EQ(in_arr[0], 20, "inorder [0] == 20");
    ASSERT_EQ(in_arr[1], 30, "inorder [1] == 30");
    ASSERT_EQ(in_arr[2], 40, "inorder [2] == 40");
    ASSERT_EQ(in_arr[3], 50, "inorder [3] == 50");
    ASSERT_EQ(in_arr[4], 70, "inorder [4] == 70");

    free_tree(root);
}

void test_public_deletion(void) {
    printf("--- Running Public Deletion Test ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++) {
        root = bst_insert(root, values[i]);
    }

    root = bst_delete(root, 20);
    TreeNode *found = bst_search(root, 20);
    ASSERT_NULL(found, "bst_delete removes leaf node 20");

    int in_arr[10] = {0};
    int in_idx = 0;
    inorder_traversal(root, in_arr, &in_idx);
    ASSERT_EQ(in_idx, 4, "inorder_traversal size after deletion is 4");
    ASSERT_EQ(in_arr[0], 30, "inorder [0] after deletion is 30");

    free_tree(root);
}

int main(void) {
    test_public_create_and_insert();
    test_public_search();
    test_public_traversals();
    test_public_deletion();

    if (failed) {
        fprintf(stderr, "\nPublic tests failed!\n");
        return 1;
    }

    printf("\nAll Public Tests Passed Successfully!\n");
    return 0;
}
