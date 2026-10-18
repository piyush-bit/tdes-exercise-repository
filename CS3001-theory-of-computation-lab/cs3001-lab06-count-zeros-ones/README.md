# CS3001 Lab 06: Automaton Counter for 0s and 1s

## Overview
In Theory of Computation, deterministic finite automata (DFAs) and finite-state devices process input strings symbol by symbol over a given alphabet $\Sigma = \{'0', '1'\}$. A fundamental task when analyzing binary input streams is scanning and counting the occurrences of each symbol.

In this lab, you will write a C function that scans a null-terminated binary string `s` and populates integer counters for '0's and '1's.

## Problem Specification

You must implement the function:

```c
void count_zeros_and_ones(const char *s, int *count_0, int *count_1);
```

### Parameters
- `s`: A pointer to a null-terminated C string representing the input string.
- `count_0`: A pointer to an integer where the total count of `'0'` characters must be stored.
- `count_1`: A pointer to an integer where the total count of `'1'` characters must be stored.

### Expected Behavior
1. If `s` is valid (non-NULL), iterate through the string and count all occurrences of `'0'` and `'1'`.
2. Write the computed count of `'0'`s into `*count_0` if `count_0` is non-NULL.
3. Write the computed count of `'1'`s into `*count_1` if `count_1` is non-NULL.
4. If `s` is `NULL`, store `0` into `*count_0` and `*count_1` (if the respective pointers are non-NULL).
5. If `s` is an empty string `""`, `*count_0` and `*count_1` should both be `0`.

### Example Test Cases

| Input String (`s`) | `*count_0` | `*count_1` |
| :--- | :--- | :--- |
| `"01011"` | `2` | `3` |
| `"0000"` | `4` | `0` |
| `"111"` | `0` | `3` |
| `""` | `0` | `0` |

## Building and Testing Locally

You can test your implementation using `make` or the `./run` script:

- **Run Public Tests:**
  ```bash
  make test-public
  # or
  ./run public
  ```

- **Clean Build Artifacts:**
  ```bash
  make clean
  # or
  ./run clean
  ```
