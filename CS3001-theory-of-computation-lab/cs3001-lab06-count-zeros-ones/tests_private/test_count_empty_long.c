#include "count_symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failed = 0;

#define ASSERT_COUNTS(str, exp_0, exp_1, test_name) \
    do { \
        int c0 = -1, c1 = -1; \
        count_zeros_and_ones((str), &c0, &c1); \
        if (c0 != (exp_0) || c1 != (exp_1)) { \
            fprintf(stderr, "[FAIL] %s: expected (count_0=%d, count_1=%d), got (count_0=%d, count_1=%d)\n", \
                    (test_name), (exp_0), (exp_1), c0, c1); \
            failed = 1; \
        } else { \
            printf("[PASS] %s\n", (test_name)); \
        } \
    } while (0)

int main(void) {
    printf("--- Running Private Test: Empty and Long Strings ---\n");

    // 1. Empty string
    ASSERT_COUNTS("", 0, 0, "Empty string ''");

    // 2. NULL string handle safely
    ASSERT_COUNTS(NULL, 0, 0, "NULL string pointer");

    // 3. NULL pointer parameters (partial pointers)
    int c0 = -1, c1 = -1;
    count_zeros_and_ones("01011", &c0, NULL);
    if (c0 != 2) {
        fprintf(stderr, "[FAIL] NULL count_1 pointer: expected count_0=2, got %d\n", c0);
        failed = 1;
    } else {
        printf("[PASS] NULL count_1 pointer handled\n");
    }

    c0 = -1; c1 = -1;
    count_zeros_and_ones("01011", NULL, &c1);
    if (c1 != 3) {
        fprintf(stderr, "[FAIL] NULL count_0 pointer: expected count_1=3, got %d\n", c1);
        failed = 1;
    } else {
        printf("[PASS] NULL count_0 pointer handled\n");
    }

    // 4. Long string (1000 zeros + 1000 ones)
    char *long_str = (char *)malloc(2001);
    if (long_str) {
        memset(long_str, '0', 1000);
        memset(long_str + 1000, '1', 1000);
        long_str[2000] = '\0';
        ASSERT_COUNTS(long_str, 1000, 1000, "Long string (1000 '0's + 1000 '1's)");
        free(long_str);
    }

    // 5. Very long string (10000 zeros)
    char *zeros_str = (char *)malloc(10001);
    if (zeros_str) {
        memset(zeros_str, '0', 10000);
        zeros_str[10000] = '\0';
        ASSERT_COUNTS(zeros_str, 10000, 0, "Very long string (10000 '0's)");
        free(zeros_str);
    }

    if (failed) {
        fprintf(stderr, "\nEmpty and long strings test failed!\n");
        return 1;
    }

    printf("\nEmpty and Long Strings Test Passed!\n");
    return 0;
}
