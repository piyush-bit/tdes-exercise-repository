# CS2001 Lab 07: Binary Tree & Binary Search Tree (BST) Operations in C

## Objectives
In this lab, you will implement core binary tree and binary search tree (BST) operations in C. You will implement tree node creation, BST insertion, searching, deletion (handling 0, 1, and 2 children cases), tree traversals (in-order, pre-order, post-order), and recursive memory deallocation.

---

## Directory & File Structure

- `binary_tree.h`: Header file containing node structure definitions and function prototypes. **Do not modify this file.**
- `binary_tree.c`: Your working file. Implement all functions marked with `// TODO:`.
- `public_test.c`: Public unit test suite for local verification.
- `Makefile`: Build script for running public and submission grading targets.
- `run`: Convenience wrapper script (`./run` or `./run clean`).
- `reference/`: Reference solution directory used by the evaluator during submission grading.
- `tests_private/`: Private test suites evaluated during submission grading.

---

## Data Structure Definition

```c
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
```

---

## API Function Specifications

### 1. Node Creation
```c
TreeNode* create_node(int data);
```
- Allocates memory for a new `TreeNode`.
- Sets `node->data = data`, `node->left = NULL`, and `node->right = NULL`.
- Returns a pointer to the created node, or `NULL` if memory allocation fails.

### 2. BST Insertion
```c
TreeNode* bst_insert(TreeNode *root, int data);
```
- Inserts `data` into the BST rooted at `root` following standard BST order (`left < root < right`).
- If `root` is `NULL`, creates and returns a new node containing `data`.
- If `data` already exists in the tree, ignores insertion (does not insert duplicates) and returns `root`.
- Returns the updated root node of the tree/subtree.

### 3. BST Search
```c
TreeNode* bst_search(TreeNode *root, int data);
```
- Searches for a node with `data` in the BST rooted at `root`.
- Returns a pointer to the matching `TreeNode` if found.
- Returns `NULL` if not found or if `root` is `NULL`.

### 4. BST Deletion
```c
TreeNode* bst_delete(TreeNode *root, int data);
```
- Deletes the node containing `data` from the BST rooted at `root`.
- Handles three deletion cases:
  1. **Leaf node (0 children):** Free node and return `NULL`.
  2. **Node with 1 child:** Free node and return the non-NULL child.
  3. **Node with 2 children:** Replace node's value with its **in-order successor** (the minimum node in the right subtree), then recursively delete the in-order successor from the right subtree.
- If `data` is not present, leaves the tree unchanged.
- Returns the updated root node of the tree/subtree.

### 5. Tree Traversals
```c
void inorder_traversal(TreeNode *root, int *arr, int *index);
void preorder_traversal(TreeNode *root, int *arr, int *index);
void postorder_traversal(TreeNode *root, int *arr, int *index);
```
- Traverses the tree rooted at `root` and records visited node values into `arr` starting at `*index`.
- Increments `*index` by 1 for each node visited.
- Order of visits:
  - `inorder_traversal`: Left subtree $\rightarrow$ Root node $\rightarrow$ Right subtree.
  - `preorder_traversal`: Root node $\rightarrow$ Left subtree $\rightarrow$ Right subtree.
  - `postorder_traversal`: Left subtree $\rightarrow$ Right subtree $\rightarrow$ Root node.
- Handles `root == NULL`, `arr == NULL`, or `index == NULL` gracefully without performing operations.

### 6. Memory Deallocation
```c
void free_tree(TreeNode *root);
```
- Recursively frees all nodes in the tree using post-order cleanup.
- Handles `root == NULL` gracefully.

---

## Instructions & Local Testing

1. **Implement Logic:** Complete all functions in `binary_tree.c`.
2. **Run Public Tests:**
   ```bash
   make test-public
   # or
   ./run
   ```
3. **Clean Build Artifacts:**
   ```bash
   make clean
   # or
   ./run clean
   ```

---

## Grading Scheme

Your submission will be evaluated against private test suites:

| Target | Description | Points |
| :--- | :--- | :--- |
| `make test-public` | Basic tree creation, insertion, search, traversal, deletion | 0 pts |
| `make test-submission-traversals` | Comprehensive edge case tests for in-order, pre-order, and post-order traversals | 3 pts |
| `make test-submission-insertion` | Node creation, BST insertion, duplicate handling, and search verification | 3 pts |
| `make test-submission-deletion` | Leaf, single child, two children, root, and sequential deletions | 4 pts |
| **Total** | | **10 pts** |
