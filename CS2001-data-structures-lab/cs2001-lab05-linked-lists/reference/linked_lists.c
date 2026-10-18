#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"

/* ========================================================================= */
/* Singly Linked List (SLL) Implementation                                  */
/* ========================================================================= */

SLLNode *sll_create_node(int data) {
    SLLNode *node = (SLLNode *)malloc(sizeof(SLLNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

SLLNode *sll_insert_at_head(SLLNode *head, int data) {
    SLLNode *new_node = sll_create_node(data);
    if (new_node == NULL) {
        return head;
    }
    new_node->next = head;
    return new_node;
}

SLLNode *sll_insert_at_tail(SLLNode *head, int data) {
    SLLNode *new_node = sll_create_node(data);
    if (new_node == NULL) {
        return head;
    }
    if (head == NULL) {
        return new_node;
    }
    SLLNode *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
    return head;
}

SLLNode *sll_insert_at_index(SLLNode *head, int data, int index) {
    if (index < 0) {
        return head;
    }
    size_t len = sll_get_length(head);
    if ((size_t)index > len) {
        return head;
    }
    if (index == 0) {
        return sll_insert_at_head(head, data);
    }

    SLLNode *new_node = sll_create_node(data);
    if (new_node == NULL) {
        return head;
    }

    SLLNode *curr = head;
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
    return head;
}

SLLNode *sll_delete_by_value(SLLNode *head, int value) {
    if (head == NULL) {
        return NULL;
    }
    if (head->data == value) {
        SLLNode *temp = head->next;
        free(head);
        return temp;
    }
    SLLNode *curr = head;
    while (curr->next != NULL && curr->next->data != value) {
        curr = curr->next;
    }
    if (curr->next != NULL) {
        SLLNode *target = curr->next;
        curr->next = target->next;
        free(target);
    }
    return head;
}

SLLNode *sll_delete_at_index(SLLNode *head, int index) {
    if (head == NULL || index < 0) {
        return head;
    }
    size_t len = sll_get_length(head);
    if ((size_t)index >= len) {
        return head;
    }
    if (index == 0) {
        SLLNode *temp = head->next;
        free(head);
        return temp;
    }
    SLLNode *curr = head;
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    SLLNode *target = curr->next;
    curr->next = target->next;
    free(target);
    return head;
}

size_t sll_get_length(const SLLNode *head) {
    size_t count = 0;
    const SLLNode *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

SLLNode *sll_find(SLLNode *head, int value) {
    SLLNode *curr = head;
    while (curr != NULL) {
        if (curr->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void sll_to_array(const SLLNode *head, int *arr) {
    if (head == NULL || arr == NULL) {
        return;
    }
    const SLLNode *curr = head;
    size_t i = 0;
    while (curr != NULL) {
        arr[i++] = curr->data;
        curr = curr->next;
    }
}

void sll_free_list(SLLNode *head) {
    SLLNode *curr = head;
    while (curr != NULL) {
        SLLNode *next = curr->next;
        free(curr);
        curr = next;
    }
}


/* ========================================================================= */
/* Doubly Linked List (DLL) Implementation                                  */
/* ========================================================================= */

DLLNode *dll_create_node(int data) {
    DLLNode *node = (DLLNode *)malloc(sizeof(DLLNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

DLLNode *dll_insert_at_head(DLLNode *head, int data) {
    DLLNode *new_node = dll_create_node(data);
    if (new_node == NULL) {
        return head;
    }
    new_node->next = head;
    if (head != NULL) {
        head->prev = new_node;
    }
    return new_node;
}

DLLNode *dll_insert_at_tail(DLLNode *head, int data) {
    DLLNode *new_node = dll_create_node(data);
    if (new_node == NULL) {
        return head;
    }
    if (head == NULL) {
        return new_node;
    }
    DLLNode *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
    new_node->prev = curr;
    return head;
}

DLLNode *dll_insert_at_index(DLLNode *head, int data, int index) {
    if (index < 0) {
        return head;
    }
    size_t len = dll_get_length(head);
    if ((size_t)index > len) {
        return head;
    }
    if (index == 0) {
        return dll_insert_at_head(head, data);
    }
    if ((size_t)index == len) {
        return dll_insert_at_tail(head, data);
    }

    DLLNode *new_node = dll_create_node(data);
    if (new_node == NULL) {
        return head;
    }

    DLLNode *curr = head;
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    new_node->next = curr->next;
    new_node->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = new_node;
    }
    curr->next = new_node;
    return head;
}

DLLNode *dll_delete_by_value(DLLNode *head, int value) {
    if (head == NULL) {
        return NULL;
    }
    DLLNode *curr = head;
    while (curr != NULL && curr->data != value) {
        curr = curr->next;
    }
    if (curr == NULL) {
        return head;
    }

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        head = curr->next;
    }

    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }

    free(curr);
    return head;
}

DLLNode *dll_delete_at_index(DLLNode *head, int index) {
    if (head == NULL || index < 0) {
        return head;
    }
    size_t len = dll_get_length(head);
    if ((size_t)index >= len) {
        return head;
    }

    DLLNode *curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        head = curr->next;
    }

    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }

    free(curr);
    return head;
}

size_t dll_get_length(const DLLNode *head) {
    size_t count = 0;
    const DLLNode *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

DLLNode *dll_find(DLLNode *head, int value) {
    DLLNode *curr = head;
    while (curr != NULL) {
        if (curr->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void dll_to_array(const DLLNode *head, int *arr) {
    if (head == NULL || arr == NULL) {
        return;
    }
    const DLLNode *curr = head;
    size_t i = 0;
    while (curr != NULL) {
        arr[i++] = curr->data;
        curr = curr->next;
    }
}

void dll_free_list(DLLNode *head) {
    DLLNode *curr = head;
    while (curr != NULL) {
        DLLNode *next = curr->next;
        free(curr);
        curr = next;
    }
}
