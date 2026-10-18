#ifndef BINARY_INCREMENTER_H
#define BINARY_INCREMENTER_H

/**
 * Increments a binary string by 1.
 *
 * @param binary_in  Null-terminated string of '0' and '1' characters.
 * @param binary_out Output buffer to receive the null-terminated incremented binary string.
 */
void increment_binary(const char *binary_in, char *binary_out);

#endif // BINARY_INCREMENTER_H
