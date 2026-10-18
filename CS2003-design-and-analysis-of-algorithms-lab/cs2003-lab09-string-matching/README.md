# CS2003 Lab 09: Security Log Pattern & String Matcher (Naive vs Rabin-Karp)

## Problem Overview

String searching algorithms are essential components of intrusion detection systems (IDS), log analyzer engines, and malware scanners.

In this lab, you will implement two core string matching algorithms in C++:
1. **Naive String Matching Algorithm**: A brute-force sliding window approach checking all alignment offsets ($O(N \times M)$ time complexity).
2. **Rabin-Karp Algorithm**: A hash-based pattern matching algorithm using rolling hash functions to efficiently locate pattern occurrences ($O(N + M)$ average time complexity).

---

## File Structure

- `string_matching.hpp` — Function prototypes and API contract (Do not modify).
- `string_matching.cpp` — **Your working file.** Implement functions marked with `// TODO:`.
- `public_test.cpp` — Public test suite.
- `Makefile` — Build targets (`make test-public`).
- `run` — Executable wrapper script (`./run`).

---

## API Function Specifications

### 1. `std::vector<int> naive_string_match(const std::string& text, const std::string& pattern)`
Iterates over `text` and checks if `pattern` matches at each index offset `i`.
- **Returns**: A `std::vector<int>` containing 0-based starting indices of all pattern matches.
- Returns empty vector if `text` or `pattern` is empty, or `pattern.length() > text.length()`.

### 2. `std::vector<int> rabin_karp_string_match(const std::string& text, const std::string& pattern, int prime = 101)`
Computes pattern hash and rolling hash of `text` windows using polynomial rolling hash logic (`(hash * d + char) % prime`). Upon hash match, verifies actual substring equivalence to avoid hash collisions.
- **Returns**: A `std::vector<int>` containing 0-based starting indices of all matches.

---

## How to Test Locally

```bash
make test-public
# OR
./run
```

---

## Grading Criteria

| Target | Points | Type | Description |
| :--- | :---: | :---: | :--- |
| `make test-public` | 0 | Public | Local student test execution |
| `make test-submission-naive-matcher` | 5 | Private | Naive matcher correctness, edge cases, overlapping matches |
| `make test-submission-rabin-karp-matcher` | 5 | Private | Rabin-Karp rolling hash, multi-occurrence search, collision safety |
| **Total** | **10** | | |
