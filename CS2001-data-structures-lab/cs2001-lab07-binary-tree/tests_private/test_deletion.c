#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

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

void test_delete_null_and_nonexistent(void) {
    printf("--- Private Test: Delete NULL & Non-existent ---\n");
    TreeNode *res = bst_delete(NULL, 10);
    ASSERT_NULL(res, "bst_delete on NULL tree returns NULL");

    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 70);

    root = bst_delete(root, 100); // Non-existent
    int in_arr[5] = {0}, idx = 0;
    inorder_traversal(root, in_arr, &idx);
    ASSERT_EQ(idx, 3, "deleting non-existent value keeps node count 3");
    ASSERT_EQ(in_arr[0], 30, "inorder [0] unchanged");
    ASSERT_EQ(in_arr[1], 50, "inorder [1] unchanged");
    ASSERT_EQ(in_arr[2], 70, "inorder [2] unchanged");

    free_tree(root);
}

void test_delete_leaf(void) {
    printf("--- Private Test: Delete Leaf Node (0 Children) ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 70);
    root = bst_insert(root, 20);

    root = bst_delete(root, 20);
    ASSERT_NULL(bst_search(root, 20), "leaf 20 deleted");
    ASSERT_NULL(root->left->left, "node 30 left child becomes NULL");

    int in_arr[5] = {0}, idx = 0;
    inorder_traversal(root, in_arr, &idx);
    ASSERT_EQ(idx, 3, "traversal count after leaf deletion is 3");

    free_tree(root);
}

void test_delete_one_child(void) {
    printf("--- Private Test: Delete Node with 1 Child ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 20); // 30 has left child 20 only

    root = bst_delete(root, 30);
    ASSERT_NULL(bst_search(root, 30), "node 30 deleted");
    ASSERT_NOT_NULL(root->left, "root left updated to 20");
    if (root->left) {
        ASSERT_EQ(root->left->data, 20, "root left child data is 20");
    }

    free_tree(root);
}

void test_delete_two_children(void) {
    printf("--- Private Test: Delete Node with 2 Children ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    for (int i = 0; i < 9; i++) {
        root = bst_insert(root, values[i]);
    }

    // Delete node 30 (has left child 20 and right subtree with min 35)
    root = bst_delete(root, 30);
    ASSERT_NULL(bst_search(root, 30), "node 30 deleted");

    int in_arr[10] = {0}, idx = 0;
    inorder_traversal(root, in_arr, &idx);
    ASSERT_EQ(idx, 8, "traversal count after deleting 2-child node is 8");

    int expected[] = {20, 35, 40, 45, 50, 60, 70, 80};
    for (int i = 0; i < 8; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "inorder array element [%d] after 2-child deletion", i);
        ASSERT_EQ(in_arr[i], expected[i], msg);
    }

    // Delete root 50 (has two children)
    root = bst_delete(root, 50);
    ASSERT_NULL(bst_search(root, 50), "root 50 deleted");
    ASSERT_EQ(root->data, 60, "new root is 60 (in-order successor of 50)");

    idx = 0;
    inorder_traversal(root, in_arr, &idx);
    ASSERT_EQ(idx, 7, "traversal count after root deletion is 7");

    free_tree(root);
}

void test_delete_sequential_until_empty(void) {
    printf("--- Private Test: Sequential Deletion Until Empty ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 10);
    root = bst_insert(root, 5);
    root = bst_insert(root, 15);

    root = bst_delete(root, 10);
    root = bst_delete(root, 5);
    root = bst_delete(root, 15);

    ASSERT_NULL(root, "tree becomes NULL after deleting all elements");
}

int main(void) {
    test_delete_null_and_nonexistent();
    test_delete_leaf();
    test_delete_one_child();
    test_delete_two_children();
    test_delete_sequential_until_empty();

    if (failed) {
        fprintf(stderr, "\nPrivate Deletion Tests Failed!\n");
        return 1;
    }

    printf("\nAll Private Deletion Tests Passed!\n");
    return 0;
}
