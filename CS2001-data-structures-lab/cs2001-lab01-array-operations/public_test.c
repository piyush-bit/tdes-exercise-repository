#include "array_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int failed = 0;

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "[FAIL] %s: Expected %d, got %d\n", msg, (expected), (actual)); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", msg); \
        } \
    } while (0)

void test_public_traversal(void) {
    printf("--- Running Public Traversal Test ---\n");
    int src[5] = {10, 20, 30, 40, 50};
    int dest[5] = {0};

    int result = traverse_array(src, 5, dest, 5);
    ASSERT_EQ(result, 5, "traverse_array returns copied element count");
    ASSERT_EQ(dest[0], 10, "traverse_array dest[0] matches src[0]");
    ASSERT_EQ(dest[4], 50, "traverse_array dest[4] matches src[4]");
}

void test_public_insertion(void) {
    printf("--- Running Public Insertion Test ---\n");
    int arr[10] = {10, 30, 40};
    int size = 3;

    size = insert_at_index(arr, size, 10, 1, 20);
    ASSERT_EQ(size, 4, "insert_at_index returns new array size");
    ASSERT_EQ(arr[0], 10, "insert_at_index arr[0] is unchanged");
    ASSERT_EQ(arr[1], 20, "insert_at_index arr[1] has inserted element");
    ASSERT_EQ(arr[2], 30, "insert_at_index arr[2] shifted right");
    ASSERT_EQ(arr[3], 40, "insert_at_index arr[3] shifted right");
}

void test_public_deletion(void) {
    printf("--- Running Public Deletion Test ---\n");
    int arr[10] = {10, 20, 30, 40};
    int size = 4;

    size = delete_at_index(arr, size, 1);
    ASSERT_EQ(size, 3, "delete_at_index returns updated size");
    ASSERT_EQ(arr[0], 10, "delete_at_index arr[0] unchanged");
    ASSERT_EQ(arr[1], 30, "delete_at_index arr[1] shifted left");
    ASSERT_EQ(arr[2], 40, "delete_at_index arr[2] shifted left");
}

void test_public_search(void) {
    printf("--- Running Public Search Test ---\n");
    int arr[5] = {5, 15, 25, 35, 45};
    int idx = find_element(arr, 5, 25);
    ASSERT_EQ(idx, 2, "find_element returns correct index for present element");

    idx = find_element(arr, 5, 100);
    ASSERT_EQ(idx, -1, "find_element returns -1 for absent element");
}

int main(void) {
    test_public_traversal();
    test_public_insertion();
    test_public_deletion();
    test_public_search();

    if (failed) {
        fprintf(stderr, "\nPublic tests failed!\n");
        return 1;
    }

    printf("\nAll Public Tests Passed Successfully!\n");
    return 0;
}
