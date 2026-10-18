#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(Stack *s, int capacity) {
    if (s == NULL) return;
    if (capacity <= 0) {
        s->data = NULL;
        s->top = -1;
        s->capacity = 0;
        return;
    }
    s->data = (int *)malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
}

void free_stack(Stack *s) {
    if (s == NULL) return;
    if (s->data != NULL) {
        free(s->data);
        s->data = NULL;
    }
    s->top = -1;
    s->capacity = 0;
}

bool stack_is_empty(const Stack *s) {
    if (s == NULL || s->data == NULL) return true;
    return s->top == -1;
}

bool stack_is_full(const Stack *s) {
    if (s == NULL || s->data == NULL || s->capacity <= 0) return true;
    return s->top >= s->capacity - 1;
}

bool stack_push(Stack *s, int value) {
    if (s == NULL || stack_is_full(s)) {
        return false;
    }
    s->top++;
    s->data[s->top] = value;
    return true;
}

bool stack_pop(Stack *s, int *out_value) {
    if (s == NULL || out_value == NULL || stack_is_empty(s)) {
        return false;
    }
    *out_value = s->data[s->top];
    s->top--;
    return true;
}

bool stack_peek(const Stack *s, int *out_value) {
    if (s == NULL || out_value == NULL || stack_is_empty(s)) {
        return false;
    }
    *out_value = s->data[s->top];
    return true;
}
