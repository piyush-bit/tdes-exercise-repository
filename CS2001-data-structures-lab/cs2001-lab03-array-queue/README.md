# CS2001 Lab 03: Array-Based Queue in C

## Objectives
- Understand the First-In-First-Out (FIFO) properties of a Queue data structure.
- Implement a fixed-capacity, circular array-based queue in C.
- Practice modular programming, pointer safety, boundary condition handling, and structural invariants.

---

## Overview

A **Queue** is an abstract data type that maintains elements in a FIFO (First-In, First-Out) sequence. Elements are inserted at the **rear** (enqueue) and removed from the **front** (dequeue).

In this lab, you will implement a bounded circular array queue using the `Queue` struct defined in [`queue.h`](file:///Users/piyush/Developer/tdes-exercise-repository/cs2001-lab03-array-queue/queue.h).

---

## Data Structure Definition

```c
#define MAX_CAPACITY 100

typedef struct {
    int data[MAX_CAPACITY];
    int front;
    int rear;
    int size;
    int capacity;
} Queue;
```

### Fields:
- `data`: Fixed-size array of `int` elements with maximum size `MAX_CAPACITY` (100).
- `front`: Index of the current front element in the queue.
- `rear`: Index of the current rear element in the queue.
- `size`: Number of elements currently stored in the queue.
- `capacity`: Effective maximum capacity for this queue instance (`1 <= capacity <= MAX_CAPACITY`).

---

## API Specification

Implement the following functions in `queue.c`:

### 1. `void init_queue(Queue *q, int capacity)`
- Initializes the queue `q`.
- If `q` is `NULL`, the function does nothing.
- If `capacity <= 0` or `capacity > MAX_CAPACITY`, set `q->capacity` to `MAX_CAPACITY`. Otherwise, set `q->capacity = capacity`.
- Initializes `front = 0`, `rear = -1`, `size = 0`.

### 2. `bool queue_is_empty(const Queue *q)`
- Returns `true` if `q` is `NULL` or `q->size == 0`.
- Otherwise returns `false`.

### 3. `bool queue_is_full(const Queue *q)`
- Returns `false` if `q` is `NULL`.
- Returns `true` if `q->size >= q->capacity`.
- Otherwise returns `false`.

### 4. `bool enqueue(Queue *q, int value)`
- Inserts `value` at the rear of the queue using circular array indexing: `rear = (rear + 1) % capacity`.
- Returns `false` if `q` is `NULL` or `queue_is_full(q)` is `true`.
- Increments `q->size` by 1 and returns `true`.

### 5. `bool dequeue(Queue *q, int *value)`
- Removes the front element from the queue.
- Returns `false` if `q` is `NULL` or `queue_is_empty(q)` is `true`.
- If `value` is not `NULL`, populates `*value` with the dequeued element.
- Advances `front` circularly: `front = (front + 1) % capacity`.
- Decrements `q->size` by 1 and returns `true`.

### 6. `bool queue_front(const Queue *q, int *value)`
- Retrieves the element at the front of the queue without modifying the queue state or size.
- Returns `false` if `q` is `NULL` or `queue_is_empty(q)` is `true`.
- If `value` is not `NULL`, populates `*value` with the front element.
- Returns `true` on success.

---

## Building and Testing Locally

Run the public test suite using the convenience wrapper script:
```bash
./run
# or directly:
make test-public
```

Clean up build artifacts:
```bash
./run clean
# or directly:
make clean
```
