#include "linked_sq.h"
#include <stdlib.h>

LinkedStack* lstack_create(void) {
    // TODO: Allocate memory for a new LinkedStack.
    // Initialize top to NULL and size to 0.
    // Return pointer to the stack, or NULL on allocation failure.
    return NULL;
}

bool lstack_push(LinkedStack* stack, int value) {
    (void)stack;
    (void)value;
    // TODO: Allocate a new Node with data = value.
    // Push the node onto the top of the stack and update size.
    // Return true on success, false if stack is NULL or allocation fails.
    return false;
}

bool lstack_pop(LinkedStack* stack, int* value) {
    (void)stack;
    (void)value;
    // TODO: Pop top element from stack, write data to *value, free popped node.
    // Update stack size.
    // Return true on success, false if stack is NULL, empty, or value is NULL.
    return false;
}

bool lstack_peek(const LinkedStack* stack, int* value) {
    (void)stack;
    (void)value;
    // TODO: Write top element's data to *value without removing the node.
    // Return true on success, false if stack is NULL, empty, or value is NULL.
    return false;
}

bool lstack_is_empty(const LinkedStack* stack) {
    (void)stack;
    // TODO: Return true if stack is NULL or stack->top == NULL, false otherwise.
    return true;
}

size_t lstack_size(const LinkedStack* stack) {
    (void)stack;
    // TODO: Return the current size of the stack (0 if NULL).
    return 0;
}

void lstack_free(LinkedStack* stack) {
    (void)stack;
    // TODO: Free all nodes in the stack, then free the stack structure itself.
}

LinkedQueue* lqueue_create(void) {
    // TODO: Allocate memory for a new LinkedQueue.
    // Initialize front and rear to NULL and size to 0.
    // Return pointer to the queue, or NULL on allocation failure.
    return NULL;
}

bool lqueue_enqueue(LinkedQueue* queue, int value) {
    (void)queue;
    (void)value;
    // TODO: Allocate a new Node with data = value.
    // Enqueue the node at the rear of the queue and update size.
    // Return true on success, false if queue is NULL or allocation fails.
    return false;
}

bool lqueue_dequeue(LinkedQueue* queue, int* value) {
    (void)queue;
    (void)value;
    // TODO: Dequeue front element from queue, write data to *value, free dequeued node.
    // Update front and rear pointers (if empty, rear should become NULL) and size.
    // Return true on success, false if queue is NULL, empty, or value is NULL.
    return false;
}

bool lqueue_front(const LinkedQueue* queue, int* value) {
    (void)queue;
    (void)value;
    // TODO: Write front element's data to *value without removing the node.
    // Return true on success, false if queue is NULL, empty, or value is NULL.
    return false;
}

bool lqueue_is_empty(const LinkedQueue* queue) {
    (void)queue;
    // TODO: Return true if queue is NULL or queue->front == NULL, false otherwise.
    return true;
}

size_t lqueue_size(const LinkedQueue* queue) {
    (void)queue;
    // TODO: Return the current size of the queue (0 if NULL).
    return 0;
}

void lqueue_free(LinkedQueue* queue) {
    (void)queue;
    // TODO: Free all nodes in the queue, then free the queue structure itself.
}
