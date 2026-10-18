# CS3001 Lab 01: DFA String Matching (Start/End Patterns)

## Overview
In Theory of Computation, a **Deterministic Finite Automaton (DFA)** is a theoretical machine used to recognize regular languages. A DFA consists of:
- A finite set of states ($Q$)
- An input alphabet ($\Sigma$)
- A transition function ($\delta: Q \times \Sigma \to Q$)
- An initial state ($q_0 \in Q$)
- A set of accept/final states ($F \subseteq Q$)

In this lab, you will implement string matching algorithms using DFA state transitions in C. Instead of using high-level string library functions, you will model state transitions explicitly as you process characters one by one.

---

## Task Description
You are required to complete three C functions in `dfa_match.c` declared in `dfa_match.h`:

### 1. `int starts_with_a(const char *s)`
Accepts strings that start with the character `'a'`.
- Returns `1` if the string starts with `'a'`.
- Returns `0` if the string does not start with `'a'`, is empty (`""`), or is `NULL`.

**State Machine Specification:**
- $Q = \{q_0, q_1, q_2\}$
- $q_0$: Initial state (before reading any characters).
- $q_1$: Accept state (first character was `'a'`).
- $q_2$: Dead/Reject state (first character was not `'a'`).
- $\Sigma$: All ASCII characters.
- $F = \{q_1\}$.

**Transitions:**
- From $q_0$: on `'a'`, transition to $q_1$; on any other character, transition to $q_2$.
- From $q_1$: stay in $q_1$ for all subsequent characters.
- From $q_2$: stay in $q_2$ for all subsequent characters.

---

### 2. `int ends_with_b(const char *s)`
Accepts strings that end with the character `'b'`.
- Returns `1` if the last character of the string is `'b'`.
- Returns `0` if the string does not end with `'b'`, is empty (`""`), or is `NULL`.

**State Machine Specification:**
- $Q = \{q_0, q_1\}$
- $q_0$: Start / non-`'b'` end state (empty or last character read was not `'b'`).
- $q_1$: Accept state (last character read was `'b'`).
- $\Sigma$: All ASCII characters.
- $F = \{q_1\}$.

**Transitions:**
- From any state: on `'b'`, transition to $q_1$; on any other character, transition to $q_0$.

---

### 3. `int starts_a_ends_b(const char *s)`
Accepts strings that **both** start with `'a'` **and** end with `'b'`.
- Returns `1` if the string starts with `'a'` and ends with `'b'`.
- Returns `0` otherwise (including empty string `""` or `NULL`).

**State Machine Specification:**
- $Q = \{q_0, q_1, q_2, q_3\}$
- $q_0$: Initial state.
- $q_1$: Dead state (string did not start with `'a'`).
- $q_2$: Non-accept state (starts with `'a'`, but current ending character is not `'b'`).
- $q_3$: Accept state (starts with `'a'`, and current ending character is `'b'`).
- $F = \{q_3\}$.

**Transitions:**
- From $q_0$: on `'a'`, transition to $q_2$; on any other character, transition to $q_1$.
- From $q_1$: stay in $q_1$ on all inputs.
- From $q_2$ or $q_3$: on `'b'`, transition to $q_3$; on any other character, transition to $q_2$.

---

## File Structure
```
cs3001-lab01-dfa-string-match/
├── manifest.json        # Lab metadata and grading configuration
├── README.md            # Lab instructions (this file)
├── dfa_match.h          # Function declarations
├── dfa_match.c          # Student implementation (edit this)
├── public_test.c        # Public assertion test suite
├── reference/
│   └── dfa_match.c      # Reference solution (for evaluator)
├── tests_private/
│   ├── test_start_end_patterns.c
│   └── test_combined_dfa.c
├── Makefile             # Build automation using Strategy B (Inject & Restore)
└── run                  # Execution helper script
```

---

## Building and Running Tests

### 1. Run Public Tests
To compile and execute the public test suite against your `dfa_match.c`:
```bash
make test-public
# or
./run public
```

### 2. Clean Build Artifacts
```bash
make clean
# or
./run clean
```

---

## Edge Case Handling
- **`NULL` Pointers**: All functions must safely return `0` when `s == NULL`.
- **Empty Strings**: An empty string `""` contains 0 characters, so it cannot start with `'a'` or end with `'b'`. Returns `0`.
- **Single Character Strings**: E.g., `"a"` starts with `'a'` (returns 1 for `starts_with_a`) but does NOT end with `'b'` (returns 0 for `starts_a_ends_b`).
- **Case Sensitivity**: `'a'` and `'b'` are lowercase. Uppercase `'A'` or `'B'` should be treated as non-matching characters.
