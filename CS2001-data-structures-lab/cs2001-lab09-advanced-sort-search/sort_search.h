#ifndef SORT_SEARCH_H
#define SORT_SEARCH_H

#include <stddef.h>

/**
 * Sorts an array of integers in non-decreasing (ascending) order using the Quick Sort algorithm.
 *
 * @param arr  Pointer to the array of integers to be sorted.
 * @param size Number of elements in the array.
 *
 * Specifications:
 * - If arr is NULL or size <= 1, the function must handle it safely and return without error.
 * - Sorts the array in-place so that arr[0] <= arr[1] <= ... <= arr[size - 1].
 */
void quick_sort(int arr[], int size);

/**
 * Sorts an array of integers in non-decreasing (ascending) order using the Merge Sort algorithm.
 *
 * @param arr  Pointer to the array of integers to be sorted.
 * @param size Number of elements in the array.
 *
 * Specifications:
 * - If arr is NULL or size <= 1, the function must handle it safely and return without error.
 * - Sorts the array in-place so that arr[0] <= arr[1] <= ... <= arr[size - 1].
 */
void merge_sort(int arr[], int size);

/**
 * Searches for 'target' in an array of integers sequentially (Linear Search).
 *
 * @param arr    Pointer to the array of integers (read-only).
 * @param size   Number of elements in the array.
 * @param target The integer value to search for.
 * @return       0-based index of the first occurrence of target if found;
 *               -1 if target is not present or if parameters are invalid (arr == NULL or size <= 0).
 */
int sequential_search(const int arr[], int size, int target);

/**
 * Searches for 'target' in a sorted (ascending order) array of integers using Binary Search.
 *
 * @param arr    Pointer to the sorted array of integers (read-only).
 * @param size   Number of elements in the array.
 * @param target The integer value to search for.
 * @return       0-based index of target if found;
 *               -1 if target is not present or if parameters are invalid (arr == NULL or size <= 0).
 */
int binary_search(const int arr[], int size, int target);

#endif /* SORT_SEARCH_H */
