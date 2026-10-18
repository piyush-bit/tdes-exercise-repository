#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "twos_complement.h"

static void test_case(const char *input, const char *expected) {
    char output[256];
    compute_twos_complement(input, output);
    if (strcmp(output, expected) != 0) {
        printf("FAILED: Input '%s', Expected '%s', Got '%s'\n", input, expected, output);
        assert(strcmp(output, expected) == 0);
    } else {
        printf("PASSED: Input '%s' -> '%s'\n", input, output);
    }
}

int main(void) {
    printf("Running public tests for 2's Complement Transducer...\n");
    test_case("1010", "0110");
    test_case("1100", "0100");
    test_case("0000", "0000");
    printf("All public tests passed successfully!\n");
    return 0;
}
