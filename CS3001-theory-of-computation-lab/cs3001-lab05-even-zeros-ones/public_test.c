#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "even_parity.h"

int main(void) {
    printf("Running public tests...\n");

    // "0011" -> 2 zeros, 2 ones -> 1
    assert(has_even_zeros_and_ones("0011") == 1);

    // "011" -> 1 zero, 2 ones -> 0
    assert(has_even_zeros_and_ones("011") == 0);

    // "" -> 0 zeros, 0 ones -> 1
    assert(has_even_zeros_and_ones("") == 1);

    // "00" -> 2 zeros, 0 ones -> 1
    assert(has_even_zeros_and_ones("00") == 1);

    // "11" -> 0 zeros, 2 ones -> 1
    assert(has_even_zeros_and_ones("11") == 1);

    // "0" -> 1 zero, 0 ones -> 0
    assert(has_even_zeros_and_ones("0") == 0);

    // "1" -> 0 zeros, 1 one -> 0
    assert(has_even_zeros_and_ones("1") == 0);

    printf("All public tests passed successfully!\n");
    return 0;
}
