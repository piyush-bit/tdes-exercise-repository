#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stddef.h>

/**
 * Node structure for a Binary Tree / Binary Search Tree (BST).
 */
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/**
 * Creates and initializes a new tree node with the given integer value.
 *
 * @param data Integer value to store in the node.
 * @return Pointer to newly allocated TreeNode, or NULL if memory allocation fails.
 */
TreeNode* create_node(int data);

/**
 * Inserts a value into a Binary Search Tree (BST).
 * Follows standard BST property (left < root < right). Duplicate values are ignored.
 *
 * @param root Pointer to the root node of the BST.
 * @param data Integer value to insert.
 * @return Pointer to the root of the updated tree.
 */
TreeNode* bst_insert(TreeNode *root, int data);

/**
 * Deletes a node containing the specified value from a Binary Search Tree (BST).
 * For nodes with two children, the node value is replaced with its in-order successor
 * (minimum node in the right subtree), and the successor node is removed.
 *
 * @param root Pointer to the root node of the BST.
 * @param data Integer value to delete.
 * @return Pointer to the root of the updated tree.
 */
TreeNode* bst_delete(TreeNode *root, int data);

/**
 * Searches for a node containing the specified value in a Binary Search Tree (BST).
 *
 * @param root Pointer to the root node of the BST.
 * @param data Integer value to search for.
 * @return Pointer to the TreeNode containing data if found, or NULL if not found / root is NULL.
 */
TreeNode* bst_search(TreeNode *root, int data);

/**
 * Performs an in-order traversal (Left -> Root -> Right) of the tree.
 * Stores visited node values into 'arr' starting at index '*index', incrementing '*index' for each element.
 *
 * @param root Pointer to the root of the tree.
 * @param arr Output array to receive visited node values.
 * @param index Pointer to the current output index (updated during traversal).
 */
void inorder_traversal(TreeNode *root, int *arr, int *index);

/**
 * Performs a pre-order traversal (Root -> Left -> Right) of the tree.
 * Stores visited node values into 'arr' starting at index '*index', incrementing '*index' for each element.
 *
 * @param root Pointer to the root of the tree.
 * @param arr Output array to receive visited node values.
 * @param index Pointer to the current output index (updated during traversal).
 */
void preorder_traversal(TreeNode *root, int *arr, int *index);

/**
 * Performs a post-order traversal (Left -> Right -> Root) of the tree.
 * Stores visited node values into 'arr' starting at index '*index', incrementing '*index' for each element.
 *
 * @param root Pointer to the root of the tree.
 * @param arr Output array to receive visited node values.
 * @param index Pointer to the current output index (updated during traversal).
 */
void postorder_traversal(TreeNode *root, int *arr, int *index);

/**
 * Recursively frees all memory allocated for the tree rooted at 'root'.
 * Safely handles NULL root.
 *
 * @param root Pointer to the root node of the tree to free.
 */
void free_tree(TreeNode *root);

#endif /* BINARY_TREE_H */
