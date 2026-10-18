#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "even_parity.h"

int main(void) {
    printf("Running private tests for even parity inputs...\n");

    assert(has_even_zeros_and_ones("") == 1);
    assert(has_even_zeros_and_ones("00") == 1);
    assert(has_even_zeros_and_ones("11") == 1);
    assert(has_even_zeros_and_ones("0011") == 1);
    assert(has_even_zeros_and_ones("1100") == 1);
    assert(has_even_zeros_and_ones("0101") == 1);
    assert(has_even_zeros_and_ones("1010") == 1);
    assert(has_even_zeros_and_ones("0000") == 1);
    assert(has_even_zeros_and_ones("1111") == 1);
    assert(has_even_zeros_and_ones("00001111") == 1);
    assert(has_even_zeros_and_ones("01010101") == 1);
    assert(has_even_zeros_and_ones("10011001") == 1);
    assert(has_even_zeros_and_ones("000000") == 1);
    assert(has_even_zeros_and_ones("11111111") == 1);
    assert(has_even_zeros_and_ones("001100110011") == 1);

    printf("All even parity tests passed!\n");
    return 0;
}
