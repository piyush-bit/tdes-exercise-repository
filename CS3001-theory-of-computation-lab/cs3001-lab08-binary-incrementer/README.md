# CS3001 Lab 08: Binary Incrementer Transducer

## Overview
In Theory of Computation, finite state transducers (Mealy/Moore machines) process input strings symbol by symbol and produce output strings. In this lab, you will implement a binary incrementer transducer in C.

Given an input binary string `binary_in` representing a non-negative integer in binary (with the most significant bit on the left), your program must compute the binary string representing that integer plus 1 and store the null-terminated result in `binary_out`.

## Requirements

Implement the following function in `binary_incrementer.c`:

```c
void increment_binary(const char *binary_in, char *binary_out);
```

### Specifications
1. **Input Format**: `binary_in` is a valid, null-terminated string consisting of binary digits (`'0'` and `'1'`).
2. **Output Format**: Write the null-terminated incremented binary string into `binary_out`.
3. **Carry and Overflow Handling**:
   - If incrementing causes a carry to ripple through all bits (e.g., `"111"` + 1), the resulting binary string will be one character longer (e.g., `"1000"`).
   - If no carry overflows past the most significant bit (e.g., `"1011"` + 1), the result has the same length (e.g., `"1100"`).
4. **Examples**:
   - `binary_in = "0"` $\rightarrow$ `binary_out = "1"`
   - `binary_in = "1011"` $\rightarrow$ `binary_out = "1100"`
   - `binary_in = "111"` $\rightarrow$ `binary_out = "1000"`
   - `binary_in = "011"` $\rightarrow$ `binary_out = "100"`

## Building and Testing

To test your implementation locally:

```bash
make test-public
```

or use the runner script:

```bash
./run
```
