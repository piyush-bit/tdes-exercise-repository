#include <stdio.h>
#include <stdlib.h>
#include "divisible_by_2.h"

static int tests_run = 0;
static int tests_passed = 0;

static void check(const char *input, int expected, const char *test_name) {
    tests_run++;
    int actual = is_binary_divisible_by_2(input);
    if (actual == expected) {
        printf("  [PASS] %s (\"%s\" -> %d)\n", test_name, input ? input : "NULL", expected);
        tests_passed++;
    } else {
        printf("  [FAIL] %s (\"%s\" -> expected %d, got %d)\n", test_name, input ? input : "NULL", expected, actual);
    }
}

int main(void) {
    printf("Running Public Test Suite for is_binary_divisible_by_2...\n");
    check("1010", 1, "Even binary 1010");
    check("1011", 0, "Odd binary 1011");
    check("0", 1, "Single digit 0");
    check("1", 0, "Single digit 1");

    printf("Public Tests Summary: %d/%d passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
