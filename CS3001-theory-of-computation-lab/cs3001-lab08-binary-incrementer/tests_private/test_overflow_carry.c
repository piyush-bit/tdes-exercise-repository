#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../binary_incrementer.h"

static int test_count = 0;
static int pass_count = 0;

static void assert_increment(const char *input, const char *expected) {
    test_count++;
    char output[256];
    memset(output, 0, sizeof(output));
    increment_binary(input, output);
    if (strcmp(output, expected) == 0) {
        printf("PASS [Overflow]: increment_binary(\"%s\") -> \"%s\"\n", input, output);
        pass_count++;
    } else {
        printf("FAIL [Overflow]: increment_binary(\"%s\") -> Expected \"%s\", got \"%s\"\n", input, expected, output);
    }
}

int main(void) {
    printf("=== Private Tests: Overflow & Carry ===\n");
    assert_increment("1", "10");
    assert_increment("11", "100");
    assert_increment("111", "1000");
    assert_increment("1111", "10000");
    assert_increment("11111111", "100000000");

    printf("Overflow Tests Summary: %d/%d passed.\n", pass_count, test_count);
    return (pass_count == test_count) ? 0 : 1;
}
