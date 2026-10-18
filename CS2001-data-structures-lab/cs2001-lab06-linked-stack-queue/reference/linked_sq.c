#include "linked_sq.h"
#include <stdlib.h>

LinkedStack* lstack_create(void) {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if (!stack) {
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool lstack_push(LinkedStack* stack, int value) {
    if (!stack) {
        return false;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return false;
    }
    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    return true;
}

bool lstack_pop(LinkedStack* stack, int* value) {
    if (!stack || !value || stack->top == NULL) {
        return false;
    }
    Node* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return true;
}

bool lstack_peek(const LinkedStack* stack, int* value) {
    if (!stack || !value || stack->top == NULL) {
        return false;
    }
    *value = stack->top->data;
    return true;
}

bool lstack_is_empty(const LinkedStack* stack) {
    if (!stack) {
        return true;
    }
    return stack->top == NULL;
}

size_t lstack_size(const LinkedStack* stack) {
    if (!stack) {
        return 0;
    }
    return stack->size;
}

void lstack_free(LinkedStack* stack) {
    if (!stack) {
        return;
    }
    Node* current = stack->top;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

LinkedQueue* lqueue_create(void) {
    LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if (!queue) {
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

bool lqueue_enqueue(LinkedQueue* queue, int value) {
    if (!queue) {
        return false;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return false;
    }
    new_node->data = value;
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
    return true;
}

bool lqueue_dequeue(LinkedQueue* queue, int* value) {
    if (!queue || !value || queue->front == NULL) {
        return false;
    }
    Node* temp = queue->front;
    *value = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return true;
}

bool lqueue_front(const LinkedQueue* queue, int* value) {
    if (!queue || !value || queue->front == NULL) {
        return false;
    }
    *value = queue->front->data;
    return true;
}

bool lqueue_is_empty(const LinkedQueue* queue) {
    if (!queue) {
        return true;
    }
    return queue->front == NULL;
}

size_t lqueue_size(const LinkedQueue* queue) {
    if (!queue) {
        return 0;
    }
    return queue->size;
}

void lqueue_free(LinkedQueue* queue) {
    if (!queue) {
        return;
    }
    Node* current = queue->front;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}
