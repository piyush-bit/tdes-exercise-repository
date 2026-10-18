#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "even_parity.h"

int main(void) {
    printf("Running private tests for odd parity / invalid inputs...\n");

    assert(has_even_zeros_and_ones("0") == 0);
    assert(has_even_zeros_and_ones("1") == 0);
    assert(has_even_zeros_and_ones("01") == 0);
    assert(has_even_zeros_and_ones("10") == 0);
    assert(has_even_zeros_and_ones("000") == 0);
    assert(has_even_zeros_and_ones("111") == 0);
    assert(has_even_zeros_and_ones("011") == 0);
    assert(has_even_zeros_and_ones("001") == 0);
    assert(has_even_zeros_and_ones("00011") == 0);
    assert(has_even_zeros_and_ones("00111") == 0);
    assert(has_even_zeros_and_ones("01010") == 0);
    assert(has_even_zeros_and_ones("10101") == 0);
    assert(has_even_zeros_and_ones("0101010") == 0);
    assert(has_even_zeros_and_ones("00000") == 0);
    assert(has_even_zeros_and_ones("11111") == 0);
    assert(has_even_zeros_and_ones("abc") == 0);
    assert(has_even_zeros_and_ones("001211") == 0);
    assert(has_even_zeros_and_ones(NULL) == 0);

    printf("All odd parity tests passed!\n");
    return 0;
}
