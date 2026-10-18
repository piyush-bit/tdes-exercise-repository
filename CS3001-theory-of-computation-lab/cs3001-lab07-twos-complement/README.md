# CS3001 Lab 07: Binary 2's Complement Transducer

## Overview
In Theory of Computation and Digital Logic, a **Finite State Transducer (FST)** or **Mealy Machine** can compute the 2's complement of a binary number bit by bit. The 2's complement representation of a binary string is obtained by scanning bits from least significant bit (LSB / rightmost) to most significant bit (MSB / leftmost):
1. Copy all trailing `'0'` bits and the first `'1'` bit without modification.
2. Invert (flip) all remaining bits to the left of the first `'1'` bit (`'0'` becomes `'1'`, `'1'` becomes `'0'`).

In this lab, you will implement `compute_twos_complement` in C to process an input binary string and store its 2's complement representation in an output buffer.

## Objectives
- Understand bitwise transformations and transducer logic for binary arithmetic.
- Implement string manipulation in C safely.
- Output the exact 2's complement representation of binary strings.

## Function Signature
In `twos_complement.h`:
```c
void compute_twos_complement(const char *binary_in, char *binary_out);
```

### Parameters
- `binary_in`: A null-terminated string containing binary characters (`'0'` and `'1'`).
- `binary_out`: A pre-allocated character buffer where the resulting 2's complement string must be written. It will always have sufficient space for the output string plus the null-terminator `'\0'`.

## Examples
- `binary_in = "1010"` -> `binary_out = "0110"`
- `binary_in = "1100"` -> `binary_out = "0100"`
- `binary_in = "0000"` -> `binary_out = "0000"`
- `binary_in = "1111"` -> `binary_out = "0001"`

## Instructions
1. Implement your solution in `twos_complement.c`.
2. Test your implementation locally using:
   ```bash
   make test-public
   ```
   or using the helper script:
   ```bash
   ./run
   ```
