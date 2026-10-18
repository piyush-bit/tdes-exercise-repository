#include "../array_operations.h"
#include <stdio.h>
#include <stdlib.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[PRIVATE FAIL] %s: Expected %d, got %d\n", msg, (expected), (actual)); \
            failed = 1; \
        } \
    } while (0)

int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int size = 5;

    // Test 1: Delete from beginning (index 0)
    size = delete_at_index(arr, size, 0);
    ASSERT_EQ(size, 4, "Delete index 0 returns size 4");
    ASSERT_EQ(arr[0], 20, "arr[0] is now 20");
    ASSERT_EQ(arr[1], 30, "arr[1] is now 30");

    // Test 2: Delete from middle (index 1)
    size = delete_at_index(arr, size, 1);
    ASSERT_EQ(size, 3, "Delete index 1 returns size 3");
    ASSERT_EQ(arr[0], 20, "arr[0] is 20");
    ASSERT_EQ(arr[1], 40, "arr[1] is 40");
    ASSERT_EQ(arr[2], 50, "arr[2] is 50");

    // Test 3: Delete from end (index size - 1)
    size = delete_at_index(arr, size, 2);
    ASSERT_EQ(size, 2, "Delete last element returns size 2");
    ASSERT_EQ(arr[0], 20, "arr[0] is 20");
    ASSERT_EQ(arr[1], 40, "arr[1] is 40");

    // Test 4: Invalid index >= size
    int err = delete_at_index(arr, size, 2);
    ASSERT_EQ(err, -1, "Delete at index >= size should fail (-1)");

    // Test 5: Invalid index < 0
    err = delete_at_index(arr, size, -1);
    ASSERT_EQ(err, -1, "Delete at negative index should fail (-1)");

    // Test 6: Delete from empty array
    int empty_arr[2];
    err = delete_at_index(empty_arr, 0, 0);
    ASSERT_EQ(err, -1, "Delete from empty array (size 0) should fail (-1)");

    // Test 7: NULL array
    err = delete_at_index(NULL, 5, 0);
    ASSERT_EQ(err, -1, "Delete from NULL array should fail (-1)");

    // Test 8: Searching / find_element edge cases
    int search_arr[6] = {100, 200, 300, 200, 400, 500};
    int idx = find_element(search_arr, 6, 200);
    ASSERT_EQ(idx, 1, "find_element returns first occurrence index");

    idx = find_element(search_arr, 6, 999);
    ASSERT_EQ(idx, -1, "find_element returns -1 when target not found");

    idx = find_element(NULL, 6, 200);
    ASSERT_EQ(idx, -1, "find_element returns -1 when arr is NULL");

    if (failed) {
        fprintf(stderr, "Deletion Private Tests FAILED\n");
        return 1;
    }

    printf("Deletion Private Tests PASSED\n");
    return 0;
}
