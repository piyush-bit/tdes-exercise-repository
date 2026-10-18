#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode* create_node(int data) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* bst_insert(TreeNode *root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data < root->data) {
        root->left = bst_insert(root->left, data);
    } else if (data > root->data) {
        root->right = bst_insert(root->right, data);
    }
    // Duplicate values are ignored
    return root;
}

TreeNode* bst_search(TreeNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return bst_search(root->left, data);
    } else {
        return bst_search(root->right, data);
    }
}

static TreeNode* find_min(TreeNode *node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode* bst_delete(TreeNode *root, int data) {
    if (root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        root->left = bst_delete(root->left, data);
    } else if (data > root->data) {
        root->right = bst_delete(root->right, data);
    } else {
        // Node to delete found
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: get in-order successor (min in right subtree)
        TreeNode *temp = find_min(root->right);
        root->data = temp->data;
        root->right = bst_delete(root->right, temp->data);
    }
    return root;
}

void inorder_traversal(TreeNode *root, int *arr, int *index) {
    if (root == NULL || arr == NULL || index == NULL) {
        return;
    }
    inorder_traversal(root->left, arr, index);
    arr[(*index)++] = root->data;
    inorder_traversal(root->right, arr, index);
}

void preorder_traversal(TreeNode *root, int *arr, int *index) {
    if (root == NULL || arr == NULL || index == NULL) {
        return;
    }
    arr[(*index)++] = root->data;
    preorder_traversal(root->left, arr, index);
    preorder_traversal(root->right, arr, index);
}

void postorder_traversal(TreeNode *root, int *arr, int *index) {
    if (root == NULL || arr == NULL || index == NULL) {
        return;
    }
    postorder_traversal(root->left, arr, index);
    postorder_traversal(root->right, arr, index);
    arr[(*index)++] = root->data;
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
