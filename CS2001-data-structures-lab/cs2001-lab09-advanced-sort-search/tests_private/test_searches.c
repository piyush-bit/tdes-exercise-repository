#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort_search.h"

static bool test_sequential_search(void) {
    printf("Running Sequential Search Tests...\n");

    // NULL array check
    if (sequential_search(NULL, 5, 10) != -1) {
        printf("  [FAIL] Sequential Search NULL array did not return -1\n");
        return false;
    }

    // Invalid size check
    int dummy[] = {1, 2, 3};
    if (sequential_search(dummy, 0, 1) != -1 || sequential_search(dummy, -5, 1) != -1) {
        printf("  [FAIL] Sequential Search invalid size did not return -1\n");
        return false;
    }

    // Normal array
    int arr[] = {45, -10, 0, 88, 12, 33, -10};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Search first element
    if (sequential_search(arr, size, 45) != 0) {
        printf("  [FAIL] Sequential Search first element failed\n");
        return false;
    }

    // Search last element
    if (sequential_search(arr, size, -10) != 1) { // First occurrence of -10 is index 1
        printf("  [FAIL] Sequential Search duplicate/first occurrence failed\n");
        return false;
    }

    // Search middle element
    if (sequential_search(arr, size, 88) != 3) {
        printf("  [FAIL] Sequential Search middle element failed\n");
        return false;
    }

    // Search missing element
    if (sequential_search(arr, size, 999) != -1) {
        printf("  [FAIL] Sequential Search missing target failed\n");
        return false;
    }

    printf("  [PASS] Sequential Search All Tests Passed\n");
    return true;
}

static bool test_binary_search(void) {
    printf("Running Binary Search Tests...\n");

    // NULL array check
    if (binary_search(NULL, 5, 10) != -1) {
        printf("  [FAIL] Binary Search NULL array did not return -1\n");
        return false;
    }

    // Invalid size check
    int dummy[] = {1, 2, 3};
    if (binary_search(dummy, 0, 1) != -1 || binary_search(dummy, -1, 1) != -1) {
        printf("  [FAIL] Binary Search invalid size did not return -1\n");
        return false;
    }

    // Single element array
    int single[] = {15};
    if (binary_search(single, 1, 15) != 0 || binary_search(single, 1, 10) != -1) {
        printf("  [FAIL] Binary Search single element failed\n");
        return false;
    }

    // Sorted array with negatives
    int sorted[] = {-50, -20, -10, 0, 5, 15, 30, 45, 100};
    int size = sizeof(sorted) / sizeof(sorted[0]);

    // First element
    if (binary_search(sorted, size, -50) != 0) {
        printf("  [FAIL] Binary Search first element (-50) failed\n");
        return false;
    }

    // Last element
    if (binary_search(sorted, size, 100) != size - 1) {
        printf("  [FAIL] Binary Search last element (100) failed\n");
        return false;
    }

    // Middle elements
    if (binary_search(sorted, size, 0) != 3 || binary_search(sorted, size, 15) != 5) {
        printf("  [FAIL] Binary Search middle elements failed\n");
        return false;
    }

    // Missing targets (smaller than min, larger than max, intermediate missing)
    if (binary_search(sorted, size, -100) != -1 ||
        binary_search(sorted, size, 500) != -1 ||
        binary_search(sorted, size, 7) != -1) {
        printf("  [FAIL] Binary Search missing target checks failed\n");
        return false;
    }

    // Large sorted array
    int large_size = 1000;
    int *large_arr = (int *)malloc((size_t)large_size * sizeof(int));
    if (large_arr == NULL) return false;
    for (int i = 0; i < large_size; i++) {
        large_arr[i] = i * 2; // Even numbers 0, 2, 4, ..., 1998
    }

    bool large_ok = true;
    for (int i = 0; i < large_size; i++) {
        if (binary_search(large_arr, large_size, i * 2) != i) {
            large_ok = false;
            break;
        }
        if (binary_search(large_arr, large_size, i * 2 + 1) != -1) {
            large_ok = false;
            break;
        }
    }
    free(large_arr);

    if (!large_ok) {
        printf("  [FAIL] Binary Search large array failed\n");
        return false;
    }

    printf("  [PASS] Binary Search All Tests Passed\n");
    return true;
}

int main(void) {
    printf("=== Private Test Suite: Searches ===\n");
    bool seq_ok = test_sequential_search();
    bool bin_ok = test_binary_search();

    if (seq_ok && bin_ok) {
        printf("RESULT: PASS\n");
        return 0;
    } else {
        printf("RESULT: FAIL\n");
        return 1;
    }
}
