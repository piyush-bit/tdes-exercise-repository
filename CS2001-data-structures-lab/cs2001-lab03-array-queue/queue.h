#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define MAX_CAPACITY 100

typedef struct {
    int data[MAX_CAPACITY];
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

/**
 * Initializes the Queue struct with given capacity.
 * @param q Pointer to Queue struct
 * @param capacity Maximum number of elements the queue can hold (capped at MAX_CAPACITY)
 */
void init_queue(Queue *q, int capacity);

/**
 * Adds an element to the rear of the queue.
 * @param q Pointer to Queue struct
 * @param value Integer value to enqueue
 * @return true if successful, false if queue is full or NULL pointer
 */
bool enqueue(Queue *q, int value);

/**
 * Removes an element from the front of the queue and stores it in *value.
 * @param q Pointer to Queue struct
 * @param value Pointer to store the dequeued value
 * @return true if successful, false if queue is empty or NULL q pointer
 */
bool dequeue(Queue *q, int *value);

/**
 * Retrieves the front element of the queue without removing it.
 * @param q Pointer to Queue struct
 * @param value Pointer to store the front value
 * @return true if successful, false if queue is empty or NULL q pointer
 */
bool queue_front(const Queue *q, int *value);

/**
 * Checks whether the queue is empty.
 * @param q Pointer to Queue struct
 * @return true if empty or NULL q, false otherwise
 */
bool queue_is_empty(const Queue *q);

/**
 * Checks whether the queue is full.
 * @param q Pointer to Queue struct
 * @return true if full, false otherwise (returns false if q is NULL)
 */
bool queue_is_full(const Queue *q);

#endif // QUEUE_H
