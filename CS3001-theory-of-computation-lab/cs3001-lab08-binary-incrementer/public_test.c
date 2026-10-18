#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_incrementer.h"

static int test_count = 0;
static int pass_count = 0;

static void assert_increment(const char *input, const char *expected) {
    test_count++;
    char output[256];
    memset(output, 0, sizeof(output));
    increment_binary(input, output);
    if (strcmp(output, expected) == 0) {
        printf("PASS: increment_binary(\"%s\") -> \"%s\"\n", input, output);
        pass_count++;
    } else {
        printf("FAIL: increment_binary(\"%s\") -> Expected \"%s\", got \"%s\"\n", input, expected, output);
    }
}

int main(void) {
    printf("=== Public Tests: Binary Incrementer ===\n");
    assert_increment("0", "1");
    assert_increment("1011", "1100");
    assert_increment("111", "1000");

    printf("\nSummary: %d/%d tests passed.\n", pass_count, test_count);
    return (pass_count == test_count) ? 0 : 1;
}
