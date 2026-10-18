# CS2001 Lab 04: Infix to Postfix Conversion & Postfix Evaluation in C

## Objectives
- Understand stack-based algorithms for parsing and evaluating arithmetic expressions.
- Implement the **Shunting Yard Algorithm** to convert infix expressions to postfix (Reverse Polish Notation).
- Implement a **Postfix Evaluator** stack algorithm supporting multi-digit integer arithmetic and basic operators (`+`, `-`, `*`, `/`, `%`, `^`).

---

## Background & Specifications

### 1. Infix to Postfix Conversion (`infix_to_postfix`)
Arithmetic expressions written in standard infix notation (e.g., `A + B * C`) use operator precedence and parentheses to determine execution order. Postfix notation (e.g., `A B C * +`) eliminates the need for parentheses and explicit precedence rules during evaluation.

#### Operator Rules:
| Operator | Precedence | Associativity | Description |
| :--- | :--- | :--- | :--- |
| `^` | 3 (Highest) | Right-to-Left | Exponentiation (e.g. `2 ^ 3 ^ 2` = `2 ^ (3 ^ 2)` = `512`) |
| `*`, `/`, `%` | 2 | Left-to-Right | Multiplication, Integer Division, Modulo |
| `+`, `-` | 1 (Lowest) | Left-to-Right | Addition, Subtraction |
| `(` , `)` | N/A | N/A | Grouping Parentheses |

#### Output Formatting Rules:
- Output tokens in the `postfix` buffer **must be separated by a single space**.
- Multi-character tokens (e.g., numbers like `10`, variables like `x1`) must be preserved as unified tokens.
- Output string must be properly null-terminated.
- `infix_to_postfix` should return `0` on success, or `-1` if the input infix expression is invalid (e.g., mismatched parentheses or unrecognized symbol).

---

### 2. Postfix Evaluation (`evaluate_postfix`)
Evaluates a space-separated postfix expression containing integer operands and operators using an operand stack.

#### Supported Operators & Behavior:
- `+`: Addition (`a + b`)
- `-`: Subtraction (`a - b`)
- `*`: Multiplication (`a * b`)
- `/`: Integer Division (`a / b`). Must return `-1` error on division by zero.
- `%`: Modulo (`a % b`). Must return `-1` error on modulo by zero.
- `^`: Exponentiation ($a^b$, assuming $b \ge 0$). Must return `-1` error if $b < 0$.

#### Function Contract:
- `int evaluate_postfix(const char *postfix, int *result)`
- Reads space-separated tokens from `postfix`.
- Pushes numbers (positive/negative integer literals) to stack.
- When an operator is encountered, pops the top two values $b$ (right operand) and $a$ (left operand), computes $a \text{ op } b$, and pushes the result back.
- On success, stores the final result in `*result` and returns `0`.
- Returns `-1` if the expression is invalid (insufficient operands, leftover operands, invalid operator, division/modulo by zero, or negative exponent).

---

## Function Prototypes (`infix_postfix.h`)

```c
int infix_to_postfix(const char *infix, char *postfix);
int evaluate_postfix(const char *postfix, int *result);
```

---

## Directory Structure

```
cs2001-lab04-infix-postfix-stack/
├── Dockerfile
├── manifest.json
├── README.md
├── Makefile
├── run
├── infix_postfix.h
├── infix_postfix.c            ← Student implementation (boilerplate)
├── public_test.c              ← Public test suite
├── reference/
│   └── infix_postfix.c        ← Problem setter's reference solution
└── tests_private/
    ├── test_conversion.c      ← Private conversion test suite
    └── test_evaluation.c      ← Private evaluation test suite
```

---

## How to Test & Run

### Local Testing (Student)
To run public tests against your live `infix_postfix.c`:
```bash
make test-public
# or
./run public
```

### Cleanup
To clean up compiled binaries and build artifacts:
```bash
make clean
# or
./run clean
```
