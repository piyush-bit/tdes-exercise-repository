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
    printf("--- Running Public Tests for count_zeros_and_ones ---\n");

    ASSERT_COUNTS("01011", 2, 3, "Test 1: Mixed string '01011'");
    ASSERT_COUNTS("0000", 4, 0, "Test 2: All zeros '0000'");
    ASSERT_COUNTS("111", 0, 3, "Test 3: All ones '111'");
    ASSERT_COUNTS("", 0, 0, "Test 4: Empty string ''");

    if (failed) {
        fprintf(stderr, "\nPublic tests failed!\n");
        return 1;
    }

    printf("\nAll Public Tests Passed Successfully!\n");
    return 0;
}
