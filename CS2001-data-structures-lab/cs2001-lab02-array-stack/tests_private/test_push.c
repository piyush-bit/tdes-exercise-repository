#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int main(void) {
    printf("Running private tests: test_push...\n");

    // NULL pointer checks
    assert(stack_push(NULL, 100) == false);
    assert(stack_is_full(NULL) == true);
    assert(stack_is_empty(NULL) == true);

    // Invalid capacity initialization
    Stack s_invalid;
    init_stack(&s_invalid, 0);
    assert(stack_is_full(&s_invalid) == true);
    assert(stack_push(&s_invalid, 42) == false);
    free_stack(&s_invalid);

    // Normal push & capacity limits
    Stack s;
    init_stack(&s, 3);

    assert(stack_is_empty(&s) == true);
    assert(stack_is_full(&s) == false);

    assert(stack_push(&s, 101) == true);
    assert(stack_is_empty(&s) == false);
    assert(stack_is_full(&s) == false);

    assert(stack_push(&s, 102) == true);
    assert(stack_is_full(&s) == false);

    assert(stack_push(&s, 103) == true);
    assert(stack_is_full(&s) == true);

    // Overflow push attempt
    assert(stack_push(&s, 104) == false);
    assert(s.top == 2);
    assert(stack_is_full(&s) == true);

    free_stack(&s);
    printf("test_push passed!\n");
    return 0;
}
