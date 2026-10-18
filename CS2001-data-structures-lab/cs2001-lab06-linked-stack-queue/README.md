# CS2001 Lab 06: Stack & Queue using Linked List in C

## Overview

In this lab, you will implement Stack (LIFO - Last In, First Out) and Queue (FIFO - First In, First Out) data structures using dynamically allocated singly-linked lists in C.

Unlike fixed-size array implementations, linked list implementations allow stacks and queues to grow dynamically without a predetermined capacity limit, bounded only by available system memory.

---

## Data Structures

The data structures are defined in [`linked_sq.h`](linked_sq.h):

```c
// Node structure for single linked list element
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
```

---

## API Specifications

You need to implement all functions declared in [`linked_sq.h`](linked_sq.h) within [`linked_sq.c`](linked_sq.c).

### 1. Linked Stack Functions

- **`LinkedStack* lstack_create(void)`**
  - Allocates and initializes a new `LinkedStack`.
  - Sets `top` to `NULL` and `size` to `0`.
  - Returns pointer to the created stack, or `NULL` if `malloc` fails.

- **`bool lstack_push(LinkedStack* stack, int value)`**
  - Pushes `value` onto the top of `stack`.
  - Allocates a new `Node`, sets `data = value`, updates `next` and `top` pointer, and increments `size`.
  - Returns `true` on success, `false` if `stack` is `NULL` or memory allocation fails.

- **`bool lstack_pop(LinkedStack* stack, int* value)`**
  - Removes the top element from `stack` and stores its `data` in `*value`.
  - Frees the popped node and decrements `size`.
  - Returns `true` on success, `false` if `stack` is `NULL`, `value` is `NULL`, or the stack is empty.

- **`bool lstack_peek(const LinkedStack* stack, int* value)`**
  - Reads the data of the top element into `*value` without removing the node.
  - Returns `true` on success, `false` if `stack` is `NULL`, `value` is `NULL`, or the stack is empty.

- **`bool lstack_is_empty(const LinkedStack* stack)`**
  - Returns `true` if `stack` is `NULL` or `stack->top == NULL`, `false` otherwise.

- **`size_t lstack_size(const LinkedStack* stack)`**
  - Returns the number of elements in `stack` (0 if `stack` is `NULL`).

- **`void lstack_free(LinkedStack* stack)`**
  - Traverses and frees all nodes in `stack`, then frees the `stack` structure itself.
  - Safely does nothing if `stack` is `NULL`.

---

### 2. Linked Queue Functions

- **`LinkedQueue* lqueue_create(void)`**
  - Allocates and initializes a new `LinkedQueue`.
  - Sets `front` and `rear` to `NULL`, and `size` to `0`.
  - Returns pointer to the created queue, or `NULL` if `malloc` fails.

- **`bool lqueue_enqueue(LinkedQueue* queue, int value)`**
  - Enqueues `value` at the rear of `queue`.
  - Allocates a new `Node`, sets `data = value`, updates `rear->next` and `rear` (and `front` if queue was empty), and increments `size`.
  - Returns `true` on success, `false` if `queue` is `NULL` or memory allocation fails.

- **`bool lqueue_dequeue(LinkedQueue* queue, int* value)`**
  - Dequeues the front element from `queue` and stores its `data` in `*value`.
  - Updates `front` pointer. If `front` becomes `NULL`, sets `rear` to `NULL` as well.
  - Frees the dequeued node and decrements `size`.
  - Returns `true` on success, `false` if `queue` is `NULL`, `value` is `NULL`, or the queue is empty.

- **`bool lqueue_front(const LinkedQueue* queue, int* value)`**
  - Reads the data of the front element into `*value` without removing the node.
  - Returns `true` on success, `false` if `queue` is `NULL`, `value` is `NULL`, or the queue is empty.

- **`bool lqueue_is_empty(const LinkedQueue* queue)`**
  - Returns `true` if `queue` is `NULL` or `queue->front == NULL`, `false` otherwise.

- **`size_t lqueue_size(const LinkedQueue* queue)`**
  - Returns the number of elements in `queue` (0 if `queue` is `NULL`).

- **`void lqueue_free(LinkedQueue* queue)`**
  - Traverses and frees all nodes in `queue`, then frees the `queue` structure itself.
  - Safely does nothing if `queue` is `NULL`.

---

## Testing Locally

Run the public test suite locally to verify your progress:

```bash
make test-public
# or
./run
```

To clean up build artifacts:

```bash
make clean
```
