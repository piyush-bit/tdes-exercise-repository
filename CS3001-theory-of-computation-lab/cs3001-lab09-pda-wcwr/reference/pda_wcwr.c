#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "pda_wcwr.h"

int is_valid_wcwr(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strlen(s);

    // Find the center marker ('c' or 'C')
    int center_idx = -1;
    for (size_t i = 0; i < len; i++) {
        if (s[i] == 'c' || s[i] == 'C') {
            if (center_idx != -1) {
                // Multiple center markers found
                return 0;
            }
            center_idx = (int)i;
        }
    }

    if (center_idx == -1) {
        // No center marker found
        return 0;
    }

    size_t w_len = (size_t)center_idx;
    size_t wr_len = len - 1 - (size_t)center_idx;

    if (w_len != wr_len) {
        return 0;
    }

    char *stack = (char *)malloc(w_len > 0 ? w_len : 1);
    if (!stack) {
        return 0;
    }

    size_t top = 0;

    // Phase 1: Push W onto stack
    for (size_t i = 0; i < w_len; i++) {
        char ch = s[i];
        if (ch != 'a' && ch != 'b' && ch != 'A' && ch != 'B') {
            free(stack);
            return 0;
        }
        stack[top++] = ch;
    }

    // Phase 2: Pop and match W^R
    for (size_t i = (size_t)center_idx + 1; i < len; i++) {
        char ch = s[i];
        if (top == 0) {
            free(stack);
            return 0;
        }
        char expected = stack[--top];
        if (ch != expected) {
            free(stack);
            return 0;
        }
    }

    int result = (top == 0) ? 1 : 0;
    free(stack);
    return result;
}
