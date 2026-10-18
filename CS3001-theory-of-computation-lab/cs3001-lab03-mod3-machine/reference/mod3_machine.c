#include "mod3_machine.h"
#include <stddef.h>

int compute_mod3(const char *binary_str) {
    if (binary_str == NULL || *binary_str == '\0') {
        return -1;
    }

    int state = 0;
    for (int i = 0; binary_str[i] != '\0'; i++) {
        char ch = binary_str[i];
        if (ch == '0') {
            state = (state * 2 + 0) % 3;
        } else if (ch == '1') {
            state = (state * 2 + 1) % 3;
        } else {
            return -1;
        }
    }

    return state;
}
