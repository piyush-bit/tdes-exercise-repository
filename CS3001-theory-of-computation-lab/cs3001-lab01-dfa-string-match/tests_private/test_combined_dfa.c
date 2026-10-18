#include <stdio.h>
#include <assert.h>
#include "dfa_match.h"

int main(void) {
    printf("[PRIVATE TEST] Testing starts_a_ends_b...\n");

    // Accept cases: starts with 'a' AND ends with 'b'
    assert(starts_a_ends_b("ab") == 1);
    assert(starts_a_ends_b("abb") == 1);
    assert(starts_a_ends_b("aab") == 1);
    assert(starts_a_ends_b("axxxb") == 1);
    assert(starts_a_ends_b("a b") == 1);
    assert(starts_a_ends_b("aaaaab") == 1);
    assert(starts_a_ends_b("abbbbbbb") == 1);
    assert(starts_a_ends_b("a123b") == 1);
    assert(starts_a_ends_b("a_b_b") == 1);

    // Reject cases
    assert(starts_a_ends_b("a") == 0);
    assert(starts_a_ends_b("b") == 0);
    assert(starts_a_ends_b("ba") == 0);
    assert(starts_a_ends_b("bab") == 0);
    assert(starts_a_ends_b("aba") == 0);
    assert(starts_a_ends_b("abc") == 0);
    assert(starts_a_ends_b("xab") == 0);
    assert(starts_a_ends_b("Ab") == 0);
    assert(starts_a_ends_b("aB") == 0);
    assert(starts_a_ends_b("AB") == 0);
    assert(starts_a_ends_b("ab ") == 0);
    assert(starts_a_ends_b(" ab") == 0);
    assert(starts_a_ends_b("") == 0);
    assert(starts_a_ends_b(NULL) == 0);

    printf("[PRIVATE TEST] starts_a_ends_b passed successfully!\n");
    return 0;
}
