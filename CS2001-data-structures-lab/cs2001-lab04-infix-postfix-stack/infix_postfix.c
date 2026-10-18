#include "infix_postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Converts an infix expression into a space-separated postfix expression.
 * Returns 0 on success, or -1 if the expression is invalid.
 */
int infix_to_postfix(const char *infix, char *postfix) {
    (void)infix;
    if (postfix != NULL) {
        postfix[0] = '\0';
    }

    // TODO: Implement the Shunting Yard Algorithm using an operator stack.
    // 1. Traverse through the infix string token by token.
    // 2. Handle operands, operators (+, -, *, /, %, ^), and parentheses ( ).
    // 3. Obey operator precedence and right-associativity of ^.
    // 4. Format tokens into postfix separated by single spaces.
    // 5. Return 0 on successful conversion, or -1 on syntax/parenthesis error.

    return -1;
}

/*
 * Evaluates a space-separated postfix expression containing integer operands and operators.
 * Stores the final result in *result and returns 0 on success, or -1 on error.
 */
int evaluate_postfix(const char *postfix, int *result) {
    (void)postfix;
    if (result != NULL) {
        *result = 0;
    }

    // TODO: Implement Postfix Evaluation using an integer operand stack.
    // 1. Tokenize the space-separated postfix string.
    // 2. Push integer operands onto the stack.
    // 3. For operators (+, -, *, /, %, ^), pop two operands, perform the operation, and push result.
    // 4. Handle invalid cases: insufficient operands, leftover operands, division/modulo by zero.
    // 5. Store final evaluated result in *result and return 0 on success, or -1 on error.

    return -1;
}
