#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int main(void) {
    printf("Running private tests: test_peek...\n");

    int val = -1;

    // NULL pointer checks
    assert(stack_peek(NULL, &val) == false);
    assert(val == -1);

    Stack s;
    init_stack(&s, 3);

    // Empty stack peek
    assert(stack_peek(&s, &val) == false);

    // NULL out_value check
    assert(stack_push(&s, 77) == true);
    assert(stack_peek(&s, NULL) == false);

    // Multiple consecutive peeks (non-mutating check)
    int peek1 = 0, peek2 = 0, peek3 = 0;
    assert(stack_peek(&s, &peek1) == true && peek1 == 77);
    assert(stack_peek(&s, &peek2) == true && peek2 == 77);
    assert(stack_peek(&s, &peek3) == true && peek3 == 77);
    assert(s.top == 0); // Stack top unchanged

    // Push another element and verify peek updates to top
    assert(stack_push(&s, 88) == true);
    assert(stack_peek(&s, &val) == true && val == 88);

    // Pop and verify peek reverts to previous top element
    int popped = 0;
    assert(stack_pop(&s, &popped) == true && popped == 88);
    assert(stack_peek(&s, &val) == true && val == 77);

    assert(stack_pop(&s, &popped) == true && popped == 77);
    assert(stack_peek(&s, &val) == false);

    free_stack(&s);
    printf("test_peek passed!\n");
    return 0;
}
