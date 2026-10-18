#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort_search.h"

static bool is_sorted(const int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

static void print_array(const int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i == size - 1) ? "" : ", ");
    }
    printf("]\n");
}

int main(void) {
    int passed = 0;
    int total = 0;

    printf("=========================================\n");
    printf(" CS2001 Lab 09: Public Test Suite\n");
    printf("=========================================\n\n");

    // Test 1: Quick Sort basic array
    total++;
    printf("Test %d: Quick Sort - Basic Unsorted Array\n", total);
    int arr1[] = {5, 2, 9, 1, 7, 6, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("  Original: "); print_array(arr1, size1);
    quick_sort(arr1, size1);
    printf("  Sorted:   "); print_array(arr1, size1);
    if (is_sorted(arr1, size1) && arr1[0] == 1 && arr1[size1 - 1] == 9) {
        printf("  Result: PASS\n\n");
        passed++;
    } else {
        printf("  Result: FAIL\n\n");
    }

    // Test 2: Merge Sort basic array
    total++;
    printf("Test %d: Merge Sort - Basic Unsorted Array\n", total);
    int arr2[] = {12, 11, 13, 5, 6, 7};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("  Original: "); print_array(arr2, size2);
    merge_sort(arr2, size2);
    printf("  Sorted:   "); print_array(arr2, size2);
    if (is_sorted(arr2, size2) && arr2[0] == 5 && arr2[size2 - 1] == 13) {
        printf("  Result: PASS\n\n");
        passed++;
    } else {
        printf("  Result: FAIL\n\n");
    }

    // Test 3: Sequential Search
    total++;
    printf("Test %d: Sequential Search - Existing & Missing Targets\n", total);
    int arr3[] = {10, 20, 30, 7, 50};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int idx1 = sequential_search(arr3, size3, 7);
    int idx2 = sequential_search(arr3, size3, 99);
    printf("  Searching for 7: found at index %d (expected 3)\n", idx1);
    printf("  Searching for 99: found at index %d (expected -1)\n", idx2);
    if (idx1 == 3 && idx2 == -1) {
        printf("  Result: PASS\n\n");
        passed++;
    } else {
        printf("  Result: FAIL\n\n");
    }

    // Test 4: Binary Search
    total++;
    printf("Test %d: Binary Search - Existing & Missing Targets\n", total);
    int arr4[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int b_idx1 = binary_search(arr4, size4, 23);
    int b_idx2 = binary_search(arr4, size4, 100);
    printf("  Searching for 23: found at index %d (expected 5)\n", b_idx1);
    printf("  Searching for 100: found at index %d (expected -1)\n", b_idx2);
    if (b_idx1 == 5 && b_idx2 == -1) {
        printf("  Result: PASS\n\n");
        passed++;
    } else {
        printf("  Result: FAIL\n\n");
    }

    printf("-----------------------------------------\n");
    printf("Summary: %d / %d public tests passed.\n", passed, total);
    printf("-----------------------------------------\n");

    return (passed == total) ? 0 : 1;
}
