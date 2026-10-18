#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_lists.h"

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("[FAIL SLL] %s (%s:%d)\n", msg, __FILE__, __LINE__); \
            return 1; \
        } \
    } while(0)

int main(void) {
    printf("Running private SLL test suite...\n");

    SLLNode *head = NULL;

    // Test 1: Empty list behavior
    TEST_ASSERT(sll_get_length(head) == 0, "Length of NULL list should be 0");
    TEST_ASSERT(sll_find(head, 42) == NULL, "Find on NULL list should return NULL");
    head = sll_delete_by_value(head, 42);
    TEST_ASSERT(head == NULL, "Deleting from NULL list should return NULL");
    head = sll_delete_at_index(head, 0);
    TEST_ASSERT(head == NULL, "Deleting index 0 from NULL list should return NULL");
    sll_to_array(head, NULL);
    sll_free_list(NULL);

    // Test 2: Node creation
    SLLNode *n1 = sll_create_node(100);
    TEST_ASSERT(n1 != NULL, "sll_create_node returned NULL");
    TEST_ASSERT(n1->data == 100, "sll_create_node data wrong");
    TEST_ASSERT(n1->next == NULL, "sll_create_node next should be NULL");
    free(n1);

    // Test 3: Insertions (head, tail, index)
    head = sll_insert_at_head(NULL, 20); // [20]
    head = sll_insert_at_head(head, 10); // [10, 20]
    head = sll_insert_at_tail(head, 40); // [10, 20, 40]
    head = sll_insert_at_index(head, 30, 2); // [10, 20, 30, 40]
    head = sll_insert_at_index(head, 5, 0); // [5, 10, 20, 30, 40]
    head = sll_insert_at_index(head, 50, 5); // [5, 10, 20, 30, 40, 50]

    // Invalid index insertions should leave list unchanged
    head = sll_insert_at_index(head, 999, -1);
    head = sll_insert_at_index(head, 999, 100);

    TEST_ASSERT(sll_get_length(head) == 6, "SLL length should be 6 after insertions");

    int expected[6] = {5, 10, 20, 30, 40, 50};
    int actual[6] = {0};
    sll_to_array(head, actual);
    for (int i = 0; i < 6; i++) {
        TEST_ASSERT(actual[i] == expected[i], "SLL element mismatch after insertions");
    }

    // Test 4: Search
    TEST_ASSERT(sll_find(head, 30) != NULL && sll_find(head, 30)->data == 30, "sll_find failed for 30");
    TEST_ASSERT(sll_find(head, 999) == NULL, "sll_find failed for nonexistent value");

    // Test 5: Deletions
    // Delete head (value 5)
    head = sll_delete_by_value(head, 5); // [10, 20, 30, 40, 50]
    TEST_ASSERT(sll_get_length(head) == 5, "Length wrong after deleting head by value");

    // Delete tail (index 4 -> value 50)
    head = sll_delete_at_index(head, 4); // [10, 20, 30, 40]
    TEST_ASSERT(sll_get_length(head) == 4, "Length wrong after deleting tail by index");

    // Delete middle (value 30)
    head = sll_delete_by_value(head, 30); // [10, 20, 40]
    TEST_ASSERT(sll_get_length(head) == 3, "Length wrong after deleting middle by value");

    // Delete non-existent value / invalid indices
    head = sll_delete_by_value(head, 999);
    head = sll_delete_at_index(head, -1);
    head = sll_delete_at_index(head, 10);
    TEST_ASSERT(sll_get_length(head) == 3, "Length changed after invalid deletions");

    int expected_final[3] = {10, 20, 40};
    int actual_final[3] = {0};
    sll_to_array(head, actual_final);
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT(actual_final[i] == expected_final[i], "Final SLL content mismatch");
    }

    sll_free_list(head);
    printf("Private SLL test suite passed!\n");
    return 0;
}
