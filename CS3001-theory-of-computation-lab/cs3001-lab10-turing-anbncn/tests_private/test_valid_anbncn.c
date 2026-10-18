#include "turing_anbncn.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running private tests for valid a^n b^n c^n strings...\n");

    assert(is_valid_anbncn("abc") == 1);
    assert(is_valid_anbncn("aabbcc") == 1);
    assert(is_valid_anbncn("aaabbbccc") == 1);
    assert(is_valid_anbncn("aaaabbbbcccc") == 1);
    assert(is_valid_anbncn("aaaaabbbbbccccc") == 1);

    printf("Private valid tests passed!\n");
    return 0;
}
