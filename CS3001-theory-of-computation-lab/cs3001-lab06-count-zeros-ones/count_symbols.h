#ifndef COUNT_SYMBOLS_H
#define COUNT_SYMBOLS_H

/**
 * Counts occurrences of '0' and '1' in a binary string s.
 *
 * @param s        Pointer to null-terminated input string
 * @param count_0  Pointer to integer where count of '0's will be stored
 * @param count_1  Pointer to integer where count of '1's will be stored
 */
void count_zeros_and_ones(const char *s, int *count_0, int *count_1);

#endif // COUNT_SYMBOLS_H
