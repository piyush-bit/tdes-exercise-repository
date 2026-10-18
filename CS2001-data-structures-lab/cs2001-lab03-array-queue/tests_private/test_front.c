#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

int main(void) {
    printf("--- Running Private Test: Front ---\n");

    Queue q;
    init_queue(&q, 5);

    int val = -1;
    // Front on empty queue
    assert(queue_front(&q, &val) == false);
    assert(queue_front(NULL, &val) == false);

    assert(enqueue(&q, 55) == true);
    assert(enqueue(&q, 65) == true);

    // Front should return 55 without modifying size
    assert(queue_front(&q, &val) == true);
    assert(val == 55);
    assert(q.size == 2);

    // Calling front again should return same value 55
    assert(queue_front(&q, &val) == true);
    assert(val == 55);

    // Calling front with NULL value parameter on non-empty queue
    assert(queue_front(&q, NULL) == true);

    // Dequeue 55
    int dequeued = 0;
    assert(dequeue(&q, &dequeued) == true);
    assert(dequeued == 55);

    // Front should now be 65
    assert(queue_front(&q, &val) == true);
    assert(val == 65);

    // Dequeue 65
    assert(dequeue(&q, &dequeued) == true);
    assert(dequeued == 65);

    // Queue is empty, front should return false
    assert(queue_is_empty(&q) == true);
    assert(queue_front(&q, &val) == false);

    printf("--- Private Test Front PASSED ---\n");
    return 0;
}
