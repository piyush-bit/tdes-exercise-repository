#ifndef TURING_ANBNCN_H
#define TURING_ANBNCN_H

/**
 * Checks if input string s belongs to language L = { a^n b^n c^n | n >= 1 }.
 * Returns 1 if s is valid (accepted by Turing Machine), 0 otherwise (rejected).
 */
int is_valid_anbncn(const char *s);

#endif // TURING_ANBNCN_H
