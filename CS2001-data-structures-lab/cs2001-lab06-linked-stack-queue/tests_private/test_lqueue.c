#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_sq.h"

static void test_queue_creation_and_empty(void) {
    printf("  [Queue Test 1] Creation and Empty Check...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);
    assert(lqueue_is_empty(queue) == true);
    assert(lqueue_size(queue) == 0);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    lqueue_free(queue);
}

static void test_queue_enqueue_dequeue_order(void) {
    printf("  [Queue Test 2] FIFO Order and Size Tracking...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);

    int elements[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(elements) / sizeof(elements[0]);

    for (size_t i = 0; i < count; i++) {
        assert(lqueue_enqueue(queue, elements[i]) == true);
        assert(lqueue_size(queue) == i + 1);
        assert(lqueue_is_empty(queue) == false);
        assert(queue->rear != NULL);
        assert(queue->rear->data == elements[i]);
    }

    int val = 0;
    for (size_t i = 0; i < count; i++) {
        assert(lqueue_dequeue(queue, &val) == true);
        assert(val == elements[i]);
        assert(lqueue_size(queue) == count - 1 - i);
    }

    assert(lqueue_is_empty(queue) == true);
    assert(lqueue_size(queue) == 0);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    lqueue_free(queue);
}

static void test_queue_front(void) {
    printf("  [Queue Test 3] Front Non-Destructive Behavior...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);

    assert(lqueue_enqueue(queue, 100) == true);
    assert(lqueue_enqueue(queue, 200) == true);

    int val1 = 0, val2 = 0;
    assert(lqueue_front(queue, &val1) == true);
    assert(val1 == 100);
    assert(lqueue_front(queue, &val2) == true);
    assert(val2 == 100);
    assert(lqueue_size(queue) == 2);

    lqueue_free(queue);
}

static void test_queue_empty_dequeue_front(void) {
    printf("  [Queue Test 4] Dequeue and Front on Empty Queue...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);

    int val = 999;
    assert(lqueue_dequeue(queue, &val) == false);
    assert(val == 999);

    assert(lqueue_front(queue, &val) == false);
    assert(val == 999);

    lqueue_free(queue);
}

static void test_queue_null_arguments(void) {
    printf("  [Queue Test 5] Handling NULL Arguments Safely...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);

    int val = 0;
    assert(lqueue_enqueue(NULL, 10) == false);
    assert(lqueue_dequeue(NULL, &val) == false);
    assert(lqueue_dequeue(queue, NULL) == false);
    assert(lqueue_front(NULL, &val) == false);
    assert(lqueue_front(queue, NULL) == false);
    assert(lqueue_is_empty(NULL) == true);
    assert(lqueue_size(NULL) == 0);

    // lqueue_free NULL check
    lqueue_free(NULL);

    lqueue_free(queue);
}

static void test_queue_interleaved_enqueue_dequeue(void) {
    printf("  [Queue Test 6] Interleaved Enqueue and Dequeue Operations...\n");
    LinkedQueue* queue = lqueue_create();
    assert(queue != NULL);

    assert(lqueue_enqueue(queue, 1) == true);
    assert(lqueue_enqueue(queue, 2) == true);

    int val = 0;
    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 1);

    assert(lqueue_enqueue(queue, 3) == true);
    assert(lqueue_enqueue(queue, 4) == true);

    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 2);
    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 3);
    assert(lqueue_dequeue(queue, &val) == true);
    assert(val == 4);

    assert(lqueue_is_empty(queue) == true);
    assert(queue->front == NULL);
    assert(queue->rear == NULL);
    lqueue_free(queue);
}

int main(void) {
    printf("=== Running Private Tests: Linked Queue ===\n");
    test_queue_creation_and_empty();
    test_queue_enqueue_dequeue_order();
    test_queue_front();
    test_queue_empty_dequeue_front();
    test_queue_null_arguments();
    test_queue_interleaved_enqueue_dequeue();
    printf("=== ALL LINKED QUEUE PRIVATE TESTS PASSED ===\n");
    return 0;
}
