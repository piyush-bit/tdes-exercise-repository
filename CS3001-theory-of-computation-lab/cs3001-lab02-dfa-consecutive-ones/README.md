# CS3001 Lab 02: DFA Accepting Three Consecutive Ones

## Overview

In Theory of Computation, a **Deterministic Finite Automaton (DFA)** is a finite-state machine that accepts or rejects strings of symbols and produces a unique computation path for each input string.

In this lab, you will construct a DFA that accepts binary strings containing at least three consecutive `1`s (i.e., substring `"111"`).

---

## Objectives

- Understand state transition logic in Deterministic Finite Automata.
- Implement DFA state tracking in C using conditional logic or transition arrays.
- Correctly classify binary strings into accept (`1`) or reject (`0`) states.

---

## Problem Statement

Implement the following function in `consecutive_ones.c`:

```c
int accepts_three_consecutive_ones(const char *s);
```

### Input Specifications
- `s`: A null-terminated binary string containing characters `'0'` and `'1'`.
- If `s` is `NULL` or contains characters other than `'0'` and `'1'`, the function should return `0` (reject).

### Output Specifications
- Return `1` if the input string contains at least three consecutive `'1'` characters (`"111"`).
- Return `0` otherwise.

---

## DFA Specification

Let $Q = \{q_0, q_1, q_2, q_3\}$ be the set of states:
- **$q_0$ (Start State):** Initial state; 0 consecutive `'1'`s seen.
- **$q_1$:** Exactly 1 consecutive `'1'` seen.
- **$q_2$:** Exactly 2 consecutive `'1'`s seen.
- **$q_3$ (Accept State / Trap State):** At least 3 consecutive `'1'`s seen.

### Transition Function $\delta(q, c)$

| Current State $q$ | Input Symbol `'0'` | Input Symbol `'1'` |
| :--- | :--- | :--- |
| **$q_0$** (Start) | $q_0$ | $q_1$ |
| **$q_1$** | $q_0$ | $q_2$ |
| **$q_2$** | $q_0$ | $q_3$ |
| **$q_3$** (Accept) | $q_3$ | $q_3$ |

---

## Example Test Cases

| Input String | Expected Result | Reason |
| :--- | :--- | :--- |
| `"111"` | `1` | Contains exact substring `"111"` |
| `"01110"` | `1` | Contains substring `"111"` surrounded by zeroes |
| `"1101"` | `0` | Sequence of ones interrupted by `'0'` |
| `"000"` | `0` | No `'1'`s present |
| `"11"` | `0` | Only two consecutive `'1'`s |

---

## Instructions & Building

1. Edit your solution in `consecutive_ones.c`.
2. Run public unit tests locally:
   ```bash
   make test-public
   # or
   ./run
   ```
3. Clean build artifacts:
   ```bash
   make clean
   # or
   ./run clean
   ```
