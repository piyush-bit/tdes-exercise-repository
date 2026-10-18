#include <stdio.h>
#include <assert.h>
#include "pda_wcwr.h"

int main(void) {
    printf("Running public tests for PDA W c W^R...\n");

    assert(is_valid_wcwr("abCba") == 1);
    assert(is_valid_wcwr("abcba") == 1);
    assert(is_valid_wcwr("aCa") == 1);
    assert(is_valid_wcwr("C") == 1);
    assert(is_valid_wcwr("c") == 1);
    assert(is_valid_wcwr("abCab") == 0);
    assert(is_valid_wcwr("aCab") == 0);
    assert(is_valid_wcwr("abc") == 0);
    assert(is_valid_wcwr(NULL) == 0);

    printf("All public tests passed successfully!\n");
    return 0;
}
