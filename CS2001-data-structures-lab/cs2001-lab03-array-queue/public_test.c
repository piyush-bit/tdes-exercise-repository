#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int main(void) {
    printf("=== Running Public Queue Tests ===\n");

    Queue q;
    init_queue(&q, 5);

    assert(queue_is_empty(&q) == true);
    assert(queue_is_full(&q) == false);
    assert(q.size == 0);
    assert(q.capacity == 5);
    printf("[PASS] init_queue & empty check\n");

    assert(enqueue(&q, 10) == true);
    assert(enqueue(&q, 20) == true);
    assert(enqueue(&q, 30) == true);
    assert(q.size == 3);
    printf("[PASS] enqueue (10, 20, 30)\n");

    int val = 0;
    assert(queue_front(&q, &val) == true);
    assert(val == 10);
    assert(q.size == 3);
    printf("[PASS] queue_front returns 10 without removing\n");

    assert(dequeue(&q, &val) == true);
    assert(val == 10);
    assert(dequeue(&q, &val) == true);
    assert(val == 20);
    assert(q.size == 1);
    printf("[PASS] dequeue (10, 20)\n");

    assert(dequeue(&q, &val) == true);
    assert(val == 30);
    assert(queue_is_empty(&q) == true);
    assert(q.size == 0);
    printf("[PASS] dequeue 30, queue empty\n");

    printf("=== All Public Tests Passed! ===\n");
    return 0;
}
