# CS3001 Lab 10: Turing Machine for a^n b^n c^n

## Objective
Implement a Turing Machine recognizer in C for the context-sensitive language:
$$L = \{ a^n b^n c^n \mid n \ge 1 \}$$

## Problem Description
You are given a null-terminated string `s`. Your goal is to write a function `int is_valid_anbncn(const char *s)` that simulates or checks the language acceptance criteria of a deterministic Turing Machine.

- **Accept (return `1`)**: If the string `s` consists of $n$ `'a'`s followed by $n$ `'b'`s followed by $n$ `'c'`s, where $n \ge 1$.
- **Reject (return `0`)**: Otherwise (e.g., mismatched counts, out-of-order characters, empty string, invalid characters, or `NULL` input).

### Examples
- `"abc"` $\rightarrow$ `1` ($n=1$)
- `"aabbcc"` $\rightarrow$ `1` ($n=2$)
- `"aaabbbccc"` $\rightarrow$ `1` ($n=3$)
- `"aabbc"` $\rightarrow$ `0` (mismatched counts)
- `"aabcc"` $\rightarrow$ `0` (mismatched counts)
- `"ab"` $\rightarrow$ `0` (missing `'c'`)
- `""` $\rightarrow$ `0` ($n \ge 1$ required)
- `"abcabc"` $\rightarrow$ `0` (invalid ordering)

## Function Contract
In `turing_anbncn.h`:
```c
int is_valid_anbncn(const char *s);
```

Implement your solution in `turing_anbncn.c`.

## How to Test
Run the public tests locally:
```bash
./run
```
or
```bash
make test-public
```
