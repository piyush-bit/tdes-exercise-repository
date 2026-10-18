#include <stdio.h>
#include <string.h>
#include "twos_complement.h"

void compute_twos_complement(const char *binary_in, char *binary_out) {
    if (!binary_in || !binary_out) {
        return;
    }

    // TODO: Implement 2's complement calculation for binary_in.
    // Write the resulting binary string into binary_out (null-terminated).
    // Hint: Process from right to left (LSB to MSB). Keep trailing zeros and the first '1' unchanged,
    // then invert all remaining bits to the left.

    binary_out[0] = '\0';
}
