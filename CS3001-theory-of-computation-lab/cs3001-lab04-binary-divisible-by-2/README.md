# CS3001 Lab 04: Binary Divisible by 2 Automaton

## Overview
In Theory of Computation, regular languages and deterministic finite automata (DFA) can process strings over an alphabet $\Sigma = \{'0', '1'\}$ to decide properties of numbers represented in binary.

In this lab, you will implement a C function `is_binary_divisible_by_2` that checks whether a given binary string input represents an even binary integer (i.e., divisible by 2).

## Mathematical / Automaton Concept
A binary string $S \in \{'0', '1\}^+$ represents a non-negative integer in base 2.
- A binary number is divisible by 2 if and only if its least significant digit (the last character) is `'0'`.
- If the binary string ends in `'1'`, the number is odd (remainder 1 modulo 2), so it is not divisible by 2.
- An empty string `""`, `NULL` pointer, or string containing non-binary characters is invalid and should return `0`.

### Examples
- `"1010"` (decimal 10) $\rightarrow$ Even $\rightarrow$ returns `1`
- `"1011"` (decimal 11) $\rightarrow$ Odd $\rightarrow$ returns `0`
- `"0"` (decimal 0) $\rightarrow$ Even $\rightarrow$ returns `1`
- `"1"` (decimal 1) $\rightarrow$ Odd $\rightarrow$ returns `0`

## Function Signature
In `divisible_by_2.h`:
```c
int is_binary_divisible_by_2(const char *s);
```

### Parameters & Return Value
- **`s`**: A null-terminated string representing a binary number.
- **Return Value**: Returns `1` if `s` is a valid binary string divisible by 2 (even), or `0` otherwise.

## Instructions
1. Implement your solution inside `divisible_by_2.c`.
2. Do not modify `divisible_by_2.h` or test runner files.

## Running Tests
Run the public test suite locally:
```bash
make test-public
# or
./run
```

To clean build artifacts:
```bash
make clean
# or
./run clean
```
