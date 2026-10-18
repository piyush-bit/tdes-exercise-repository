#include <stdio.h>
#include <assert.h>
#include "dfa_match.h"

int main(void) {
    printf("[PUBLIC TEST] Running basic DFA string matching tests...\n");

    // Test 1: starts_with_a
    assert(starts_with_a("apple") == 1);
    assert(starts_with_a("a") == 1);
    assert(starts_with_a("banana") == 0);
    assert(starts_with_a("") == 0);
    assert(starts_with_a(NULL) == 0);

    // Test 2: ends_with_b
    assert(ends_with_b("cab") == 1);
    assert(ends_with_b("b") == 1);
    assert(ends_with_b("caba") == 0);
    assert(ends_with_b("") == 0);
    assert(ends_with_b(NULL) == 0);

    // Test 3: starts_a_ends_b
    assert(starts_a_ends_b("ab") == 1);
    assert(starts_a_ends_b("acb") == 1);
    assert(starts_a_ends_b("a") == 0);
    assert(starts_a_ends_b("b") == 0);
    assert(starts_a_ends_b("ba") == 0);
    assert(starts_a_ends_b("") == 0);
    assert(starts_a_ends_b(NULL) == 0);

    printf("[PUBLIC TEST] All public tests passed successfully!\n");
    return 0;
}
