#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

int main(void) {
    printf("=== Private Test Suite: Heap Sort ===\n");

    // Test 1: NULL and boundary sizes
    heap_sort(NULL, 10);
    int single[] = {99};
    heap_sort(single, 1);
    assert_test(single[0] == 99, "Single element heap sort");

    int zero_len[] = {5, 4, 3};
    heap_sort(zero_len, 0);
    assert_test(zero_len[0] == 5, "Zero length heap sort");

    // Test 2: Two elements swapped and ordered
    int pair1[] = {2, 1};
    heap_sort(pair1, 2);
    assert_test(is_sorted(pair1, 2) && pair1[0] == 1 && pair1[1] == 2, "Two elements reverse");

    int pair2[] = {1, 2};
    heap_sort(pair2, 2);
    assert_test(is_sorted(pair2, 2) && pair2[0] == 1 && pair2[1] == 2, "Two elements sorted");

    // Test 3: Reverse sorted array
    int reverse[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
    heap_sort(reverse, 10);
    assert_test(is_sorted(reverse, 10) && reverse[0] == 0 && reverse[9] == 99, "Reverse sorted array");

    // Test 4: All duplicate values
    int dupes[] = {7, 7, 7, 7, 7, 7, 7};
    heap_sort(dupes, 7);
    assert_test(is_sorted(dupes, 7) && dupes[0] == 7 && dupes[6] == 7, "All duplicate elements");

    // Test 5: Mixed positive, negative, zero
    int mixed[] = {-10, 50, 0, -50, 100, -100, 25};
    heap_sort(mixed, 7);
    assert_test(is_sorted(mixed, 7) && mixed[0] == -100 && mixed[6] == 100, "Mixed positive/negative array");

    // Test 6: Large dataset test (5000 elements)
    const int N = 5000;
    int* large_arr = (int*)malloc(N * sizeof(int));
    if (!large_arr) {
        perror("malloc failed");
        exit(1);
    }
    srand(54321);
    for (int i = 0; i < N; i++) {
        large_arr[i] = (rand() % 100000) - 50000;
    }
    heap_sort(large_arr, N);
    assert_test(is_sorted(large_arr, N), "Large 5000-element heap sort");
    free(large_arr);

    printf("All Heap Sort private tests passed!\n");
    return 0;
}
