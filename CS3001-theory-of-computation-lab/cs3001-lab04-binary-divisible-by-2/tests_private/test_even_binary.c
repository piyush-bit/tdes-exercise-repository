#include <stdio.h>
#include <stdlib.h>
#include "divisible_by_2.h"

int main(void) {
    printf("Running Private Test Suite: Even Binary Strings...\n");
    const char *even_cases[] = {
        "0",
        "10",
        "100",
        "1010",
        "1100",
        "11110",
        "100000",
        "0010"
    };
    int num_cases = (int)(sizeof(even_cases) / sizeof(even_cases[0]));
    int passed = 0;

    for (int i = 0; i < num_cases; i++) {
        int res = is_binary_divisible_by_2(even_cases[i]);
        if (res == 1) {
            printf("  [PASS] input: \"%s\" -> %d\n", even_cases[i], res);
            passed++;
        } else {
            printf("  [FAIL] input: \"%s\" (expected 1, got %d)\n", even_cases[i], res);
        }
    }

    printf("Even Binary Tests Summary: %d/%d passed.\n", passed, num_cases);
    return (passed == num_cases) ? 0 : 1;
}
