#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infix_postfix.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void check_conversion(const char *infix, const char *expected_postfix) {
    char postfix[512];
    int status = infix_to_postfix(infix, postfix);
    if (status == 0 && strcmp(postfix, expected_postfix) == 0) {
        tests_passed++;
    } else {
        printf(" [FAIL] Conversion: \"%s\"\n", infix);
        printf("        Expected: \"%s\"\n", expected_postfix);
        printf("        Got:      \"%s\" (status %d)\n", status == 0 ? postfix : "ERROR", status);
        tests_failed++;
    }
}

static void check_conversion_error(const char *infix) {
    char postfix[512];
    int status = infix_to_postfix(infix, postfix);
    if (status != 0) {
        tests_passed++;
    } else {
        printf(" [FAIL] Expected error for conversion: \"%s\", but got status %d (\"%s\")\n", infix, status, postfix);
        tests_failed++;
    }
}

int main(void) {
    printf("=== Private Test Suite: Infix to Postfix Conversion ===\n");

    // Simple expressions
    check_conversion("A + B", "A B +");
    check_conversion("A - B + C", "A B - C +");
    check_conversion("A * B / C", "A B * C /");

    // Operator precedence
    check_conversion("A + B * C", "A B C * +");
    check_conversion("A * B + C", "A B * C +");
    check_conversion("A + B * C - D", "A B C * + D -");

    // Right-associative exponentiation
    check_conversion("A ^ B ^ C", "A B C ^ ^");
    check_conversion("2 ^ 3 ^ 2", "2 3 2 ^ ^");

    // Parentheses
    check_conversion("(A + B) * C", "A B + C *");
    check_conversion("(A + B) * (C - D)", "A B + C D - *");
    check_conversion("((A + B) * C) / D", "A B + C * D /");

    // Multi-digit numbers & identifiers
    check_conversion("10 + 200 * 3", "10 200 3 * +");
    check_conversion("var1 + var2 * var3", "var1 var2 var3 * +");

    // Complex combined expression
    check_conversion("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3", "3 4 2 * 1 5 - 2 3 ^ ^ / +");

    // Error handling (unmatched parentheses)
    check_conversion_error("(A + B");
    check_conversion_error("A + B)");
    check_conversion_error("((A + B) * C");
    check_conversion_error("A + (B * C))");

    printf("Conversion Private Tests: %d passed, %d failed\n", tests_passed, tests_failed);
    return (tests_failed == 0) ? 0 : 1;
}
