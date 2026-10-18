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

static bool test_quick_sort(void) {
    printf("Running Quick Sort Tests...\n");

    // NULL array check
    quick_sort(NULL, 5);

    // Empty array check
    int empty_arr[1] = {0};
    quick_sort(empty_arr, 0);

    // Single element
    int single_arr[] = {42};
    quick_sort(single_arr, 1);
    if (single_arr[0] != 42) {
        printf("  [FAIL] Quick Sort single element failed\n");
        return false;
    }

    // Already sorted
    int sorted_arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    quick_sort(sorted_arr, 8);
    if (!is_sorted(sorted_arr, 8)) {
        printf("  [FAIL] Quick Sort already sorted array failed\n");
        return false;
    }

    // Reverse sorted
    int rev_arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    quick_sort(rev_arr, 11);
    if (!is_sorted(rev_arr, 11) || rev_arr[0] != 0 || rev_arr[10] != 10) {
        printf("  [FAIL] Quick Sort reverse sorted array failed\n");
        return false;
    }

    // Duplicates and negatives
    int dup_neg[] = {-10, 5, 0, -10, 2, 5, -3, 0};
    int dup_neg_size = sizeof(dup_neg) / sizeof(dup_neg[0]);
    quick_sort(dup_neg, dup_neg_size);
    if (!is_sorted(dup_neg, dup_neg_size) || dup_neg[0] != -10 || dup_neg[dup_neg_size - 1] != 5) {
        printf("  [FAIL] Quick Sort duplicates and negatives failed\n");
        return false;
    }

    // Large array
    int large_size = 1000;
    int *large_arr = (int *)malloc((size_t)large_size * sizeof(int));
    if (large_arr == NULL) return false;
    srand(12345);
    for (int i = 0; i < large_size; i++) {
        large_arr[i] = rand() % 5000 - 2500;
    }
    quick_sort(large_arr, large_size);
    bool large_ok = is_sorted(large_arr, large_size);
    free(large_arr);
    if (!large_ok) {
        printf("  [FAIL] Quick Sort large array failed\n");
        return false;
    }

    printf("  [PASS] Quick Sort All Tests Passed\n");
    return true;
}

static bool test_merge_sort(void) {
    printf("Running Merge Sort Tests...\n");

    // NULL array check
    merge_sort(NULL, 5);

    // Empty array check
    int empty_arr[1] = {0};
    merge_sort(empty_arr, 0);

    // Single element
    int single_arr[] = {99};
    merge_sort(single_arr, 1);
    if (single_arr[0] != 99) {
        printf("  [FAIL] Merge Sort single element failed\n");
        return false;
    }

    // Already sorted
    int sorted_arr[] = {10, 20, 30, 40, 50};
    merge_sort(sorted_arr, 5);
    if (!is_sorted(sorted_arr, 5)) {
        printf("  [FAIL] Merge Sort already sorted array failed\n");
        return false;
    }

    // Reverse sorted
    int rev_arr[] = {100, 80, 60, 40, 20, 0, -20};
    merge_sort(rev_arr, 7);
    if (!is_sorted(rev_arr, 7) || rev_arr[0] != -20 || rev_arr[6] != 100) {
        printf("  [FAIL] Merge Sort reverse sorted array failed\n");
        return false;
    }

    // Duplicates and negatives
    int dup_neg[] = {7, -1, 7, 3, -1, 0, 7, -5};
    int dup_neg_size = sizeof(dup_neg) / sizeof(dup_neg[0]);
    merge_sort(dup_neg, dup_neg_size);
    if (!is_sorted(dup_neg, dup_neg_size) || dup_neg[0] != -5 || dup_neg[dup_neg_size - 1] != 7) {
        printf("  [FAIL] Merge Sort duplicates and negatives failed\n");
        return false;
    }

    // Large array
    int large_size = 1000;
    int *large_arr = (int *)malloc((size_t)large_size * sizeof(int));
    if (large_arr == NULL) return false;
    srand(54321);
    for (int i = 0; i < large_size; i++) {
        large_arr[i] = rand() % 10000 - 5000;
    }
    merge_sort(large_arr, large_size);
    bool large_ok = is_sorted(large_arr, large_size);
    free(large_arr);
    if (!large_ok) {
        printf("  [FAIL] Merge Sort large array failed\n");
        return false;
    }

    printf("  [PASS] Merge Sort All Tests Passed\n");
    return true;
}

int main(void) {
    printf("=== Private Test Suite: Advanced Sorts ===\n");
    bool q_ok = test_quick_sort();
    bool m_ok = test_merge_sort();

    if (q_ok && m_ok) {
        printf("RESULT: PASS\n");
        return 0;
    } else {
        printf("RESULT: FAIL\n");
        return 1;
    }
}
