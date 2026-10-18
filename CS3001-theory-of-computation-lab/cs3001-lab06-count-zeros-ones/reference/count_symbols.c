#include "count_symbols.h"
#include <stddef.h>

void count_zeros_and_ones(const char *s, int *count_0, int *count_1) {
    int c0 = 0;
    int c1 = 0;

    if (s != NULL) {
        for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == '0') {
                c0++;
            } else if (s[i] == '1') {
                c1++;
            }
        }
    }

    if (count_0 != NULL) {
        *count_0 = c0;
    }
    if (count_1 != NULL) {
        *count_1 = c1;
    }
}
