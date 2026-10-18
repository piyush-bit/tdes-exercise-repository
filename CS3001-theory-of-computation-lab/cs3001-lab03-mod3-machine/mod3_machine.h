#ifndef MOD3_MACHINE_H
#define MOD3_MACHINE_H

/**
 * Computes the remainder of a binary string value modulo 3 using a finite automaton.
 *
 * @param binary_str Null-terminated string containing binary digits ('0' and '1').
 * @return The integer remainder (0, 1, or 2), or -1 on invalid input / NULL / empty string.
 */
int compute_mod3(const char *binary_str);

#endif /* MOD3_MACHINE_H */
