# CS2001 Lab 05: Singly & Doubly Linked Lists in C

## Overview
In this laboratory exercise, you will implement foundational dynamic data structures in C:
1. **Singly Linked List (SLL)**: Nodes linked sequentially in one direction (`head -> node -> node -> NULL`).
2. **Doubly Linked List (DLL)**: Nodes linked bidirectionally (`NULL <- head <-> node <-> node -> NULL`).

Proper pointer manipulation and memory management (`malloc` / `free`) are central goals of this lab.

---

## Data Structures

```c
typedef struct SLLNode {
    int data;
    struct SLLNode *next;
} SLLNode;

typedef struct DLLNode {
    int data;
    struct DLLNode *prev;
    struct DLLNode *next;
} DLLNode;
```

---

## API Specifications

### Singly Linked List (SLL) Functions

| Function Signature | Description |
| :--- | :--- |
| `SLLNode *sll_create_node(int data)` | Allocates an `SLLNode` via `malloc`, sets `data`, and sets `next = NULL`. Returns NULL on allocation failure. |
| `SLLNode *sll_insert_at_head(SLLNode *head, int data)` | Inserts a new node at head. Returns new head pointer. |
| `SLLNode *sll_insert_at_tail(SLLNode *head, int data)` | Inserts a new node at tail. Returns head pointer. |
| `SLLNode *sll_insert_at_index(SLLNode *head, int data, int index)` | Inserts a new node at 0-based `index`. Returns head pointer. If `index < 0` or `index > length`, leaves list unchanged. |
| `SLLNode *sll_delete_by_value(SLLNode *head, int value)` | Deletes the first node with `data == value` and frees its memory. Returns head pointer. |
| `SLLNode *sll_delete_at_index(SLLNode *head, int index)` | Deletes node at 0-based `index` and frees its memory. Returns head pointer. If `index < 0` or `index >= length`, leaves list unchanged. |
| `size_t sll_get_length(const SLLNode *head)` | Returns total number of nodes in list. Returns 0 if `head == NULL`. |
| `SLLNode *sll_find(SLLNode *head, int value)` | Returns pointer to first node with `data == value`, or `NULL` if not found. |
| `void sll_to_array(const SLLNode *head, int *arr)` | Copies node data sequentially into pre-allocated array `arr`. Does nothing if `head` or `arr` is NULL. |
| `void sll_free_list(SLLNode *head)` | Frees all nodes in the list iteratively or recursively. Safe to call with `NULL`. |

---

### Doubly Linked List (DLL) Functions

| Function Signature | Description |
| :--- | :--- |
| `DLLNode *dll_create_node(int data)` | Allocates a `DLLNode` via `malloc`, sets `data`, `prev = NULL`, and `next = NULL`. |
| `DLLNode *dll_insert_at_head(DLLNode *head, int data)` | Inserts node at head. Updates `next` and `prev` pointers. Returns new head pointer. |
| `DLLNode *dll_insert_at_tail(DLLNode *head, int data)` | Inserts node at tail. Updates `next` and `prev` pointers. Returns head pointer. |
| `DLLNode *dll_insert_at_index(DLLNode *head, int data, int index)` | Inserts node at 0-based `index`. Updates `next` and `prev` pointers. Returns head pointer. If invalid `index`, leaves list unchanged. |
| `DLLNode *dll_delete_by_value(DLLNode *head, int value)` | Deletes first node with `data == value`, updating adjacent `prev` and `next` pointers. Frees node memory. Returns head pointer. |
| `DLLNode *dll_delete_at_index(DLLNode *head, int index)` | Deletes node at 0-based `index`, updating adjacent `prev` and `next` pointers. Frees node memory. Returns head pointer. |
| `size_t dll_get_length(const DLLNode *head)` | Returns total number of nodes in DLL. Returns 0 if `head == NULL`. |
| `DLLNode *dll_find(DLLNode *head, int value)` | Returns pointer to first node with `data == value`, or `NULL` if not found. |
| `void dll_to_array(const DLLNode *head, int *arr)` | Copies node data sequentially into pre-allocated array `arr`. Does nothing if `head` or `arr` is NULL. |
| `void dll_free_list(DLLNode *head)` | Frees all nodes in the DLL. Safe to call with `NULL`. |

---

## Instructions & Rules

1. You must edit only `linked_lists.c`.
2. Do not modify `linked_lists.h`.
3. Memory leaks are invalid implementations: make sure every node freed by `sll_delete_*`, `dll_delete_*`, `sll_free_list`, and `dll_free_list` is correctly passed to `free()`.
4. Ensure NULL checks on pointer parameters and allocation results.

---

## Running Tests

Run public tests locally:
```bash
./run
# or
make test-public
```

To clean build artifacts:
```bash
./run clean
# or
make clean
```
