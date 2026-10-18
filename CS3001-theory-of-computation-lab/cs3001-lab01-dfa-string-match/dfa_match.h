#ifndef DFA_MATCH_H
#define DFA_MATCH_H

/**
 * Checks if the string starts with the character 'a'.
 * Returns 1 if accepted, 0 if rejected (including NULL or empty string).
 */
int starts_with_a(const char *s);

/**
 * Checks if the string ends with the character 'b'.
 * Returns 1 if accepted, 0 if rejected (including NULL or empty string).
 */
int ends_with_b(const char *s);

/**
 * Checks if the string starts with 'a' AND ends with 'b'.
 * Returns 1 if accepted, 0 if rejected (including NULL or empty string).
 */
int starts_a_ends_b(const char *s);

#endif /* DFA_MATCH_H */
