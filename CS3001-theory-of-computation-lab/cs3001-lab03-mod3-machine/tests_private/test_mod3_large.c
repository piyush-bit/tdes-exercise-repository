#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mod3_machine.h"

int main(void) {
    printf("Running private large binary string tests...\n");

    // 100 '1's in binary:
    // Value = 2^100 - 1. 2 = -1 mod 3 => (-1)^100 - 1 = 1 - 1 = 0 mod 3.
    char str100[101];
    memset(str100, '1', 100);
    str100[100] = '\0';
    assert(compute_mod3(str100) == 0);

    // 101 '1's in binary:
    // Value = 2^101 - 1 => (-1)^101 - 1 = -1 - 1 = -2 = 1 mod 3.
    char str101[102];
    memset(str101, '1', 101);
    str101[101] = '\0';
    assert(compute_mod3(str101) == 1);

    // '1' followed by 100 '0's (2^100 mod 3):
    // 2^100 mod 3 => (-1)^100 = 1 mod 3.
    char pow2_100[102];
    pow2_100[0] = '1';
    memset(pow2_100 + 1, '0', 100);
    pow2_100[101] = '\0';
    assert(compute_mod3(pow2_100) == 1);

    // '1' followed by 101 '0's (2^101 mod 3):
    // 2^101 mod 3 => (-1)^101 = -1 = 2 mod 3.
    char pow2_101[103];
    pow2_101[0] = '1';
    memset(pow2_101 + 1, '0', 101);
    pow2_101[102] = '\0';
    assert(compute_mod3(pow2_101) == 2);

    // Alternating "101010..." of length 100
    char alt[101];
    for (int i = 0; i < 100; i++) {
        alt[i] = (i % 2 == 0) ? '1' : '0';
    }
    alt[100] = '\0';
    assert(compute_mod3(alt) == 1);

    printf("Private large string tests passed!\n");
    return 0;
}
