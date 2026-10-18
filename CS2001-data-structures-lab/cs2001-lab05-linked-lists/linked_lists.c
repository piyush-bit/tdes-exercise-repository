#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

/* ========================================================================= */
/* Singly Linked List (SLL) Implementation                                  */
/* ========================================================================= */

SLLNode *sll_create_node(int data) {
    // TODO: Allocate memory for a new SLLNode, set data and next pointer, and return it.
    (void)data;
    return NULL;
}

SLLNode *sll_insert_at_head(SLLNode *head, int data) {
    // TODO: Create a new node with data and insert it at the head of the SLL.
    (void)data;
    return head;
}

SLLNode *sll_insert_at_tail(SLLNode *head, int data) {
    // TODO: Create a new node with data and insert it at the end of the SLL.
    (void)data;
    return head;
}

SLLNode *sll_insert_at_index(SLLNode *head, int data, int index) {
    // TODO: Create a new node with data and insert it at 0-based index in the SLL.
    (void)data;
    (void)index;
    return head;
}

SLLNode *sll_delete_by_value(SLLNode *head, int value) {
    // TODO: Delete the first occurrence of node with given value from the SLL and free memory.
    (void)value;
    return head;
}

SLLNode *sll_delete_at_index(SLLNode *head, int index) {
    // TODO: Delete node at 0-based index from the SLL and free memory.
    (void)index;
    return head;
}

size_t sll_get_length(const SLLNode *head) {
    // TODO: Calculate and return the total number of nodes in the SLL.
    (void)head;
    return 0;
}

SLLNode *sll_find(SLLNode *head, int value) {
    // TODO: Search for first node with data equal to value in SLL. Return node pointer or NULL.
    (void)head;
    (void)value;
    return NULL;
}

void sll_to_array(const SLLNode *head, int *arr) {
    // TODO: Copy node elements sequentially into array arr.
    (void)head;
    (void)arr;
}

void sll_free_list(SLLNode *head) {
    // TODO: Free all nodes in the SLL.
    (void)head;
}


/* ========================================================================= */
/* Doubly Linked List (DLL) Implementation                                  */
/* ========================================================================= */

DLLNode *dll_create_node(int data) {
    // TODO: Allocate memory for a new DLLNode, set data, prev, and next pointers.
    (void)data;
    return NULL;
}

DLLNode *dll_insert_at_head(DLLNode *head, int data) {
    // TODO: Create a new node with data and insert it at the head of the DLL.
    (void)data;
    return head;
}

DLLNode *dll_insert_at_tail(DLLNode *head, int data) {
    // TODO: Create a new node with data and insert it at the tail of the DLL.
    (void)data;
    return head;
}

DLLNode *dll_insert_at_index(DLLNode *head, int data, int index) {
    // TODO: Create a new node with data and insert it at 0-based index in the DLL.
    (void)data;
    (void)index;
    return head;
}

DLLNode *dll_delete_by_value(DLLNode *head, int value) {
    // TODO: Delete first occurrence of node with given value from DLL and free memory.
    (void)value;
    return head;
}

DLLNode *dll_delete_at_index(DLLNode *head, int index) {
    // TODO: Delete node at 0-based index from DLL and free memory.
    (void)index;
    return head;
}

size_t dll_get_length(const DLLNode *head) {
    // TODO: Calculate and return total number of nodes in DLL.
    (void)head;
    return 0;
}

DLLNode *dll_find(DLLNode *head, int value) {
    // TODO: Search for first node with data equal to value in DLL. Return node pointer or NULL.
    (void)head;
    (void)value;
    return NULL;
}

void dll_to_array(const DLLNode *head, int *arr) {
    // TODO: Copy node elements sequentially into array arr.
    (void)head;
    (void)arr;
}

void dll_free_list(DLLNode *head) {
    // TODO: Free all nodes in the DLL.
    (void)head;
}
