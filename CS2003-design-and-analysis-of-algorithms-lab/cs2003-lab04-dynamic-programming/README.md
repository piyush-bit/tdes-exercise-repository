# CS2003 Lab 04: Dynamic Programming Engine

Welcome to CS2003 Lab 04! In this lab, you will build a versatile Dynamic Programming Engine in C++ implementing four classic DP algorithms, along with optimal path/sequence reconstruction.

---

## Learning Objectives

By completing this lab, you will learn to:
1. Formulate 2D and 3D Dynamic Programming state transitions.
2. Reconstruct optimal solutions (backtracking through DP tables for LCS diff, item selection, parenthesization, and tour paths).
3. Apply matrix chain order algorithms to optimize matrix multiplication sequences.
4. Implement Bitmask Dynamic Programming for NP-hard optimization problems (Traveling Salesperson Problem / Held-Karp algorithm).

---

## Task Requirements & Function Specifications

You are required to implement the functions prototyped in `dynamic_programming.hpp`:

### 1. Longest Common Subsequence & Diff (`longest_common_subsequence`)

```cpp
LCSResult longest_common_subsequence(const std::string& X, const std::string& Y);
```

- **Problem:** Compute the longest common subsequence between sequence $X$ (length $m$) and sequence $Y$ (length $n$), as well as an edit diff script.
- **Return Type:** `LCSResult` containing:
  - `length`: Integer length of the LCS.
  - `lcs`: The reconstructed LCS string.
  - `diff`: A `std::vector<std::string>` representing diff tokens from $X$ to $Y$:
    - `" c"` (space prefix + char): Character `c` matched (present in LCS).
    - `"-c"` (minus prefix + char): Character `c` deleted from $X$.
    - `"+c"` (plus prefix + char): Character `c` inserted into $Y$.
- **Backtracking Rule for Diff:**
  - Build DP table `dp[i][j]` representing LCS length of $X[0..i-1]$ and $Y[0..j-1]$.
  - Backtrack from $i=m, j=n$ down to $0, 0$:
    - If $i > 0$ and $j > 0$ and $X[i-1] == Y[j-1]$, record `" " + X[i-1]`, move to $(i-1, j-1)$.
    - Else if $j > 0$ and ($i == 0$ or `dp[i][j-1] >= dp[i-1][j]`), record `"+" + Y[j-1]`, move to $(i, j-1)$.
    - Else if $i > 0$, record `"-" + X[i-1]`, move to $(i-1, j)$.
  - Reverse the reconstructed tokens/string.

---

### 2. 0/1 Knapsack Problem (`knapsack_01_dp`)

```cpp
KnapsackResult knapsack_01_dp(int capacity, const std::vector<int>& weights, const std::vector<int>& values);
```

- **Problem:** Given $N$ items with positive integer weights and values, find the subset of items that maximizes total value without exceeding total `capacity`.
- **Return Type:** `KnapsackResult` containing:
  - `max_value`: Maximum achievable total value.
  - `selected_indices`: 0-based item indices included in the optimal knapsack, sorted in ascending order.
- **Backtracking Rule:**
  - Standard 2D DP table `dp[i][w]`.
  - Backtrack from item $N$ to 1: if `dp[i][w] != dp[i-1][w]`, item $i-1$ was selected! Decrement $w$ by `weights[i-1]`.

---

### 3. Matrix Chain Multiplication (`matrix_chain_order`)

```cpp
MCMResult matrix_chain_order(const std::vector<int>& dims);
```

- **Problem:** Given matrix dimensions $p_0, p_1, \dots, p_n$ representing matrices $A_1 (p_0 \times p_1), A_2 (p_1 \times p_2), \dots, A_n (p_{n-1} \times p_n)$, compute the minimum number of scalar multiplications required to multiply the chain, and the optimal parenthesization string.
- **Return Type:** `MCMResult` containing:
  - `min_scalar_multiplications`: Minimum scalar multiplications.
  - `optimal_parenthesization`: String representation of matrix parenthesization using 1-based matrix labels `A1`, `A2`, etc.
  - Example: `dims = {10, 30, 5, 60}` ($A_1: 10 \times 30, A_2: 30 \times 5, A_3: 5 \times 60$)
    - `min_scalar_multiplications`: `4500`
    - `optimal_parenthesization`: `"((A1A2)A3)"`

---

### 4. Traveling Salesperson Problem (`tsp_dp`)

```cpp
TSPResult tsp_dp(const std::vector<std::vector<int>>& dist);
```

- **Problem:** Given an $N \times N$ distance matrix `dist`, find the minimum-cost tour that starts at city 0, visits every city $0 \dots N-1$ exactly once, and returns to city 0.
- **Return Type:** `TSPResult` containing:
  - `min_cost`: Minimum tour cost.
  - `path`: A `std::vector<int>` containing the city sequence starting and ending with 0 (e.g. `{0, 1, 3, 2, 0}`).
- **Algorithm:** Use Bitmask Dynamic Programming (Held-Karp algorithm). State `dp[mask][u]` stores the minimum cost to visit the set of cities represented by `mask`, ending at city `u`.

---

## Verification & Testing

To test your implementation locally:

```bash
make test-public
# or
./run public
```

Grading will evaluate your code against hidden private test suites (`make test-submission-lcs-diff` and `make test-submission-knapsack-mcm`).
