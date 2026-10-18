# CS3001 Lab 05: Automaton for Even Number of 0s and 1s

## Overview
In Theory of Computation, deterministic finite automata (DFAs) are frequently used to accept regular languages defined by parity constraints. In this lab, you will implement a C function to determine whether a given binary string contains both an **even number of `0`s** and an **even number of `1`s**.

Formally, the language is defined over the alphabet $\Sigma = \{0, 1\}$ as:
$$L = \{ w \in \{0, 1\}^* \mid \text{count}_0(w) \equiv 0 \pmod 2 \text{ and } \text{count}_1(w) \equiv 0 \pmod 2 \}$$

A 4-state automaton can model this problem by maintaining the parity of `0`s and `1`s:
- **$q_0$ (State 0)**: Even `0`s, Even `1`s *(Start & Accepting State)*
- **$q_1$ (State 1)**: Even `0`s, Odd `1`s
- **$q_2$ (State 2)**: Odd `0`s, Even `1`s
- **$q_3$ (State 3)**: Odd `0`s, Odd `1`s

---

## Function Contract

In `even_parity.h`, the function is declared as:

```c
int has_even_zeros_and_ones(const char *s);
```

### Parameters
- `s`: A null-terminated C string consisting of binary digits `'0'` and `'1'`.

### Return Value
- `1`: If the input string `s` contains an even number of `'0'`s **AND** an even number of `'1'`s.
- `0`: Otherwise (if either count is odd, if `s` is `NULL`, or if `s` contains invalid non-binary characters).

### Examples
- `has_even_zeros_and_ones("0011")` $\rightarrow$ `1` (2 zeros, 2 ones)
- `has_even_zeros_and_ones("011")` $\rightarrow$ `0` (1 zero, 2 ones)
- `has_even_zeros_and_ones("")` $\rightarrow$ `1` (0 zeros, 0 ones — both 0 % 2 == 0)
- `has_even_zeros_and_ones("0000")` $\rightarrow$ `1` (4 zeros, 0 ones)
- `has_even_zeros_and_ones("01")` $\rightarrow$ `0` (1 zero, 1 one)

---

## Project Structure

```
cs3001-lab05-even-zeros-ones/
├── manifest.json       # Evaluator configuration
├── README.md           # Instructions
├── Makefile            # Build & test rules
├── run                 # Convenience test script
├── even_parity.h       # Function declaration
├── even_parity.c       # Your implementation (editable)
├── public_test.c       # Public test suite
├── reference/          # Reference solution (for evaluator)
└── tests_private/      # Private grading test suites
```

---

## Instructions

1. Implement `has_even_zeros_and_ones` in `even_parity.c`.
2. Test your implementation locally using `make test-public` or `./run`.
3. Ensure all tests pass without memory or syntax errors.
