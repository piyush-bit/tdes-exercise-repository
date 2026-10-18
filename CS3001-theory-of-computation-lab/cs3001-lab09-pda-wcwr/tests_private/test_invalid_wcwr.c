#include <stdio.h>
#include <assert.h>
#include "pda_wcwr.h"

int main(void) {
    printf("Running private tests: invalid W c W^R...\n");

    // W C W (repetition instead of reversal)
    assert(is_valid_wcwr("abCab") == 0);
    assert(is_valid_wcwr("ababCabab") == 0);

    // Mismatched lengths
    assert(is_valid_wcwr("aCab") == 0);
    assert(is_valid_wcwr("abc") == 0);
    assert(is_valid_wcwr("cab") == 0);

    // Missing center marker
    assert(is_valid_wcwr("ab") == 0);
    assert(is_valid_wcwr("abba") == 0);
    assert(is_valid_wcwr("") == 0);

    // Multiple center markers
    assert(is_valid_wcwr("abCbaCba") == 0);
    assert(is_valid_wcwr("cCc") == 0);

    // Invalid alphabet characters
    assert(is_valid_wcwr("axCxa") == 0);
    assert(is_valid_wcwr("ab1C1ba") == 0);

    // NULL pointer
    assert(is_valid_wcwr(NULL) == 0);

    printf("Invalid W c W^R tests passed successfully!\n");
    return 0;
}
