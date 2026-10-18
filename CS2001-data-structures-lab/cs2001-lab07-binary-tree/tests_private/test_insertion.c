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

void test_create_node(void) {
    printf("--- Private Test: create_node ---\n");
    TreeNode *node = create_node(100);
    ASSERT_NOT_NULL(node, "create_node returns valid non-NULL pointer");
    if (node) {
        ASSERT_EQ(node->data, 100, "create_node data is set correctly");
        ASSERT_NULL(node->left, "create_node left child is NULL");
        ASSERT_NULL(node->right, "create_node right child is NULL");
    }
    free_tree(node);
}

void test_bst_insert_structure(void) {
    printf("--- Private Test: bst_insert Structure & Order ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    ASSERT_NOT_NULL(root, "bst_insert into empty tree sets root");
    ASSERT_EQ(root->data, 50, "root value is 50");

    root = bst_insert(root, 30);
    root = bst_insert(root, 70);
    root = bst_insert(root, 20);
    root = bst_insert(root, 40);
    root = bst_insert(root, 60);
    root = bst_insert(root, 80);

    ASSERT_EQ(root->left->data, 30, "root->left is 30");
    ASSERT_EQ(root->right->data, 70, "root->right is 70");
    ASSERT_EQ(root->left->left->data, 20, "root->left->left is 20");
    ASSERT_EQ(root->left->right->data, 40, "root->left->right is 40");
    ASSERT_EQ(root->right->left->data, 60, "root->right->left is 60");
    ASSERT_EQ(root->right->right->data, 80, "root->right->right is 80");

    free_tree(root);
}

void test_bst_insert_duplicates(void) {
    printf("--- Private Test: bst_insert Duplicates ---\n");
    TreeNode *root = NULL;
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 70);

    // Insert duplicate values
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 70);

    int in_arr[10] = {0}, in_idx = 0;
    inorder_traversal(root, in_arr, &in_idx);
    ASSERT_EQ(in_idx, 3, "duplicate insertions do not increase tree node count");
    ASSERT_EQ(in_arr[0], 30, "inorder [0] is 30");
    ASSERT_EQ(in_arr[1], 50, "inorder [1] is 50");
    ASSERT_EQ(in_arr[2], 70, "inorder [2] is 70");

    free_tree(root);
}

void test_bst_search(void) {
    printf("--- Private Test: bst_search ---\n");
    TreeNode *null_res = bst_search(NULL, 10);
    ASSERT_NULL(null_res, "bst_search on NULL root returns NULL");

    TreeNode *root = NULL;
    int values[] = {45, 15, 75, 10, 25, 65, 90};
    for (int i = 0; i < 7; i++) {
        root = bst_insert(root, values[i]);
    }

    TreeNode *res = bst_search(root, 45);
    ASSERT_NOT_NULL(res, "bst_search finds root value 45");
    if (res) ASSERT_EQ(res->data, 45, "node value is 45");

    res = bst_search(root, 10);
    ASSERT_NOT_NULL(res, "bst_search finds leaf value 10");
    if (res) ASSERT_EQ(res->data, 10, "node value is 10");

    res = bst_search(root, 75);
    ASSERT_NOT_NULL(res, "bst_search finds internal node 75");
    if (res) ASSERT_EQ(res->data, 75, "node value is 75");

    res = bst_search(root, 100);
    ASSERT_NULL(res, "bst_search returns NULL for non-existent value 100");

    res = bst_search(root, 5);
    ASSERT_NULL(res, "bst_search returns NULL for non-existent value 5");

    res = bst_search(root, 50);
    ASSERT_NULL(res, "bst_search returns NULL for non-existent value 50");

    free_tree(root);
}

int main(void) {
    test_create_node();
    test_bst_insert_structure();
    test_bst_insert_duplicates();
    test_bst_search();

    if (failed) {
        fprintf(stderr, "\nPrivate Insertion Tests Failed!\n");
        return 1;
    }

    printf("\nAll Private Insertion Tests Passed!\n");
    return 0;
}
