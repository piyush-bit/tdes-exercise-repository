#include <stdio.h>
#include <assert.h>
#include "dfa_match.h"

int main(void) {
    printf("[PRIVATE TEST] Testing starts_with_a and ends_with_b...\n");

    // Comprehensive tests for starts_with_a
    assert(starts_with_a("a") == 1);
    assert(starts_with_a("a123") == 1);
    assert(starts_with_a("aaaaa") == 1);
    assert(starts_with_a("a_b_c") == 1);
    assert(starts_with_a("alphabet") == 1);
    
    assert(starts_with_a("b") == 0);
    assert(starts_with_a("ba") == 0);
    assert(starts_with_a("A") == 0); // case sensitivity
    assert(starts_with_a(" apple") == 0); // leading space
    assert(starts_with_a("123a") == 0);
    assert(starts_with_a("") == 0);
    assert(starts_with_a(NULL) == 0);

    // Comprehensive tests for ends_with_b
    assert(ends_with_b("b") == 1);
    assert(ends_with_b("ab") == 1);
    assert(ends_with_b("bbbbb") == 1);
    assert(ends_with_b("123b") == 1);
    assert(ends_with_b("suburb") == 1);

    assert(ends_with_b("a") == 0);
    assert(ends_with_b("ba") == 0);
    assert(ends_with_b("B") == 0); // case sensitivity
    assert(ends_with_b("b ") == 0); // trailing space
    assert(ends_with_b("b123") == 0);
    assert(ends_with_b("") == 0);
    assert(ends_with_b(NULL) == 0);

    printf("[PRIVATE TEST] starts_with_a and ends_with_b passed successfully!\n");
    return 0;
}
