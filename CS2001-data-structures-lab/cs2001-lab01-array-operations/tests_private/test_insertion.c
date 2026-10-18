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
    int arr[5] = {10, 20, 30};
    int size = 3;
    int capacity = 5;

    // Test 1: Insert at beginning (index 0)
    size = insert_at_index(arr, size, capacity, 0, 5);
    ASSERT_EQ(size, 4, "Insert at index 0 returns size 4");
    ASSERT_EQ(arr[0], 5, "arr[0] is 5");
    ASSERT_EQ(arr[1], 10, "arr[1] is 10");
    ASSERT_EQ(arr[2], 20, "arr[2] is 20");
    ASSERT_EQ(arr[3], 30, "arr[3] is 30");

    // Test 2: Insert at end (index == size)
    size = insert_at_index(arr, size, capacity, 4, 40);
    ASSERT_EQ(size, 5, "Insert at index 4 returns size 5");
    ASSERT_EQ(arr[4], 40, "arr[4] is 40");

    // Test 3: Insert into full array (size == capacity)
    int err = insert_at_index(arr, size, capacity, 2, 99);
    ASSERT_EQ(err, -1, "Insert when size == capacity should fail (-1)");

    // Test 4: Invalid index < 0
    int arr2[5] = {10, 20};
    err = insert_at_index(arr2, 2, 5, -1, 99);
    ASSERT_EQ(err, -1, "Insert at negative index should fail (-1)");

    // Test 5: Invalid index > size
    err = insert_at_index(arr2, 2, 5, 3, 99);
    ASSERT_EQ(err, -1, "Insert at index > size should fail (-1)");

    // Test 6: NULL array or invalid capacity
    err = insert_at_index(NULL, 2, 5, 0, 99);
    ASSERT_EQ(err, -1, "Insert into NULL array should fail (-1)");

    err = insert_at_index(arr2, 2, 0, 0, 99);
    ASSERT_EQ(err, -1, "Insert with capacity <= 0 should fail (-1)");

    if (failed) {
        fprintf(stderr, "Insertion Private Tests FAILED\n");
        return 1;
    }

    printf("Insertion Private Tests PASSED\n");
    return 0;
}
