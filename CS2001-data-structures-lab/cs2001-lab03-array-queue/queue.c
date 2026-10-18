#include "queue.h"
#include <stddef.h>

void init_queue(Queue *q, int capacity) {
    // TODO: Initialize front, rear, size, and capacity fields of the queue
    (void)q;
    (void)capacity;
}

bool enqueue(Queue *q, int value) {
    // TODO: Enqueue value at the rear of the queue if not full
    (void)q;
    (void)value;
    return false;
}

bool dequeue(Queue *q, int *value) {
    // TODO: Dequeue element from the front of the queue if not empty
    (void)q;
    (void)value;
    return false;
}

bool queue_front(const Queue *q, int *value) {
    // TODO: Retrieve element at the front of the queue without removing it
    (void)q;
    (void)value;
    return false;
}

bool queue_is_empty(const Queue *q) {
    // TODO: Return true if queue is empty, false otherwise
    (void)q;
    return true;
}

bool queue_is_full(const Queue *q) {
    // TODO: Return true if queue is full, false otherwise
    (void)q;
    return false;
}
