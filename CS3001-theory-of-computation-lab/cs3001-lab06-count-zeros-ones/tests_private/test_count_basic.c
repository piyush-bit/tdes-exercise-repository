#include "count_symbols.h"
#include <stdio.h>
#include <stdlib.h>

static int failed = 0;

#define ASSERT_COUNTS(str, exp_0, exp_1, test_name) \
    do { \
        int c0 = -1, c1 = -1; \
        count_zeros_and_ones((str), &c0, &c1); \
        if (c0 != (exp_0) || c1 != (exp_1)) { \
            fprintf(stderr, "[FAIL] %s: input=\"%s\" -> expected (count_0=%d, count_1=%d), got (count_0=%d, count_1=%d)\n", \
                    (test_name), (str) ? (str) : "NULL", (exp_0), (exp_1), c0, c1); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", (test_name)); \
        } \
    } while (0)

int main(void) {
    printf("--- Running Private Test: Basic Symbol Counting ---\n");

    ASSERT_COUNTS("0", 1, 0, "Single zero '0'");
    ASSERT_COUNTS("1", 0, 1, "Single one '1'");
    ASSERT_COUNTS("000", 3, 0, "Multiple zeros '000'");
    ASSERT_COUNTS("1111", 0, 4, "Multiple ones '1111'");
    ASSERT_COUNTS("01011", 2, 3, "Mixed string '01011'");
    ASSERT_COUNTS("11001100", 4, 4, "Balanced binary '11001100'");
    ASSERT_COUNTS("101010", 3, 3, "Alternating '101010'");

    if (failed) {
        fprintf(stderr, "\nBasic symbol counting test failed!\n");
        return 1;
    }

    printf("\nBasic Symbol Counting Test Passed!\n");
    return 0;
}
