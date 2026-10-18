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
    // Test 1: Standard traversal
    int src[6] = {1, 2, 3, 4, 5, 6};
    int dest[6] = {0};
    int res = traverse_array(src, 6, dest, 6);
    ASSERT_EQ(res, 6, "Traverse standard 6-element array");
    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(dest[i], src[i], "Element copy match");
    }

    // Test 2: Size 0 array
    res = traverse_array(src, 0, dest, 6);
    ASSERT_EQ(res, 0, "Traverse size 0 array");

    // Test 3: Insufficient destination capacity
    res = traverse_array(src, 6, dest, 4);
    ASSERT_EQ(res, -1, "Destination capacity smaller than size should fail (-1)");

    // Test 4: NULL pointers
    res = traverse_array(NULL, 6, dest, 6);
    ASSERT_EQ(res, -1, "NULL source array should fail (-1)");

    res = traverse_array(src, 6, NULL, 6);
    ASSERT_EQ(res, -1, "NULL destination array should fail (-1)");

    // Test 5: Negative size
    res = traverse_array(src, -2, dest, 6);
    ASSERT_EQ(res, -1, "Negative size should fail (-1)");

    if (failed) {
        fprintf(stderr, "Traversal Private Tests FAILED\n");
        return 1;
    }

    printf("Traversal Private Tests PASSED\n");
    return 0;
}
