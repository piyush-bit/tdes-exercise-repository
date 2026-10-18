#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_lists.h"

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("[FAIL] %s (%s:%d)\n", msg, __FILE__, __LINE__); \
            return 1; \
        } \
    } while(0)

static int test_sll_basic(void) {
    SLLNode *head = NULL;
    TEST_ASSERT(sll_get_length(head) == 0, "SLL length should be 0 for empty list");

    head = sll_insert_at_tail(head, 10);
    head = sll_insert_at_tail(head, 20);
    head = sll_insert_at_head(head, 5);
    // Expected SLL: 5 -> 10 -> 20

    TEST_ASSERT(sll_get_length(head) == 3, "SLL length should be 3");

    int arr[3] = {0};
    sll_to_array(head, arr);
    TEST_ASSERT(arr[0] == 5 && arr[1] == 10 && arr[2] == 20, "SLL elements ordering mismatch");

    SLLNode *found = sll_find(head, 10);
    TEST_ASSERT(found != NULL && found->data == 10, "SLL find should locate value 10");

    head = sll_delete_by_value(head, 10);
    TEST_ASSERT(sll_get_length(head) == 2, "SLL length should be 2 after deleting 10");

    int arr2[2] = {0};
    sll_to_array(head, arr2);
    TEST_ASSERT(arr2[0] == 5 && arr2[1] == 20, "SLL elements ordering mismatch after deletion");

    sll_free_list(head);
    return 0;
}

static int test_dll_basic(void) {
    DLLNode *head = NULL;
    TEST_ASSERT(dll_get_length(head) == 0, "DLL length should be 0 for empty list");

    head = dll_insert_at_tail(head, 100);
    head = dll_insert_at_tail(head, 200);
    head = dll_insert_at_head(head, 50);
    // Expected DLL: 50 <-> 100 <-> 200

    TEST_ASSERT(dll_get_length(head) == 3, "DLL length should be 3");
    TEST_ASSERT(head->prev == NULL, "DLL head prev should be NULL");
    TEST_ASSERT(head->next != NULL && head->next->prev == head, "DLL pointers corrupted");

    int arr[3] = {0};
    dll_to_array(head, arr);
    TEST_ASSERT(arr[0] == 50 && arr[1] == 100 && arr[2] == 200, "DLL elements ordering mismatch");

    DLLNode *found = dll_find(head, 200);
    TEST_ASSERT(found != NULL && found->data == 200, "DLL find should locate value 200");

    head = dll_delete_at_index(head, 1); // delete 100
    TEST_ASSERT(dll_get_length(head) == 2, "DLL length should be 2 after deletion");

    int arr2[2] = {0};
    dll_to_array(head, arr2);
    TEST_ASSERT(arr2[0] == 50 && arr2[1] == 200, "DLL elements mismatch after deleting index 1");
    TEST_ASSERT(head->next->prev == head, "DLL prev pointer check failed after deletion");

    dll_free_list(head);
    return 0;
}

int main(void) {
    printf("Running public tests...\n");
    if (test_sll_basic() != 0) {
        printf("Public SLL test failed!\n");
        return 1;
    }
    if (test_dll_basic() != 0) {
        printf("Public DLL test failed!\n");
        return 1;
    }
    printf("All public tests passed!\n");
    return 0;
}
