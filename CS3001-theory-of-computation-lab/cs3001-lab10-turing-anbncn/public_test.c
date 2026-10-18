#include "turing_anbncn.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running public tests for Turing Machine a^n b^n c^n...\n");

    // Valid inputs (n >= 1)
    assert(is_valid_anbncn("abc") == 1);
    assert(is_valid_anbncn("aabbcc") == 1);
    assert(is_valid_anbncn("aaabbbccc") == 1);

    // Invalid inputs
    assert(is_valid_anbncn("aabbc") == 0);
    assert(is_valid_anbncn("aabcc") == 0);
    assert(is_valid_anbncn("ab") == 0);
    assert(is_valid_anbncn("") == 0);

    printf("All public tests passed successfully!\n");
    return 0;
}
