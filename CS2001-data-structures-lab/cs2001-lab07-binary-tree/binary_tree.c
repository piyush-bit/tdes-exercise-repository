#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode* create_node(int data) {
    // TODO: Allocate memory for a new TreeNode, set its data, set left and right to NULL, and return it.
    (void)data;
    return NULL;
}

TreeNode* bst_insert(TreeNode *root, int data) {
    // TODO: Insert data into the BST maintaining BST property. Ignore duplicates. Return the updated root.
    (void)root;
    (void)data;
    return NULL;
}

TreeNode* bst_search(TreeNode *root, int data) {
    // TODO: Search for data in the BST. Return pointer to matching node, or NULL if not found.
    (void)root;
    (void)data;
    return NULL;
}

TreeNode* bst_delete(TreeNode *root, int data) {
    // TODO: Delete node containing data from BST using in-order successor for 2-child nodes. Return updated root.
    (void)root;
    (void)data;
    return NULL;
}

void inorder_traversal(TreeNode *root, int *arr, int *index) {
    // TODO: Perform in-order traversal (Left, Root, Right). Append values to arr[*index] and increment *index.
    (void)root;
    (void)arr;
    (void)index;
}

void preorder_traversal(TreeNode *root, int *arr, int *index) {
    // TODO: Perform pre-order traversal (Root, Left, Right). Append values to arr[*index] and increment *index.
    (void)root;
    (void)arr;
    (void)index;
}

void postorder_traversal(TreeNode *root, int *arr, int *index) {
    // TODO: Perform post-order traversal (Left, Right, Root). Append values to arr[*index] and increment *index.
    (void)root;
    (void)arr;
    (void)index;
}

void free_tree(TreeNode *root) {
    // TODO: Recursively free all nodes in the tree using post-order cleanup.
    (void)root;
}
