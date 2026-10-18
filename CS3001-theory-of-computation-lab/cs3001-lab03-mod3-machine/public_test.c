#include <stdio.h>
#include <assert.h>
#include "mod3_machine.h"

int main(void) {
    printf("Running public tests for Modulo 3 Machine...\n");

    // Required assertions from lab prompt
    assert(compute_mod3("101") == 2);
    assert(compute_mod3("110") == 0);
    assert(compute_mod3("100") == 1);

    // Basic single/double bit tests
    assert(compute_mod3("0") == 0);
    assert(compute_mod3("1") == 1);
    assert(compute_mod3("10") == 2);
    assert(compute_mod3("11") == 0);

    // Edge and invalid cases
    assert(compute_mod3(NULL) == -1);
    assert(compute_mod3("") == -1);
    assert(compute_mod3("102") == -1);

    printf("All public tests passed successfully!\n");
    return 0;
}
