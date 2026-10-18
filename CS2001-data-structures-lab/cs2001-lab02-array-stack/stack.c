#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(Stack *s, int capacity) {
    // TODO: Initialize stack structure, allocate data array of given capacity, set top to -1
    (void)capacity;
    if (s == NULL) return;
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

void free_stack(Stack *s) {
    // TODO: Free dynamically allocated data array and reset stack fields
    if (s == NULL) return;
}

bool stack_is_empty(const Stack *s) {
    // TODO: Return true if stack is empty or s is NULL, false otherwise
    (void)s;
    return true;
}

bool stack_is_full(const Stack *s) {
    // TODO: Return true if stack is full or s is NULL, false otherwise
    (void)s;
    return false;
}

bool stack_push(Stack *s, int value) {
    // TODO: Push value onto stack if not full. Return true on success, false on failure.
    (void)s;
    (void)value;
    return false;
}

bool stack_pop(Stack *s, int *out_value) {
    // TODO: Pop element from stack if not empty and store in *out_value. Return true on success, false on failure.
    (void)s;
    (void)out_value;
    return false;
}

bool stack_peek(const Stack *s, int *out_value) {
    // TODO: Store top element in *out_value without removing it. Return true on success, false on failure.
    (void)s;
    (void)out_value;
    return false;
}
