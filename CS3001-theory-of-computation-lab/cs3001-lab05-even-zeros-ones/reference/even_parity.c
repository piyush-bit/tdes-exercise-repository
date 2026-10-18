#include "even_parity.h"
#include <stddef.h>

int has_even_zeros_and_ones(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int zeros = 0;
    int ones = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            zeros++;
        } else if (s[i] == '1') {
            ones++;
        } else {
            return 0;
        }
    }

    return (zeros % 2 == 0) && (ones % 2 == 0);
}
