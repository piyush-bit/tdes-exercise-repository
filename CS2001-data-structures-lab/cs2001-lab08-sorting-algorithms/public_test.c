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

static void print_array(const int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf("]\n");
}

static void run_test(const char* name, void (*sort_func)(int[], int)) {
    printf("Running %s... ", name);
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    sort_func(arr, n);

    if (is_sorted(arr, n)) {
        printf("PASSED: ");
        print_array(arr, n);
    } else {
        printf("FAILED: ");
        print_array(arr, n);
        exit(1);
    }
}

int main(void) {
    printf("=== Public Test Suite: Sorting Algorithms ===\n");
    run_test("Bubble Sort", bubble_sort);
    run_test("Selection Sort", selection_sort);
    run_test("Insertion Sort", insertion_sort);
    run_test("Heap Sort", heap_sort);
    printf("All public tests passed successfully!\n");
    return 0;
}
