#include "queue.h"
#include <stddef.h>

void init_queue(Queue *q, int capacity) {
    if (q == NULL) {
        return;
    }
    if (capacity <= 0 || capacity > MAX_CAPACITY) {
        q->capacity = MAX_CAPACITY;
    } else {
        q->capacity = capacity;
    }
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool queue_is_empty(const Queue *q) {
    if (q == NULL) {
        return true;
    }
    return q->size == 0;
}

bool queue_is_full(const Queue *q) {
    if (q == NULL) {
        return false;
    }
    return q->size >= q->capacity;
}

bool enqueue(Queue *q, int value) {
    if (q == NULL || queue_is_full(q)) {
        return false;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

bool dequeue(Queue *q, int *value) {
    if (q == NULL || queue_is_empty(q)) {
        return false;
    }
    if (value != NULL) {
        *value = q->data[q->front];
    }
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return true;
}

bool queue_front(const Queue *q, int *value) {
    if (q == NULL || queue_is_empty(q)) {
        return false;
    }
    if (value != NULL) {
        *value = q->data[q->front];
    }
    return true;
}
