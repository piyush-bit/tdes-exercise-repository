#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int main(void) {
    printf("--- Running Private Test: Enqueue ---\n");

    Queue q;
    init_queue(&q, 3);

    assert(enqueue(NULL, 100) == false);

    assert(enqueue(&q, 10) == true);
    assert(q.size == 1);
    assert(enqueue(&q, 20) == true);
    assert(q.size == 2);
    assert(enqueue(&q, 30) == true);
    assert(q.size == 3);
    assert(queue_is_full(&q) == true);

    // Enqueue on full queue
    assert(enqueue(&q, 40) == false);
    assert(q.size == 3);

    // Circular wrap-around test
    int val = 0;
    assert(dequeue(&q, &val) == true); // removes 10, front becomes 1, size becomes 2
    assert(val == 10);
    assert(queue_is_full(&q) == false);

    assert(enqueue(&q, 40) == true); // enqueues 40 at index 0 (wrapped), size becomes 3
    assert(q.size == 3);
    assert(queue_is_full(&q) == true);
    assert(enqueue(&q, 50) == false);

    // Test invalid capacity fallback
    Queue q2;
    init_queue(&q2, -5);
    assert(q2.capacity == MAX_CAPACITY);

    printf("--- Private Test Enqueue PASSED ---\n");
    return 0;
}
