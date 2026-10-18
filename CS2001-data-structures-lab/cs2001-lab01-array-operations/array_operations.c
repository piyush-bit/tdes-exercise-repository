#include "array_operations.h"
#include <stdio.h>

int traverse_array(const int src[], int size, int dest[], int dest_capacity) {
    // TODO: Validate input parameters (check for NULL pointers, negative size, dest_capacity < size)
    // TODO: Copy each element from src[i] to dest[i]
    // TODO: Return the number of elements copied (size), or -1 on error
    (void)src;
    (void)size;
    (void)dest;
    (void)dest_capacity;
    return -1;
}

int insert_at_index(int arr[], int size, int capacity, int index, int element) {
    // TODO: Validate input parameters (check for NULL pointer, capacity <= 0, size < 0, size >= capacity, invalid index)
    // TODO: Shift elements starting from end of array down to index one position to the right
    // TODO: Place 'element' at arr[index]
    // TODO: Return the updated array size (size + 1), or -1 on error
    (void)arr;
    (void)size;
    (void)capacity;
    (void)index;
    (void)element;
    return -1;
}

int delete_at_index(int arr[], int size, int index) {
    // TODO: Validate input parameters (check for NULL pointer, size <= 0, index < 0, index >= size)
    // TODO: Shift elements starting from index + 1 to size - 1 one position to the left
    // TODO: Return the updated array size (size - 1), or -1 on error
    (void)arr;
    (void)size;
    (void)index;
    return -1;
}

int find_element(const int arr[], int size, int target) {
    // TODO: Validate input parameters (check for NULL pointer, size <= 0)
    // TODO: Iterate over array and return index of first matching element
    // TODO: Return -1 if element is not found or parameters are invalid
    (void)arr;
    (void)size;
    (void)target;
    return -1;
}
