#include <stdio.h>
#include <assert.h>
#include "pda_wcwr.h"

int main(void) {
    printf("Running private tests: valid W c W^R...\n");

    // Basic valid patterns
    assert(is_valid_wcwr("aCa") == 1);
    assert(is_valid_wcwr("bCb") == 1);
    assert(is_valid_wcwr("aca") == 1);
    assert(is_valid_wcwr("bcb") == 1);

    // Multi-character W and W^R
    assert(is_valid_wcwr("abCba") == 1);
    assert(is_valid_wcwr("baCab") == 1);
    assert(is_valid_wcwr("abbaCabba") == 1);
    assert(is_valid_wcwr("aabbaaCaabbaa") == 1);

    // Empty W (just marker)
    assert(is_valid_wcwr("C") == 1);
    assert(is_valid_wcwr("c") == 1);

    printf("Valid W c W^R tests passed successfully!\n");
    return 0;
}
