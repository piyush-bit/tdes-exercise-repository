#ifndef INFIX_POSTFIX_H
#define INFIX_POSTFIX_H

#include <stddef.h>

/**
 * Converts an infix expression into a space-separated postfix expression.
 *
 * Supported operators: +, -, *, /, %, ^ and parentheses ( ).
 * Precedence and Associativity:
 *   - ^ : Precedence 3, Right-to-Left associative
 *   - *, /, % : Precedence 2, Left-to-Right associative
 *   - +, - : Precedence 1, Left-to-Right associative
 *
 * @param infix   Null-terminated string containing the infix expression.
 * @param postfix Output buffer where the space-separated postfix expression will be written.
 * @return 0 on success, or -1 if the expression is invalid (e.g. mismatched parentheses, unknown character).
 */
int infix_to_postfix(const char *infix, char *postfix);

/**
 * Evaluates a space-separated postfix expression containing integer operands and operators (+, -, *, /, %, ^).
 *
 * @param postfix Null-terminated string containing space-separated postfix expression.
 * @param result  Pointer to an integer where the evaluated result will be stored.
 * @return 0 on success, or -1 on error (e.g. division by zero, invalid expression, stack underflow/overflow).
 */
int evaluate_postfix(const char *postfix, int *result);

#endif // INFIX_POSTFIX_H
