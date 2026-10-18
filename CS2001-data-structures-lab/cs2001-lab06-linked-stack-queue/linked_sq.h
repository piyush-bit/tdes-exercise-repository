#ifndef LINKED_SQ_H
#define LINKED_SQ_H

#include <stdbool.h>
#include <stddef.h>

// Node structure for linked stack and queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// LinkedStack structure
typedef struct {
    Node* top;
    size_t size;
} LinkedStack;

// LinkedQueue structure
typedef struct {
    Node* front;
    Node* rear;
    size_t size;
} LinkedQueue;

// Linked Stack API
LinkedStack* lstack_create(void);
bool lstack_push(LinkedStack* stack, int value);
bool lstack_pop(LinkedStack* stack, int* value);
bool lstack_peek(const LinkedStack* stack, int* value);
bool lstack_is_empty(const LinkedStack* stack);
size_t lstack_size(const LinkedStack* stack);
void lstack_free(LinkedStack* stack);

// Linked Queue API
LinkedQueue* lqueue_create(void);
bool lqueue_enqueue(LinkedQueue* queue, int value);
bool lqueue_dequeue(LinkedQueue* queue, int* value);
bool lqueue_front(const LinkedQueue* queue, int* value);
bool lqueue_is_empty(const LinkedQueue* queue);
size_t lqueue_size(const LinkedQueue* queue);
void lqueue_free(LinkedQueue* queue);

#endif // LINKED_SQ_H
