#include <stdio.h>
#include <stdlib.h>
#include "divisible_by_2.h"

int main(void) {
    printf("Running Private Test Suite: Odd Binary Strings...\n");
    const char *odd_cases[] = {
        "1",
        "11",
        "101",
        "1011",
        "1111",
        "100001",
        "0011"
    };
    int num_cases = (int)(sizeof(odd_cases) / sizeof(odd_cases[0]));
    int passed = 0;

    for (int i = 0; i < num_cases; i++) {
        int res = is_binary_divisible_by_2(odd_cases[i]);
        if (res == 0) {
            printf("  [PASS] input: \"%s\" -> %d\n", odd_cases[i], res);
            passed++;
        } else {
            printf("  [FAIL] input: \"%s\" (expected 0, got %d)\n", odd_cases[i], res);
        }
    }

    printf("Odd Binary Tests Summary: %d/%d passed.\n", passed, num_cases);
    return (passed == num_cases) ? 0 : 1;
}
