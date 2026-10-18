#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "twos_complement.h"

static void assert_twos_comp(const char *input, const char *expected) {
    char output[512];
    compute_twos_complement(input, output);
    if (strcmp(output, expected) != 0) {
        printf("ADVANCED TEST FAILED: input=\"%s\", expected=\"%s\", got=\"%s\"\n", input, expected, output);
        assert(strcmp(output, expected) == 0);
    }
}

int main(void) {
    printf("Running private advanced tests...\n");
    // Edge cases: empty, single bit
    assert_twos_comp("", "");
    assert_twos_comp("0", "0");
    assert_twos_comp("1", "1");

    // Medium length patterns
    assert_twos_comp("10101010", "01010110");
    assert_twos_comp("01010101", "10101011");
    assert_twos_comp("00000001", "11111111");
    assert_twos_comp("10000000", "10000000");

    // Long binary string
    assert_twos_comp("1100110011001100", "0011001100110100");
    assert_twos_comp("0000000000000000", "0000000000000000");
    assert_twos_comp("1111111111111111", "0000000000000001");

    printf("All private advanced tests passed!\n");
    return 0;
}
