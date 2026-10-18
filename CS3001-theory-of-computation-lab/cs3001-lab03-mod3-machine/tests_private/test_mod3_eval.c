#include <stdio.h>
#include <assert.h>
#include "mod3_machine.h"

int main(void) {
    printf("Running private evaluation tests...\n");

    // Test zero-padded inputs
    assert(compute_mod3("000") == 0);
    assert(compute_mod3("00101") == 2);
    assert(compute_mod3("000110") == 0);

    // Test numbers 0 through 15 in binary
    const char *binaries[] = {
        "0", "1", "10", "11", "100", "101", "110", "111",
        "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };
    int expected[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    for (int i = 0; i < 16; i++) {
        int res = compute_mod3(binaries[i]);
        assert(res == expected[i]);
    }

    // Test invalid characters and formatted strings
    assert(compute_mod3("10a1") == -1);
    assert(compute_mod3(" 101") == -1);
    assert(compute_mod3("101 ") == -1);
    assert(compute_mod3("abc") == -1);
    assert(compute_mod3("123") == -1);

    printf("Private evaluation tests passed!\n");
    return 0;
}
