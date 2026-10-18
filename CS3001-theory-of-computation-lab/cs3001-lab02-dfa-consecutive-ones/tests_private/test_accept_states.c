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
    printf("--- Running Private Tests: Accept States ---\n");

    ASSERT_EQ(accepts_three_consecutive_ones("111"), 1, "Exact '111'");
    ASSERT_EQ(accepts_three_consecutive_ones("1111"), 1, "Four ones '1111'");
    ASSERT_EQ(accepts_three_consecutive_ones("01110"), 1, "Enclosed '01110'");
    ASSERT_EQ(accepts_three_consecutive_ones("000111000"), 1, "Padded zeroes '000111000'");
    ASSERT_EQ(accepts_three_consecutive_ones("10111"), 1, "Prefix '10' then '111'");
    ASSERT_EQ(accepts_three_consecutive_ones("111000111"), 1, "Multiple '111' occurrences");
    ASSERT_EQ(accepts_three_consecutive_ones("01010111"), 1, "Late '111' match");
    ASSERT_EQ(accepts_three_consecutive_ones("1110101010"), 1, "Early '111' match with long tail");
    ASSERT_EQ(accepts_three_consecutive_ones("110111011"), 1, "Interrupted then match '110111011'");

    if (failed) {
        fprintf(stderr, "\nAccept state private tests failed!\n");
        return 1;
    }

    printf("\nAll Accept State Private Tests Passed Successfully!\n");
    return 0;
}
