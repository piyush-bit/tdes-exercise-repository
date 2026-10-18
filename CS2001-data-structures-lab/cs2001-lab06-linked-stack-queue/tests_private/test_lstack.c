#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_sq.h"

static void test_stack_creation_and_empty(void) {
    printf("  [Stack Test 1] Creation and Empty Check...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);
    assert(lstack_is_empty(stack) == true);
    assert(lstack_size(stack) == 0);
    assert(stack->top == NULL);
    lstack_free(stack);
}

static void test_stack_push_pop_order(void) {
    printf("  [Stack Test 2] LIFO Order and Size Tracking...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);

    int elements[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(elements) / sizeof(elements[0]);

    for (size_t i = 0; i < count; i++) {
        assert(lstack_push(stack, elements[i]) == true);
        assert(lstack_size(stack) == i + 1);
        assert(lstack_is_empty(stack) == false);
    }

    int val = 0;
    for (size_t i = count; i > 0; i--) {
        assert(lstack_pop(stack, &val) == true);
        assert(val == elements[i - 1]);
        assert(lstack_size(stack) == i - 1);
    }

    assert(lstack_is_empty(stack) == true);
    assert(lstack_size(stack) == 0);
    lstack_free(stack);
}

static void test_stack_peek(void) {
    printf("  [Stack Test 3] Peek Non-Destructive Behavior...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);

    assert(lstack_push(stack, 100) == true);
    assert(lstack_push(stack, 200) == true);

    int val1 = 0, val2 = 0;
    assert(lstack_peek(stack, &val1) == true);
    assert(val1 == 200);
    assert(lstack_peek(stack, &val2) == true);
    assert(val2 == 200);
    assert(lstack_size(stack) == 2);

    lstack_free(stack);
}

static void test_stack_empty_pop_peek(void) {
    printf("  [Stack Test 4] Pop and Peek on Empty Stack...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);

    int val = 999;
    assert(lstack_pop(stack, &val) == false);
    assert(val == 999);

    assert(lstack_peek(stack, &val) == false);
    assert(val == 999);

    lstack_free(stack);
}

static void test_stack_null_arguments(void) {
    printf("  [Stack Test 5] Handling NULL Arguments Safely...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);

    int val = 0;
    assert(lstack_push(NULL, 10) == false);
    assert(lstack_pop(NULL, &val) == false);
    assert(lstack_pop(stack, NULL) == false);
    assert(lstack_peek(NULL, &val) == false);
    assert(lstack_peek(stack, NULL) == false);
    assert(lstack_is_empty(NULL) == true);
    assert(lstack_size(NULL) == 0);

    // lstack_free NULL check
    lstack_free(NULL);

    lstack_free(stack);
}

static void test_stack_interleaved_push_pop(void) {
    printf("  [Stack Test 6] Interleaved Push and Pop Operations...\n");
    LinkedStack* stack = lstack_create();
    assert(stack != NULL);

    assert(lstack_push(stack, 1) == true);
    assert(lstack_push(stack, 2) == true);

    int val = 0;
    assert(lstack_pop(stack, &val) == true);
    assert(val == 2);

    assert(lstack_push(stack, 3) == true);
    assert(lstack_push(stack, 4) == true);

    assert(lstack_pop(stack, &val) == true);
    assert(val == 4);
    assert(lstack_pop(stack, &val) == true);
    assert(val == 3);
    assert(lstack_pop(stack, &val) == true);
    assert(val == 1);

    assert(lstack_is_empty(stack) == true);
    lstack_free(stack);
}

int main(void) {
    printf("=== Running Private Tests: Linked Stack ===\n");
    test_stack_creation_and_empty();
    test_stack_push_pop_order();
    test_stack_peek();
    test_stack_empty_pop_peek();
    test_stack_null_arguments();
    test_stack_interleaved_push_pop();
    printf("=== ALL LINKED STACK PRIVATE TESTS PASSED ===\n");
    return 0;
}
