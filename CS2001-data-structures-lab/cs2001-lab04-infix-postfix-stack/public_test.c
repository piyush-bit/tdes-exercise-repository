#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "infix_postfix.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void assert_conversion(const char *infix, const char *expected_postfix) {
    char postfix[512];
    int status = infix_to_postfix(infix, postfix);
    if (status == 0 && strcmp(postfix, expected_postfix) == 0) {
        printf(" [PASS] Conversion: \"%s\" -> \"%s\"\n", infix, postfix);
        tests_passed++;
    } else {
        printf(" [FAIL] Conversion: \"%s\"\n", infix);
        printf("        Expected: \"%s\"\n", expected_postfix);
        printf("        Got:      \"%s\" (status %d)\n", status == 0 ? postfix : "ERROR", status);
        tests_failed++;
    }
}

static void assert_evaluation(const char *postfix, int expected_val) {
    int result = 0;
    int status = evaluate_postfix(postfix, &result);
    if (status == 0 && result == expected_val) {
        printf(" [PASS] Evaluation: \"%s\" = %d\n", postfix, result);
        tests_passed++;
    } else {
        printf(" [FAIL] Evaluation: \"%s\"\n", postfix);
        printf("        Expected: %d\n", expected_val);
        printf("        Got:      %d (status %d)\n", result, status);
        tests_failed++;
    }
}

int main(void) {
    printf("=== CS2001 Lab 04 Public Test Suite ===\n\n");

    printf("--- Testing Infix to Postfix Conversion ---\n");
    assert_conversion("A + B * C", "A B C * +");
    assert_conversion("(A + B) * C", "A B + C *");
    assert_conversion("3 + 4 * 2", "3 4 2 * +");
    assert_conversion("2 ^ 3 ^ 2", "2 3 2 ^ ^");

    printf("\n--- Testing Postfix Evaluation ---\n");
    assert_evaluation("3 4 +", 7);
    assert_evaluation("3 4 2 * +", 11);
    assert_evaluation("10 20 + 3 *", 90);
    assert_evaluation("2 3 2 ^ ^", 512);

    printf("\n=======================================\n");
    printf("Summary: %d passed, %d failed\n", tests_passed, tests_failed);

    return (tests_failed == 0) ? 0 : 1;
}
