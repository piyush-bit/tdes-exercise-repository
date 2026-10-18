# CS2001 Lab 02: Array-Based Stack in C

## Overview

In this lab, you will implement an array-backed **Stack** data structure in C. A stack is a Last-In, First-Out (LIFO) collection where elements are added (pushed) and removed (popped) from the same end, called the **top**.

## Data Structures

The stack structure is defined in `stack.h`:

```c
typedef struct {
    int *data;      // Pointer to dynamically allocated array
    int top;        // Index of the top element (-1 when empty)
    int capacity;   // Maximum capacity of the stack
} Stack;
```

## Function Contracts & Specification

You must implement the following functions in `stack.c`:

### 1. `void init_stack(Stack *s, int capacity)`
- Initializes the stack `s` with the given `capacity`.
- Sets `s->top = -1` and `s->capacity = capacity`.
- Dynamically allocates memory for `s->data` to hold `capacity` integers.
- If `s` is `NULL` or `capacity <= 0`, sets `s->data = NULL`, `s->top = -1`, and `s->capacity = 0`.

### 2. `void free_stack(Stack *s)`
- Frees the dynamically allocated `data` array if `s` and `s->data` are non-NULL.
- Resets `s->top = -1` and `s->capacity = 0`.

### 3. `bool stack_is_empty(const Stack *s)`
- Returns `true` if `s` is `NULL`, `s->data` is `NULL`, or `s->top == -1`.
- Returns `false` otherwise.

### 4. `bool stack_is_full(const Stack *s)`
- Returns `true` if `s` is `NULL`, `s->data` is `NULL`, or `s->top >= s->capacity - 1`.
- Returns `false` otherwise.

### 5. `bool stack_push(Stack *s, int value)`
- Pushes `value` onto the stack `s`.
- If `s` is `NULL` or the stack is full, returns `false` without modifying the stack.
- Otherwise, increments `top` (`s->top++`), stores `value` at `s->data[s->top]`, and returns `true`.

### 6. `bool stack_pop(Stack *s, int *out_value)`
- Removes the top element from the stack `s` and writes its value to `*out_value`.
- If `s` is `NULL`, `out_value` is `NULL`, or the stack is empty, returns `false` without modifying `*out_value` or the stack.
- Otherwise, sets `*out_value = s->data[s->top]`, decrements `top` (`s->top--`), and returns `true`.

### 7. `bool stack_peek(const Stack *s, int *out_value)`
- Inspects the top element of the stack `s` and writes its value to `*out_value` without removing it.
- If `s` is `NULL`, `out_value` is `NULL`, or the stack is empty, returns `false` without modifying `*out_value`.
- Otherwise, sets `*out_value = s->data[s->top]` and returns `true`.

---

## Getting Started

1. Run public tests locally:
   ```bash
   make test-public
   # or
   ./run
   ```
2. Implement your solutions in `stack.c`. Do not edit `stack.h` or `Makefile`.

---

## Grading Breakdown

| Test Command | Points | Type | Description |
|---|---|---|---|
| `make test-public` | 0 | Public | Basic stack operations (push, pop, peek, empty, full) |
| `make test-submission-push` | 3 | Private | Push boundary conditions, overflow, and NULL checks |
| `make test-submission-pop` | 3 | Private | Pop LIFO ordering, underflow, and NULL checks |
| `make test-submission-peek` | 4 | Private | Peek non-mutating guarantees and edge cases |
