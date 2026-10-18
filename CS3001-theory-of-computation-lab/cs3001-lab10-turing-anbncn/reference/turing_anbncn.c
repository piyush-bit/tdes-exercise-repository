#include "turing_anbncn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid_anbncn(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strlen(s);
    if (len == 0) {
        return 0;
    }

    // Step 1: Check structural order a+ b+ c+
    size_t i = 0;
    size_t count_a = 0;
    while (i < len && s[i] == 'a') {
        count_a++;
        i++;
    }
    if (count_a == 0) {
        return 0;
    }

    size_t count_b = 0;
    while (i < len && s[i] == 'b') {
        count_b++;
        i++;
    }
    if (count_b == 0) {
        return 0;
    }

    size_t count_c = 0;
    while (i < len && s[i] == 'c') {
        count_c++;
        i++;
    }
    if (count_c == 0) {
        return 0;
    }

    if (i != len) {
        return 0;
    }

    // Step 2: Turing Machine Tape Simulation
    char *tape = (char *)malloc(len + 1);
    if (tape == NULL) {
        return 0;
    }
    strcpy(tape, s);

    while (1) {
        // Scan right to find first unmarked 'a'
        size_t head = 0;
        while (head < len && tape[head] != 'a') {
            head++;
        }

        // If no unmarked 'a' left
        if (head == len) {
            // Verify no unmarked 'b' or 'c' remain on tape
            int valid = 1;
            for (size_t j = 0; j < len; j++) {
                if (tape[j] == 'a' || tape[j] == 'b' || tape[j] == 'c') {
                    valid = 0;
                    break;
                }
            }
            free(tape);
            return valid;
        }

        // Mark 'a' -> 'X'
        tape[head] = 'X';

        // Scan right to find first unmarked 'b'
        while (head < len && tape[head] != 'b') {
            head++;
        }
        if (head >= len) {
            free(tape);
            return 0;
        }
        tape[head] = 'Y';

        // Scan right to find first unmarked 'c'
        while (head < len && tape[head] != 'c') {
            head++;
        }
        if (head >= len) {
            free(tape);
            return 0;
        }
        tape[head] = 'Z';
    }
}
