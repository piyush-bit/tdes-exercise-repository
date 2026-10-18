#include "consecutive_ones.h"
#include <stddef.h>

int accepts_three_consecutive_ones(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int state = 0; // States: 0 (start), 1 ("1"), 2 ("11"), 3 ("111" - accepting)

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];
        if (ch == '1') {
            if (state < 3) {
                state++;
            }
        } else if (ch == '0') {
            if (state < 3) {
                state = 0;
            }
        } else {
            // Invalid character in binary string
            return 0;
        }
    }

    return (state == 3) ? 1 : 0;
}
