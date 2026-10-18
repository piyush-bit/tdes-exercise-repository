#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int main(void) {
    printf("Running public tests for Stack...\n");

    Stack s;
    init_stack(&s, 5);

    assert(stack_is_empty(&s) == true);
    assert(stack_is_full(&s) == false);

    assert(stack_push(&s, 10) == true);
    assert(stack_is_empty(&s) == false);

    assert(stack_push(&s, 20) == true);
    assert(stack_push(&s, 30) == true);

    int val = 0;
    assert(stack_peek(&s, &val) == true);
    assert(val == 30);

    assert(stack_pop(&s, &val) == true);
    assert(val == 30);

    assert(stack_pop(&s, &val) == true);
    assert(val == 20);

    assert(stack_pop(&s, &val) == true);
    assert(val == 10);

    assert(stack_is_empty(&s) == true);
    assert(stack_pop(&s, &val) == false);

    free_stack(&s);
    printf("Public tests passed successfully!\n");
    return 0;
}
