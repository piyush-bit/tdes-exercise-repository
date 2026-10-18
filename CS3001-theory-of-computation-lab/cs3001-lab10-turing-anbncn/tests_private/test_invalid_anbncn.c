#include "turing_anbncn.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running private tests for invalid a^n b^n c^n strings...\n");

    // Empty and NULL
    assert(is_valid_anbncn("") == 0);
    assert(is_valid_anbncn(NULL) == 0);

    // Wrong order / incomplete patterns
    assert(is_valid_anbncn("a") == 0);
    assert(is_valid_anbncn("b") == 0);
    assert(is_valid_anbncn("c") == 0);
    assert(is_valid_anbncn("ab") == 0);
    assert(is_valid_anbncn("bc") == 0);
    assert(is_valid_anbncn("ac") == 0);
    assert(is_valid_anbncn("ba") == 0);
    assert(is_valid_anbncn("cba") == 0);
    assert(is_valid_anbncn("abcabc") == 0);

    // Mismatched counts
    assert(is_valid_anbncn("aabbc") == 0);
    assert(is_valid_anbncn("aabcc") == 0);
    assert(is_valid_anbncn("abbcc") == 0);
    assert(is_valid_anbncn("aabbccc") == 0);
    assert(is_valid_anbncn("aaabbcc") == 0);

    // Invalid characters
    assert(is_valid_anbncn("abcX") == 0);
    assert(is_valid_anbncn("123") == 0);

    printf("Private invalid tests passed!\n");
    return 0;
}
