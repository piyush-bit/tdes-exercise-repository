#include "consecutive_ones.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    printf("--- Running Public DFA Tests ---\n");

    ASSERT_EQ(accepts_three_consecutive_ones("111"), 1, "Input '111' should be accepted (1)");
    ASSERT_EQ(accepts_three_consecutive_ones("01110"), 1, "Input '01110' should be accepted (1)");
    ASSERT_EQ(accepts_three_consecutive_ones("1101"), 0, "Input '1101' should be rejected (0)");
    ASSERT_EQ(accepts_three_consecutive_ones("000"), 0, "Input '000' should be rejected (0)");
    ASSERT_EQ(accepts_three_consecutive_ones("11"), 0, "Input '11' should be rejected (0)");

    if (failed) {
        fprintf(stderr, "\nPublic tests failed!\n");
        return 1;
    }

    printf("\nAll Public Tests Passed Successfully!\n");
    return 0;
}
