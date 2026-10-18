#include <stdio.h>
#include <string.h>
#include "binary_incrementer.h"

void increment_binary(const char *binary_in, char *binary_out) {
    if (!binary_in || !binary_out) return;

    size_t len = strlen(binary_in);
    if (len == 0) {
        binary_out[0] = '\0';
        return;
    }

    int all_ones = 1;
    for (size_t i = 0; i < len; i++) {
        if (binary_in[i] != '1') {
            all_ones = 0;
            break;
        }
    }

    if (all_ones) {
        binary_out[0] = '1';
        for (size_t i = 1; i <= len; i++) {
            binary_out[i] = '0';
        }
        binary_out[len + 1] = '\0';
    } else {
        binary_out[len] = '\0';
        int carry = 1;
        for (int i = (int)len - 1; i >= 0; i--) {
            if (carry) {
                if (binary_in[i] == '1') {
                    binary_out[i] = '0';
                    carry = 1;
                } else {
                    binary_out[i] = '1';
                    carry = 0;
                }
            } else {
                binary_out[i] = binary_in[i];
            }
        }
    }
}
