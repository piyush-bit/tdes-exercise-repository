#include "sorting.h"
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    // TODO: Implement Bubble Sort algorithm
    // 1. Guard against arr == NULL or n <= 1
    // 2. Perform passes, comparing adjacent elements and swapping if out of order
    // 3. Optional: add early termination if no swaps occur in a pass
    (void)arr;
    (void)n;
}

void selection_sort(int arr[], int n) {
    // TODO: Implement Selection Sort algorithm
    // 1. Guard against arr == NULL or n <= 1
    // 2. Iterate through the array, finding the minimum element in the unsorted portion
    // 3. Swap the minimum element with the first unsorted element
    (void)arr;
    (void)n;
}

void insertion_sort(int arr[], int n) {
    // TODO: Implement Insertion Sort algorithm
    // 1. Guard against arr == NULL or n <= 1
    // 2. Iterate from index 1 to n-1
    // 3. Insert arr[i] into its correct sorted position in arr[0...i-1]
    (void)arr;
    (void)n;
}

void heap_sort(int arr[], int n) {
    // TODO: Implement Heap Sort algorithm
    // 1. Guard against arr == NULL or n <= 1
    // 2. Helper function heapify(arr, n, i) to maintain max-heap property
    // 3. Build max-heap starting from last non-leaf node down to 0
    // 4. Extract elements one by one from heap, swapping root with end element and heapifying
    (void)arr;
    (void)n;
}
