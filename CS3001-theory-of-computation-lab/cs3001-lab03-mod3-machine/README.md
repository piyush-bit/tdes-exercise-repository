# CS3001 Lab 03: Binary Modulo 3 Automaton

## Overview
In Theory of Computation, a Deterministic Finite Automaton (DFA) can process a sequence of symbols (such as binary digits) to determine properties of the input word. In this lab, you will design and implement a finite state machine / DFA in C that accepts a string of binary digits and computes its remainder when divided by 3 ($N \pmod 3$).

## Problem Statement
Implement the function:
```c
int compute_mod3(const char *binary_str);
```

Given a binary string (processed from left to right, Most Significant Bit to Least Significant Bit):
- Compute the integer remainder when the binary value is divided by 3.
- The return value must be `0`, `1`, or `2`.
- If `binary_str` is `NULL`, empty `""`, or contains invalid characters (anything other than `'0'` or `'1'`), return `-1`.

## Mathematical Model / DFA State Transitions
Let the current remainder state be $S \in \{0, 1, 2\}$.
- Initial state $S_0 = 0$.
- For each binary digit $c$:
  - If $c = '0'$, $S_{new} = (S \times 2 + 0) \pmod 3$
  - If $c = '1'$, $S_{new} = (S \times 2 + 1) \pmod 3$

### Transition Table
| Current State $S$ | Input Bit `'0'` | Input Bit `'1'` |
|-------------------|-----------------|-----------------|
| $q_0$ (rem 0)    | $q_0$ (rem 0)   | $q_1$ (rem 1)   |
| $q_1$ (rem 1)    | $q_2$ (rem 2)   | $q_0$ (rem 0)   |
| $q_2$ (rem 2)    | $q_1$ (rem 1)   | $q_2$ (rem 2)   |

## Examples
- `"101"` $\rightarrow$ Decimal $5 \rightarrow 5 \pmod 3 = 2$
- `"110"` $\rightarrow$ Decimal $6 \rightarrow 6 \pmod 3 = 0$
- `"100"` $\rightarrow$ Decimal $4 \rightarrow 4 \pmod 3 = 1$

## Testing
To test your implementation locally:
```bash
make test-public
```
or use the runner script:
```bash
./run public
```
