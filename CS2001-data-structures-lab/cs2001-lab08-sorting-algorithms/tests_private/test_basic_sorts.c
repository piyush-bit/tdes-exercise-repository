#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sorting.h"

static bool is_sorted(const int arr[], int n) {
    if (arr == NULL || n <= 1) return true;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

static void assert_test(bool condition, const char* test_name) {
    if (condition) {
        printf("  [PASS] %s\n", test_name);
    } else {
        printf("  [FAIL] %s\n", test_name);
        exit(1);
    }
}

typedef void (*sort_func_t)(int[], int);

static void test_sort_algorithm(const char* algo_name, sort_func_t sort_func) {
    printf("--- Testing %s ---\n", algo_name);

    // Test 1: NULL pointer and small n
    sort_func(NULL, 5);
    int single[] = {42};
    sort_func(single, 1);
    assert_test(single[0] == 42, "Single element array");

    int zero_len[] = {1, 2, 3};
    sort_func(zero_len, 0);
    assert_test(zero_len[0] == 1, "Zero length array");

    // Test 2: Already sorted array
    int sorted[] = {10, 20, 30, 40, 50};
    sort_func(sorted, 5);
    assert_test(is_sorted(sorted, 5), "Already sorted array");

    // Test 3: Reverse sorted array
    int reverse[] = {50, 40, 30, 20, 10};
    sort_func(reverse, 5);
    assert_test(is_sorted(reverse, 5) && reverse[0] == 10 && reverse[4] == 50, "Reverse sorted array");

    // Test 4: Array with duplicates
    int duplicates[] = {5, 2, 5, 1, 2, 5, 0};
    sort_func(duplicates, 7);
    assert_test(is_sorted(duplicates, 7), "Array with duplicate elements");

    // Test 5: Negative numbers
    int negatives[] = {-5, 12, -30, 0, 8, -2};
    sort_func(negatives, 6);
    assert_test(is_sorted(negatives, 6) && negatives[0] == -30 && negatives[5] == 12, "Array with negative numbers");

    // Test 6: Larger pseudo-random array
    const int N = 500;
    int* large_arr = (int*)malloc(N * sizeof(int));
    if (!large_arr) {
        perror("malloc failed");
        exit(1);
    }
    // Seed PRNG deterministically
    srand(12345);
    for (int i = 0; i < N; i++) {
        large_arr[i] = (rand() % 20000) - 10000;
    }
    sort_func(large_arr, N);
    assert_test(is_sorted(large_arr, N), "Large 500-element array sort");
    free(large_arr);
}

int main(void) {
    printf("=== Private Test Suite: Basic Sorts (Bubble, Selection, Insertion) ===\n");
    test_sort_algorithm("Bubble Sort", bubble_sort);
    test_sort_algorithm("Selection Sort", selection_sort);
    test_sort_algorithm("Insertion Sort", insertion_sort);
    printf("All Basic Sorts private tests passed!\n");
    return 0;
}
