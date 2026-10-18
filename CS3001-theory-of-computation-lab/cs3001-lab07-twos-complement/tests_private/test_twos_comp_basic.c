#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "twos_complement.h"

static void assert_twos_comp(const char *input, const char *expected) {
    char output[256];
    compute_twos_complement(input, output);
    if (strcmp(output, expected) != 0) {
        printf("BASIC TEST FAILED: input=\"%s\", expected=\"%s\", got=\"%s\"\n", input, expected, output);
        assert(strcmp(output, expected) == 0);
    }
}

int main(void) {
    printf("Running private basic tests...\n");
    assert_twos_comp("0000", "0000");
    assert_twos_comp("0001", "1111");
    assert_twos_comp("0100", "1100");
    assert_twos_comp("1000", "1000");
    assert_twos_comp("1111", "0001");
    assert_twos_comp("0101", "1011");
    assert_twos_comp("1001", "0111");
    printf("All private basic tests passed!\n");
    return 0;
}
