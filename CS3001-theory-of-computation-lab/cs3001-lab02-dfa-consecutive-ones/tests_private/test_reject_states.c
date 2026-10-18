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
    printf("--- Running Private Tests: Reject States ---\n");

    ASSERT_EQ(accepts_three_consecutive_ones(""), 0, "Empty string ''");
    ASSERT_EQ(accepts_three_consecutive_ones("0"), 0, "Single zero '0'");
    ASSERT_EQ(accepts_three_consecutive_ones("1"), 0, "Single one '1'");
    ASSERT_EQ(accepts_three_consecutive_ones("11"), 0, "Two ones '11'");
    ASSERT_EQ(accepts_three_consecutive_ones("1101"), 0, "Input '1101'");
    ASSERT_EQ(accepts_three_consecutive_ones("11011"), 0, "Input '11011'");
    ASSERT_EQ(accepts_three_consecutive_ones("10101010"), 0, "Alternating '10101010'");
    ASSERT_EQ(accepts_three_consecutive_ones("00000"), 0, "All zeroes '00000'");
    ASSERT_EQ(accepts_three_consecutive_ones("110110110"), 0, "Repeated pairs '110110110'");
    ASSERT_EQ(accepts_three_consecutive_ones("0110110110"), 0, "Leading zero pair pattern '0110110110'");

    if (failed) {
        fprintf(stderr, "\nReject state private tests failed!\n");
        return 1;
    }

    printf("\nAll Reject State Private Tests Passed Successfully!\n");
    return 0;
}
