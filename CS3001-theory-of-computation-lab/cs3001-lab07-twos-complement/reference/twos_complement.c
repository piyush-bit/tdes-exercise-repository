#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "twos_complement.h"

void compute_twos_complement(const char *binary_in, char *binary_out) {
    if (!binary_in || !binary_out) {
        return;
    }

    size_t len = strlen(binary_in);
    binary_out[len] = '\0';

    if (len == 0) {
        return;
    }

    bool seen_first_one = false;
    for (int i = (int)len - 1; i >= 0; i--) {
        if (!seen_first_one) {
            binary_out[i] = binary_in[i];
            if (binary_in[i] == '1') {
                seen_first_one = true;
            }
        } else {
            if (binary_in[i] == '1') {
                binary_out[i] = '0';
            } else if (binary_in[i] == '0') {
                binary_out[i] = '1';
            } else {
                binary_out[i] = binary_in[i];
            }
        }
    }
}
