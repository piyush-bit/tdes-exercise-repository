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

void test_null_traversals(void) {
    printf("--- Private Test: NULL Traversals ---\n");
    int arr[5] = {-1, -1, -1, -1, -1};
    int idx = 0;

    inorder_traversal(NULL, arr, &idx);
    ASSERT_EQ(idx, 0, "inorder on NULL tree keeps index 0");

    preorder_traversal(NULL, arr, &idx);
    ASSERT_EQ(idx, 0, "preorder on NULL tree keeps index 0");

    postorder_traversal(NULL, arr, &idx);
    ASSERT_EQ(idx, 0, "postorder on NULL tree keeps index 0");

    TreeNode *node = create_node(10);
    inorder_traversal(node, NULL, &idx);
    ASSERT_EQ(idx, 0, "inorder with NULL arr does not modify index");

    inorder_traversal(node, arr, NULL);
    ASSERT_EQ(arr[0], -1, "inorder with NULL index does not crash or write");

    free_tree(node);
}

void test_single_node_traversal(void) {
    printf("--- Private Test: Single Node Traversal ---\n");
    TreeNode *root = create_node(42);

    int in_arr[5] = {0}, pre_arr[5] = {0}, post_arr[5] = {0};
    int in_idx = 0, pre_idx = 0, post_idx = 0;

    inorder_traversal(root, in_arr, &in_idx);
    preorder_traversal(root, pre_arr, &pre_idx);
    postorder_traversal(root, post_arr, &post_idx);

    ASSERT_EQ(in_idx, 1, "inorder index is 1 for single node");
    ASSERT_EQ(in_arr[0], 42, "inorder element is 42");

    ASSERT_EQ(pre_idx, 1, "preorder index is 1 for single node");
    ASSERT_EQ(pre_arr[0], 42, "preorder element is 42");

    ASSERT_EQ(post_idx, 1, "postorder index is 1 for single node");
    ASSERT_EQ(post_arr[0], 42, "postorder element is 42");

    free_tree(root);
}

void test_full_bst_traversals(void) {
    printf("--- Private Test: Full BST Traversals ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = bst_insert(root, values[i]);
    }

    int in_arr[10] = {0}, in_idx = 0;
    inorder_traversal(root, in_arr, &in_idx);
    ASSERT_EQ(in_idx, 7, "inorder visits 7 nodes");
    int expected_in[] = {20, 30, 40, 50, 60, 70, 80};
    for (int i = 0; i < 7; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "inorder_traversal element [%d]", i);
        ASSERT_EQ(in_arr[i], expected_in[i], msg);
    }

    int pre_arr[10] = {0}, pre_idx = 0;
    preorder_traversal(root, pre_arr, &pre_idx);
    ASSERT_EQ(pre_idx, 7, "preorder visits 7 nodes");
    int expected_pre[] = {50, 30, 20, 40, 70, 60, 80};
    for (int i = 0; i < 7; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "preorder_traversal element [%d]", i);
        ASSERT_EQ(pre_arr[i], expected_pre[i], msg);
    }

    int post_arr[10] = {0}, post_idx = 0;
    postorder_traversal(root, post_arr, &post_idx);
    ASSERT_EQ(post_idx, 7, "postorder visits 7 nodes");
    int expected_post[] = {20, 40, 30, 60, 80, 70, 50};
    for (int i = 0; i < 7; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "postorder_traversal element [%d]", i);
        ASSERT_EQ(post_arr[i], expected_post[i], msg);
    }

    free_tree(root);
}

void test_skewed_traversals(void) {
    printf("--- Private Test: Skewed Tree Traversals ---\n");
    // Left-skewed tree: 30 -> 20 -> 10
    TreeNode *left_tree = NULL;
    left_tree = bst_insert(left_tree, 30);
    left_tree = bst_insert(left_tree, 20);
    left_tree = bst_insert(left_tree, 10);

    int in_arr[5] = {0}, in_idx = 0;
    inorder_traversal(left_tree, in_arr, &in_idx);
    ASSERT_EQ(in_arr[0], 10, "left-skewed inorder [0]");
    ASSERT_EQ(in_arr[1], 20, "left-skewed inorder [1]");
    ASSERT_EQ(in_arr[2], 30, "left-skewed inorder [2]");

    int pre_arr[5] = {0}, pre_idx = 0;
    preorder_traversal(left_tree, pre_arr, &pre_idx);
    ASSERT_EQ(pre_arr[0], 30, "left-skewed preorder [0]");
    ASSERT_EQ(pre_arr[1], 20, "left-skewed preorder [1]");
    ASSERT_EQ(pre_arr[2], 10, "left-skewed preorder [2]");

    free_tree(left_tree);

    // Right-skewed tree: 10 -> 20 -> 30
    TreeNode *right_tree = NULL;
    right_tree = bst_insert(right_tree, 10);
    right_tree = bst_insert(right_tree, 20);
    right_tree = bst_insert(right_tree, 30);

    int post_arr[5] = {0}, post_idx = 0;
    postorder_traversal(right_tree, post_arr, &post_idx);
    ASSERT_EQ(post_arr[0], 30, "right-skewed postorder [0]");
    ASSERT_EQ(post_arr[1], 20, "right-skewed postorder [1]");
    ASSERT_EQ(post_arr[2], 10, "right-skewed postorder [2]");

    free_tree(right_tree);
}

int main(void) {
    test_null_traversals();
    test_single_node_traversal();
    test_full_bst_traversals();
    test_skewed_traversals();

    if (failed) {
        fprintf(stderr, "\nPrivate Traversals Tests Failed!\n");
        return 1;
    }

    printf("\nAll Private Traversals Tests Passed!\n");
    return 0;
}
