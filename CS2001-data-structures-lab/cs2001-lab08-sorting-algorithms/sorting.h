#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

/**
 * @brief Sorts an array of integers in ascending order using Bubble Sort.
 *
 * Bubble Sort repeatedly steps through the list, compares adjacent elements,
 * and swaps them if they are in the wrong order.
 *
 * @param arr Array of integers to sort. If NULL or n <= 1, no operation is performed.
 * @param n   Number of elements in the array.
 */
void bubble_sort(int arr[], int n);

/**
 * @brief Sorts an array of integers in ascending order using Selection Sort.
 *
 * Selection Sort repeatedly finds the minimum element from the unsorted subarray
 * and places it at the beginning.
 *
 * @param arr Array of integers to sort. If NULL or n <= 1, no operation is performed.
 * @param n   Number of elements in the array.
 */
void selection_sort(int arr[], int n);

/**
 * @brief Sorts an array of integers in ascending order using Insertion Sort.
 *
 * Insertion Sort builds the final sorted array one item at a time by repeatedly
 * inserting an unsorted element into its proper place among already sorted elements.
 *
 * @param arr Array of integers to sort. If NULL or n <= 1, no operation is performed.
 * @param n   Number of elements in the array.
 */
void insertion_sort(int arr[], int n);

/**
 * @brief Sorts an array of integers in ascending order using Heap Sort.
 *
 * Heap Sort converts the array into a max-heap structure, repeatedly extracts
 * the maximum element (root), places it at the end, and heapifies the reduced heap.
 *
 * @param arr Array of integers to sort. If NULL or n <= 1, no operation is performed.
 * @param n   Number of elements in the array.
 */
void heap_sort(int arr[], int n);

#endif /* SORTING_H */
