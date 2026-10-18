#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int main(void) {
    printf("Running private tests: test_pop...\n");

    int val = -1;

    // NULL pointer checks
    assert(stack_pop(NULL, &val) == false);
    assert(val == -1);

    Stack s;
    init_stack(&s, 4);

    // NULL out_value check
    assert(stack_push(&s, 50) == true);
    assert(stack_pop(&s, NULL) == false);

    // Empty stack pop (underflow) check
    int dummy = 999;
    Stack empty_s;
    init_stack(&empty_s, 2);
    assert(stack_pop(&empty_s, &dummy) == false);
    assert(dummy == 999);
    free_stack(&empty_s);

    // Clear s
    assert(stack_pop(&s, &val) == true);
    assert(val == 50);
    assert(stack_is_empty(&s) == true);

    // LIFO Ordering test
    assert(stack_push(&s, 10) == true);
    assert(stack_push(&s, 20) == true);
    assert(stack_push(&s, 30) == true);
    assert(stack_push(&s, 40) == true);

    assert(stack_pop(&s, &val) == true && val == 40);
    assert(stack_pop(&s, &val) == true && val == 30);

    // Interleaved push/pop
    assert(stack_push(&s, 99) == true);
    assert(stack_pop(&s, &val) == true && val == 99);

    assert(stack_pop(&s, &val) == true && val == 20);
    assert(stack_pop(&s, &val) == true && val == 10);

    // Underflow after emptying
    assert(stack_pop(&s, &val) == false);
    assert(stack_is_empty(&s) == true);

    free_stack(&s);
    printf("test_pop passed!\n");
    return 0;
}
