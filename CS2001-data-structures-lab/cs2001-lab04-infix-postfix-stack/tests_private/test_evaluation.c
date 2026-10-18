#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infix_postfix.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void check_evaluation(const char *postfix, int expected_val) {
    int result = 0;
    int status = evaluate_postfix(postfix, &result);
    if (status == 0 && result == expected_val) {
        tests_passed++;
    } else {
        printf(" [FAIL] Evaluation: \"%s\"\n", postfix);
        printf("        Expected: %d\n", expected_val);
        printf("        Got:      %d (status %d)\n", result, status);
        tests_failed++;
    }
}

static void check_evaluation_error(const char *postfix) {
    int result = 0;
    int status = evaluate_postfix(postfix, &result);
    if (status != 0) {
        tests_passed++;
    } else {
        printf(" [FAIL] Expected error for evaluation: \"%s\", but got result %d (status 0)\n", postfix, result);
        tests_failed++;
    }
}

int main(void) {
    printf("=== Private Test Suite: Postfix Evaluation ===\n");

    // Basic arithmetic
    check_evaluation("3 4 +", 7);
    check_evaluation("50 20 -", 30);
    check_evaluation("6 7 *", 42);
    check_evaluation("20 4 /", 5);
    check_evaluation("10 3 %", 1);

    // Multi-digit numbers & negative numbers
    check_evaluation("100 200 +", 300);
    check_evaluation("500 50 /", 10);
    check_evaluation("-5 10 +", 5);
    check_evaluation("10 -5 *", -50);

    // Exponentiation
    check_evaluation("2 10 ^", 1024);
    check_evaluation("3 2 3 ^ ^", 6561); // 3 ^ (2^3) = 3 ^ 8 = 6561

    // Complex combined expression
    check_evaluation("3 4 2 * 1 5 - 2 3 ^ ^ / +", 3);

    // Error handling
    check_evaluation_error("10 0 /");       // Division by zero
    check_evaluation_error("10 0 %");       // Modulo by zero
    check_evaluation_error("2 -3 ^");       // Negative exponent
    check_evaluation_error("5 +");          // Insufficient operands
    check_evaluation_error("+");            // Insufficient operands
    check_evaluation_error("5 10 15 +");    // Too many operands
    check_evaluation_error("");             // Empty expression
    check_evaluation_error("10 foo +");     // Invalid token

    printf("Evaluation Private Tests: %d passed, %d failed\n", tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}
