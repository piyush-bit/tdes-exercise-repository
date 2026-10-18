#include "infix_postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 1024

static int get_precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

static int is_right_associative(char op) {
    return (op == '^');
}

static int is_operator_char(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

/* Helper to append a token to the postfix output string with single space separation */
static void append_token(char *postfix, size_t *pos, const char *token) {
    size_t tok_len = strlen(token);
    if (*pos > 0) {
        postfix[(*pos)++] = ' ';
    }
    memcpy(postfix + *pos, token, tok_len);
    *pos += tok_len;
    postfix[*pos] = '\0';
}

int infix_to_postfix(const char *infix, char *postfix) {
    if (infix == NULL || postfix == NULL) {
        return -1;
    }

    char op_stack[STACK_SIZE];
    int top = -1;
    size_t pos = 0;
    postfix[0] = '\0';

    size_t len = strlen(infix);
    size_t i = 0;
    int last_was_operand = 0; // to help distinguish unary minus if needed

    while (i < len) {
        while (i < len && isspace((unsigned char)infix[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        char c = infix[i];

        // Check for operand token (numbers or identifiers)
        // Also check if '-' is a unary minus at the start of a number
        int is_unary_minus = (c == '-' && !last_was_operand && (i + 1 < len) && isdigit((unsigned char)infix[i + 1]));

        if (isalnum((unsigned char)c) || is_unary_minus) {
            char tok[256];
            size_t tok_len = 0;

            if (is_unary_minus) {
                tok[tok_len++] = infix[i++];
            }

            while (i < len && (isalnum((unsigned char)infix[i]) || infix[i] == '.')) {
                if (tok_len < sizeof(tok) - 1) {
                    tok[tok_len++] = infix[i];
                }
                i++;
            }
            tok[tok_len] = '\0';
            append_token(postfix, &pos, tok);
            last_was_operand = 1;
        } else if (c == '(') {
            if (top >= STACK_SIZE - 1) return -1;
            op_stack[++top] = '(';
            i++;
            last_was_operand = 0;
        } else if (c == ')') {
            int found_lparen = 0;
            while (top >= 0) {
                char top_op = op_stack[top--];
                if (top_op == '(') {
                    found_lparen = 1;
                    break;
                }
                char tok[2] = { top_op, '\0' };
                append_token(postfix, &pos, tok);
            }
            if (!found_lparen) {
                return -1; // Unmatched right parenthesis
            }
            i++;
            last_was_operand = 1;
        } else if (is_operator_char(c)) {
            int p1 = get_precedence(c);
            while (top >= 0 && op_stack[top] != '(') {
                char top_op = op_stack[top];
                int p2 = get_precedence(top_op);
                if (p2 > p1 || (p2 == p1 && !is_right_associative(c))) {
                    top--;
                    char tok[2] = { top_op, '\0' };
                    append_token(postfix, &pos, tok);
                } else {
                    break;
                }
            }
            if (top >= STACK_SIZE - 1) return -1;
            op_stack[++top] = c;
            i++;
            last_was_operand = 0;
        } else {
            return -1; // Invalid character
        }
    }

    // Pop remaining operators from stack
    while (top >= 0) {
        char top_op = op_stack[top--];
        if (top_op == '(' || top_op == ')') {
            return -1; // Unmatched left parenthesis
        }
        char tok[2] = { top_op, '\0' };
        append_token(postfix, &pos, tok);
    }

    return 0;
}

static long long power_int(long long base, long long exp) {
    if (exp < 0) return -1;
    long long result = 1;
    for (long long i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int evaluate_postfix(const char *postfix, int *result) {
    if (postfix == NULL || result == NULL) {
        return -1;
    }

    long long val_stack[STACK_SIZE];
    int top = -1;

    size_t len = strlen(postfix);
    size_t i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)postfix[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        // Read next space-delimited token
        char tok[256];
        size_t tok_len = 0;
        while (i < len && !isspace((unsigned char)postfix[i])) {
            if (tok_len < sizeof(tok) - 1) {
                tok[tok_len++] = postfix[i];
            }
            i++;
        }
        tok[tok_len] = '\0';

        // Check if operator
        if (tok_len == 1 && is_operator_char(tok[0])) {
            if (top < 1) {
                return -1; // Insufficient operands
            }
            long long b = val_stack[top--];
            long long a = val_stack[top--];
            long long val = 0;

            switch (tok[0]) {
                case '+':
                    val = a + b;
                    break;
                case '-':
                    val = a - b;
                    break;
                case '*':
                    val = a * b;
                    break;
                case '/':
                    if (b == 0) return -1; // Division by zero
                    val = a / b;
                    break;
                case '%':
                    if (b == 0) return -1; // Modulo by zero
                    val = a % b;
                    break;
                case '^':
                    if (b < 0) return -1; // Negative exponent
                    val = power_int(a, b);
                    break;
                default:
                    return -1;
            }

            if (top >= STACK_SIZE - 1) return -1;
            val_stack[++top] = val;
        } else {
            // Must be an integer operand
            char *endptr;
            long val = strtol(tok, &endptr, 10);
            if (*endptr != '\0') {
                return -1; // Invalid token
            }
            if (top >= STACK_SIZE - 1) return -1;
            val_stack[++top] = (long long)val;
        }
    }

    if (top != 0) {
        return -1; // Invalid expression: wrong number of operands
    }

    *result = (int)val_stack[0];
    return 0;
}
