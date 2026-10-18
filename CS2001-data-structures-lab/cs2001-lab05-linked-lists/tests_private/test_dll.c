#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_lists.h"

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("[FAIL DLL] %s (%s:%d)\n", msg, __FILE__, __LINE__); \
            return 1; \
        } \
    } while(0)

static bool verify_dll_integrity(const DLLNode *head, size_t expected_len) {
    if (head == NULL) {
        return expected_len == 0;
    }
    if (head->prev != NULL) {
        return false;
    }

    const DLLNode *curr = head;
    size_t count = 0;
    while (curr != NULL) {
        count++;
        if (curr->next != NULL) {
            if (curr->next->prev != curr) {
                return false;
            }
        }
        if (curr->prev != NULL) {
            if (curr->prev->next != curr) {
                return false;
            }
        }
        curr = curr->next;
    }
    return count == expected_len;
}

int main(void) {
    printf("Running private DLL test suite...\n");

    DLLNode *head = NULL;

    // Test 1: Empty list behavior
    TEST_ASSERT(dll_get_length(head) == 0, "Length of NULL list should be 0");
    TEST_ASSERT(dll_find(head, 100) == NULL, "Find on NULL DLL should return NULL");
    head = dll_delete_by_value(head, 100);
    TEST_ASSERT(head == NULL, "Deleting from NULL DLL should return NULL");
    head = dll_delete_at_index(head, 0);
    TEST_ASSERT(head == NULL, "Deleting index 0 from NULL DLL should return NULL");
    dll_to_array(head, NULL);
    dll_free_list(NULL);

    // Test 2: Node creation
    DLLNode *n1 = dll_create_node(250);
    TEST_ASSERT(n1 != NULL, "dll_create_node returned NULL");
    TEST_ASSERT(n1->data == 250, "dll_create_node data wrong");
    TEST_ASSERT(n1->prev == NULL && n1->next == NULL, "dll_create_node pointers should be NULL");
    free(n1);

    // Test 3: Insertions (head, tail, index)
    head = dll_insert_at_head(NULL, 30); // [30]
    TEST_ASSERT(verify_dll_integrity(head, 1), "Integrity failed after insert head on empty");

    head = dll_insert_at_head(head, 10); // [10, 30]
    TEST_ASSERT(verify_dll_integrity(head, 2), "Integrity failed after insert head");

    head = dll_insert_at_tail(head, 50); // [10, 30, 50]
    TEST_ASSERT(verify_dll_integrity(head, 3), "Integrity failed after insert tail");

    head = dll_insert_at_index(head, 20, 1); // [10, 20, 30, 50]
    TEST_ASSERT(verify_dll_integrity(head, 4), "Integrity failed after insert at index 1");

    head = dll_insert_at_index(head, 40, 3); // [10, 20, 30, 40, 50]
    TEST_ASSERT(verify_dll_integrity(head, 5), "Integrity failed after insert at index 3");

    head = dll_insert_at_index(head, 60, 5); // [10, 20, 30, 40, 50, 60]
    TEST_ASSERT(verify_dll_integrity(head, 6), "Integrity failed after insert at tail via index");

    // Invalid index insertions should leave list unchanged
    head = dll_insert_at_index(head, 999, -1);
    head = dll_insert_at_index(head, 999, 100);
    TEST_ASSERT(verify_dll_integrity(head, 6), "Integrity changed after invalid index insertions");

    int expected[6] = {10, 20, 30, 40, 50, 60};
    int actual[6] = {0};
    dll_to_array(head, actual);
    for (int i = 0; i < 6; i++) {
        TEST_ASSERT(actual[i] == expected[i], "DLL element mismatch after insertions");
    }

    // Test 4: Search
    TEST_ASSERT(dll_find(head, 40) != NULL && dll_find(head, 40)->data == 40, "dll_find failed for 40");
    TEST_ASSERT(dll_find(head, 777) == NULL, "dll_find failed for nonexistent value");

    // Test 5: Deletions
    // Delete head (value 10)
    head = dll_delete_by_value(head, 10); // [20, 30, 40, 50, 60]
    TEST_ASSERT(verify_dll_integrity(head, 5), "DLL integrity broken after deleting head by value");

    // Delete tail (index 4 -> 60)
    head = dll_delete_at_index(head, 4); // [20, 30, 40, 50]
    TEST_ASSERT(verify_dll_integrity(head, 4), "DLL integrity broken after deleting tail by index");

    // Delete middle (value 30)
    head = dll_delete_by_value(head, 30); // [20, 40, 50]
    TEST_ASSERT(verify_dll_integrity(head, 3), "DLL integrity broken after deleting middle by value");

    // Delete at index 1 (value 40)
    head = dll_delete_at_index(head, 1); // [20, 50]
    TEST_ASSERT(verify_dll_integrity(head, 2), "DLL integrity broken after deleting index 1");

    int expected_final[2] = {20, 50};
    int actual_final[2] = {0};
    dll_to_array(head, actual_final);
    for (int i = 0; i < 2; i++) {
        TEST_ASSERT(actual_final[i] == expected_final[i], "Final DLL content mismatch");
    }

    dll_free_list(head);
    printf("Private DLL test suite passed!\n");
    return 0;
}
