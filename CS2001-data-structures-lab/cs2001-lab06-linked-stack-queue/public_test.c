#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_sq.h"

int main(void) {
    printf("=== Running Public Tests for Linked Stack & Queue ===\n");

    // Test Stack basic operations
    printf("[1/2] Testing Linked Stack basic operations...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);
    assert(lstack_is_empty(stack) == true);
    assert(lstack_size(stack) == 0);

    assert(lstack_push(stack, 10) == true);
    assert(lstack_push(stack, 20) == true);
    assert(lstack_push(stack, 30) == true);
    assert(lstack_size(stack) == 3);
    assert(lstack_is_empty(stack) == false);

    int val = 0;
    assert(lstack_peek(stack, &val) == true);
    assert(val == 30);

    assert(lstack_pop(stack, &val) == true);
    assert(val == 30);
    assert(lstack_pop(stack, &val) == true);
    assert(val == 20);
    assert(lstack_size(stack) == 1);

    lstack_free(stack);
    printf("Linked Stack basic operations PASSED.\n");

    // Test Queue basic operations
    printf("[2/2] Testing Linked Queue basic operations...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);
    assert(lqueue_is_empty(queue) == true);
    assert(lqueue_size(queue) == 0);

    assert(lqueue_enqueue(queue, 100) == true);
    assert(lqueue_enqueue(queue, 200) == true);
    assert(lqueue_enqueue(queue, 300) == true);
    assert(lqueue_size(queue) == 3);
    assert(lqueue_is_empty(queue) == false);

    assert(lqueue_front(queue, &val) == true);
    assert(val == 100);

    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 100);
    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 200);
    assert(lqueue_size(queue) == 1);

    lqueue_free(queue);
    printf("Linked Queue basic operations PASSED.\n");

    printf("=== ALL PUBLIC TESTS PASSED ===\n");
    return 0;
}
