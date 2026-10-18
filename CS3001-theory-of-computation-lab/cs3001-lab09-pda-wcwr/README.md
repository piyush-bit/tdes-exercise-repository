# CS3001 Lab 09: Pushdown Automaton for $W c W^R$

## Objective

Implement a Deterministic Pushdown Automaton (DPDA) recognition function in C to determine whether an input string belongs to the context-free language:

$$L = \{ w c w^R \mid w \in \{a, b\}^* \}$$

where:
- $w$ is a sequence of characters from $\{a, b\}$ (or case-insensitive $\{a, b, A, B\}$).
- $c$ (or $'C'$) is the exact center marker character.
- $w^R$ is the reversal of $w$.

## Function Signature

```c
int is_valid_wcwr(const char *s);
```

## Specification & Requirements

1. **Return Values**:
   - Return `1` if the string `s` belongs to $L = \{ w c w^R \mid w \in \{a,b\}^* \}$.
   - Return `0` if the string `s` is invalid, malformed, NULL, or not in $L$.

2. **Language Rules**:
   - There must be **exactly one** center marker character (`'c'` or `'C'`).
   - The prefix before the center marker ($w$) and suffix after the center marker ($w^R$) must have equal length.
   - The suffix $w^R$ must be the exact character-by-character reverse of $w$.
   - Characters in $w$ must consist only of valid symbols ('a', 'b', 'A', 'B').

3. **Examples**:
   - `is_valid_wcwr("abCba")` $\rightarrow$ `1` ($w = \text{"ab"}$, $w^R = \text{"ba"}$)
   - `is_valid_wcwr("abcba")` $\rightarrow$ `1` ($w = \text{"ab"}$, center = `'c'`)
   - `is_valid_wcwr("aCa")` $\rightarrow$ `1` ($w = \text{"a"}$, $w^R = \text{"a"}$)
   - `is_valid_wcwr("C")` $\rightarrow$ `1` ($w = \text{""}$, $w^R = \text{""}$)
   - `is_valid_wcwr("abCab")` $\rightarrow$ `0` (suffix is $w$, not $w^R$)
   - `is_valid_wcwr("aCab")` $\rightarrow$ `0` (length mismatch)
   - `is_valid_wcwr("abc")` $\rightarrow$ `0` (length mismatch / missing suffix)
   - `is_valid_wcwr(NULL)` $\rightarrow$ `0`

## Building & Testing

- Run public tests:
  ```bash
  make test-public
  # OR
  ./run
  ```

- Clean build artifacts:
  ```bash
  make clean
  # OR
  ./run clean
  ```
