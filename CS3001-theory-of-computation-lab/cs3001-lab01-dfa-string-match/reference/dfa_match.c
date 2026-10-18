#include "dfa_match.h"
#include <stddef.h>

int starts_with_a(const char *s) {
    if (s == NULL) {
        return 0;
    }

    // State 0: Initial state (before reading any char)
    // State 1: Accept state (first character was 'a')
    // State 2: Dead/Reject state (first character was not 'a')
    int state = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        switch (state) {
            case 0:
                if (s[i] == 'a') {
                    state = 1;
                } else {
                    state = 2;
                }
                break;
            case 1:
                // Stay in accept state
                break;
            case 2:
                // Stay in dead state
                break;
        }
    }

    return state == 1;
}

int ends_with_b(const char *s) {
    if (s == NULL) {
        return 0;
    }

    // State 0: Non-'b' end state / start state
    // State 1: Accept state (last character was 'b')
    int state = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            state = 1;
        } else {
            state = 0;
        }
    }

    return state == 1;
}

int starts_a_ends_b(const char *s) {
    if (s == NULL) {
        return 0;
    }

    // State 0: Initial state
    // State 1: Dead state (did not start with 'a')
    // State 2: Starts with 'a', last character is NOT 'b'
    // State 3: Accept state (starts with 'a' AND last character is 'b')
    int state = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        switch (state) {
            case 0:
                if (s[i] == 'a') {
                    state = 2;
                } else {
                    state = 1;
                }
                break;
            case 1:
                // Stay in dead state
                break;
            case 2:
            case 3:
                if (s[i] == 'b') {
                    state = 3;
                } else {
                    state = 2;
                }
                break;
        }
    }

    return state == 3;
}
