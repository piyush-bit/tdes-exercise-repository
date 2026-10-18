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
        printf("PASS [Basic]: increment_binary(\"%s\") -> \"%s\"\n", input, output);
        pass_count++;
    } else {
        printf("FAIL [Basic]: increment_binary(\"%s\") -> Expected \"%s\", got \"%s\"\n", input, expected, output);
    }
}

int main(void) {
    printf("=== Private Tests: Basic Increment ===\n");
    assert_increment("0", "1");
    assert_increment("10", "11");
    assert_increment("1001", "1010");
    assert_increment("1010", "1011");
    assert_increment("000", "001");
    assert_increment("011", "100");
    assert_increment("101010", "101011");

    printf("Basic Tests Summary: %d/%d passed.\n", pass_count, test_count);
    return (pass_count == test_count) ? 0 : 1;
}
