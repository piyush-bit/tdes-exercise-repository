#include <stdio.h>
#include <string.h>
#include "binary_incrementer.h"

void increment_binary(const char *binary_in, char *binary_out) {
    (void)binary_in;
    // TODO: Implement binary incrementer logic
    // Read binary_in representing a binary number, increment it by 1,
    // and write the result into binary_out as a null-terminated string.
    if (binary_out) {
        binary_out[0] = '\0';
    }
}
