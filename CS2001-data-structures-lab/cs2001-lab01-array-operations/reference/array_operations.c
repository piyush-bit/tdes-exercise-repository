#include "array_operations.h"
#include <stdio.h>

int traverse_array(const int src[], int size, int dest[], int dest_capacity) {
    if (src == NULL || dest == NULL || size < 0 || dest_capacity < size) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return size;
}

int insert_at_index(int arr[], int size, int capacity, int index, int element) {
    if (arr == NULL || capacity <= 0 || size < 0 || size >= capacity) {
        return -1;
    }
    if (index < 0 || index > size) {
        return -1;
    }

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = element;
    return size + 1;
}

int delete_at_index(int arr[], int size, int index) {
    if (arr == NULL || size <= 0 || index < 0 || index >= size) {
        return -1;
    }

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    return size - 1;
}

int find_element(const int arr[], int size, int target) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}
