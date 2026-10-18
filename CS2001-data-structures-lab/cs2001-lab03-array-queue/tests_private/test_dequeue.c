#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int main(void) {
    printf("--- Running Private Test: Dequeue ---\n");

    Queue q;
    init_queue(&q, 4);

    int val = -1;
    // Dequeue on empty queue
    assert(dequeue(&q, &val) == false);
    assert(dequeue(NULL, &val) == false);

    // Enqueue 4 elements: 100, 200, 300, 400
    assert(enqueue(&q, 100) == true);
    assert(enqueue(&q, 200) == true);
    assert(enqueue(&q, 300) == true);
    assert(enqueue(&q, 400) == true);

    // Dequeue with NULL pointer value parameter (should succeed and decrement size)
    assert(dequeue(&q, NULL) == true); // Dequeues 100
    assert(q.size == 3);

    // Dequeue remaining in order
    assert(dequeue(&q, &val) == true);
    assert(val == 200);
    assert(dequeue(&q, &val) == true);
    assert(val == 300);
    assert(dequeue(&q, &val) == true);
    assert(val == 400);

    assert(queue_is_empty(&q) == true);
    assert(dequeue(&q, &val) == false);

    // Test circular wrap-around dequeue
    assert(enqueue(&q, 10) == true);
    assert(enqueue(&q, 20) == true);
    assert(enqueue(&q, 30) == true);
    assert(dequeue(&q, &val) == true); // 10
    assert(val == 10);
    assert(enqueue(&q, 40) == true);
    assert(enqueue(&q, 50) == true); // Queue full with 20, 30, 40, 50

    assert(dequeue(&q, &val) == true); assert(val == 20);
    assert(dequeue(&q, &val) == true); assert(val == 30);
    assert(dequeue(&q, &val) == true); assert(val == 40);
    assert(dequeue(&q, &val) == true); assert(val == 50);
    assert(queue_is_empty(&q) == true);

    printf("--- Private Test Dequeue PASSED ---\n");
    return 0;
}
