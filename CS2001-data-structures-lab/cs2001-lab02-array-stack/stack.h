#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

void init_stack(Stack *s, int capacity);
void free_stack(Stack *s);

bool stack_is_empty(const Stack *s);
bool stack_is_full(const Stack *s);

bool stack_push(Stack *s, int value);
bool stack_pop(Stack *s, int *out_value);
bool stack_peek(const Stack *s, int *out_value);

#endif // STACK_H
