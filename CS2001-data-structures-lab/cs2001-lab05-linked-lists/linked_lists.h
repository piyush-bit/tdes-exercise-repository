#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stddef.h>
#include <stdbool.h>

/**
 * Singly Linked List Node
 */
typedef struct SLLNode {
    int data;
    struct SLLNode *next;
} SLLNode;

/**
 * Doubly Linked List Node
 */
typedef struct DLLNode {
    int data;
    struct DLLNode *prev;
    struct DLLNode *next;
} DLLNode;

/* ========================================================================= */
/* Singly Linked List (SLL) Function Prototypes                             */
/* ========================================================================= */

/**
 * Allocates and initializes a new Singly Linked List node.
 * @param data Integer value to store in the node.
 * @return Pointer to the newly allocated SLLNode, or NULL on allocation failure.
 */
SLLNode *sll_create_node(int data);

/**
 * Inserts a new node with the specified data at the head of the Singly Linked List.
 * @param head Pointer to the current head node of the SLL (may be NULL).
 * @param data Integer value for the new node.
 * @return Pointer to the new head node of the list.
 */
SLLNode *sll_insert_at_head(SLLNode *head, int data);

/**
 * Inserts a new node with the specified data at the tail of the Singly Linked List.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param data Integer value for the new node.
 * @return Pointer to the head node of the list.
 */
SLLNode *sll_insert_at_tail(SLLNode *head, int data);

/**
 * Inserts a new node with the specified data at the 0-based index in the SLL.
 * Index 0 corresponds to inserting at the head.
 * Index equal to current length corresponds to inserting at the tail.
 * If index < 0 or index > current length, the list remains unchanged.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param data Integer value for the new node.
 * @param index 0-based insertion index.
 * @return Pointer to the head node of the list.
 */
SLLNode *sll_insert_at_index(SLLNode *head, int data, int index);

/**
 * Deletes the FIRST occurrence of a node containing the specified value from the SLL.
 * Frees the memory allocated for the deleted node.
 * If the value is not found or list is empty, the list remains unchanged.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param value Integer value to search and delete.
 * @return Pointer to the head node of the list.
 */
SLLNode *sll_delete_by_value(SLLNode *head, int value);

/**
 * Deletes the node at the 0-based index from the SLL.
 * Frees the memory allocated for the deleted node.
 * If index < 0 or index >= current length, the list remains unchanged.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param index 0-based index of the node to delete.
 * @return Pointer to the head node of the list.
 */
SLLNode *sll_delete_at_index(SLLNode *head, int index);

/**
 * Calculates the number of nodes in the SLL.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @return Count of nodes in the list.
 */
size_t sll_get_length(const SLLNode *head);

/**
 * Searches for the FIRST node in the SLL containing the specified value.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param value Integer value to search for.
 * @return Pointer to the matching node, or NULL if not found.
 */
SLLNode *sll_find(SLLNode *head, int value);

/**
 * Copies elements of the SLL into a pre-allocated array in sequential order.
 * Assumes arr has enough memory to store sll_get_length(head) integers.
 * If head or arr is NULL, does nothing.
 * @param head Pointer to the head node of the SLL (may be NULL).
 * @param arr Pointer to pre-allocated integer array.
 */
void sll_to_array(const SLLNode *head, int *arr);

/**
 * Frees all memory allocated for nodes in the SLL.
 * Safe to call with NULL.
 * @param head Pointer to the head node of the SLL (may be NULL).
 */
void sll_free_list(SLLNode *head);


/* ========================================================================= */
/* Doubly Linked List (DLL) Function Prototypes                             */
/* ========================================================================= */

/**
 * Allocates and initializes a new Doubly Linked List node.
 * @param data Integer value to store in the node.
 * @return Pointer to the newly allocated DLLNode, or NULL on allocation failure.
 */
DLLNode *dll_create_node(int data);

/**
 * Inserts a new node with the specified data at the head of the Doubly Linked List.
 * Properly updates both next and prev pointers.
 * @param head Pointer to current head node of DLL (may be NULL).
 * @param data Integer value for the new node.
 * @return Pointer to the new head node of the list.
 */
DLLNode *dll_insert_at_head(DLLNode *head, int data);

/**
 * Inserts a new node with the specified data at the tail of the Doubly Linked List.
 * Properly updates both next and prev pointers.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param data Integer value for the new node.
 * @return Pointer to the head node of the list.
 */
DLLNode *dll_insert_at_tail(DLLNode *head, int data);

/**
 * Inserts a new node with the specified data at the 0-based index in the DLL.
 * Properly updates both next and prev pointers.
 * Index 0 corresponds to inserting at the head.
 * Index equal to current length corresponds to inserting at the tail.
 * If index < 0 or index > current length, the list remains unchanged.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param data Integer value for the new node.
 * @param index 0-based insertion index.
 * @return Pointer to the head node of the list.
 */
DLLNode *dll_insert_at_index(DLLNode *head, int data, int index);

/**
 * Deletes the FIRST occurrence of a node containing the specified value from the DLL.
 * Properly updates both next and prev pointers of neighboring nodes and frees the memory.
 * If the value is not found or list is empty, the list remains unchanged.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param value Integer value to search and delete.
 * @return Pointer to the head node of the list.
 */
DLLNode *dll_delete_by_value(DLLNode *head, int value);

/**
 * Deletes the node at the 0-based index from the DLL.
 * Properly updates both next and prev pointers of neighboring nodes and frees the memory.
 * If index < 0 or index >= current length, the list remains unchanged.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param index 0-based index of the node to delete.
 * @return Pointer to the head node of the list.
 */
DLLNode *dll_delete_at_index(DLLNode *head, int index);

/**
 * Calculates the number of nodes in the DLL.
 * @param head Pointer to head node of DLL (may be NULL).
 * @return Count of nodes in the list.
 */
size_t dll_get_length(const DLLNode *head);

/**
 * Searches for the FIRST node in the DLL containing the specified value.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param value Integer value to search for.
 * @return Pointer to the matching node, or NULL if not found.
 */
DLLNode *dll_find(DLLNode *head, int value);

/**
 * Copies elements of the DLL into a pre-allocated array in sequential order.
 * Assumes arr has enough memory to store dll_get_length(head) integers.
 * If head or arr is NULL, does nothing.
 * @param head Pointer to head node of DLL (may be NULL).
 * @param arr Pointer to pre-allocated integer array.
 */
void dll_to_array(const DLLNode *head, int *arr);

/**
 * Frees all memory allocated for nodes in the DLL.
 * Safe to call with NULL.
 * @param head Pointer to head node of DLL (may be NULL).
 */
void dll_free_list(DLLNode *head);

#endif // LINKED_LISTS_H
