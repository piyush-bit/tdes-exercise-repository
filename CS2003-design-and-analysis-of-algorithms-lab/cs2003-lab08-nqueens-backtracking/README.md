# CS2003 Lab 08: N-Queens Backtracking & Branch and Bound

## Overview & Background

In microelectronic layout design and autonomous component placement, placing $N$ active interference-emitting components on an $N \times N$ grid requires ensuring that no two components lie on the same row, column, or signal bus line (main or anti-diagonal).

This classic constraint satisfaction problem is equivalent to the **N-Queens Problem**. In this lab, you will implement two algorithms to solve this problem:
1. **Recursive Backtracking with State-Space Traversal**: Generate all distinct grid placement configurations.
2. **Branch and Bound with Bitmask Pruning**: Efficiently count total valid placement configurations without constructing string board objects.

---

## Technical Specifications & Function Contracts

You must complete the implementation in `nqueens_solver.cpp` according to the function declarations in `nqueens_solver.hpp`.

### 1. `bool is_safe_placement(const std::vector<int>& queens, int row, int col)`

Checks whether placing a component/queen at `(row, col)` conflicts with any previously placed queens in rows `0` to `row - 1`.

- **Parameters**:
  - `queens`: A vector of size $\ge$ `row`, where `queens[r]` contains the column index of the queen placed at row `r`.
  - `row`: The current row being evaluated ($0 \le \text{row} < N$).
  - `col`: The candidate column index for the new queen ($0 \le \text{col} < N$).
- **Return Value**: Returns `true` if `(row, col)` does not share a column or diagonal with any queen in rows $0 \dots \text{row}-1$; `false` otherwise.

### 2. `void solve_n_queens(int n, std::vector<std::vector<std::string>>& solutions)`

Finds all distinct valid $N \times N$ placement configurations using recursive depth-first backtracking.

- **Parameters**:
  - `n`: Board dimension $N \times N$ ($N \ge 1$).
  - `solutions`: Output vector to store all valid board solutions.
- **Behavior**:
  - Clears `solutions` before execution.
  - If $N \le 0$, `solutions` remains empty.
  - Each board solution is represented as a `std::vector<std::string>` of size $N$, where each string has length $N$.
  - Use `'Q'` to denote a component/queen and `'.'` to denote an empty grid square.
  - Explore candidate columns in increasing order ($0$ to $N-1$) for standard DFS output ordering.

### 3. `long long count_n_queens_solutions(int n)`

Calculates the total number of distinct valid $N$-Queens placements using **bitmasking and branch-and-bound pruning**.

- **Parameters**:
  - `n`: Board dimension $N \times N$.
- **Return Value**: Total count of valid configurations. Returns `0` for $N \le 0$.
- **Algorithm Requirements**:
  - Must use bitwise operations (`cols`, `diag1`, `diag2`) to maintain occupied columns and diagonals in $O(1)$ time per state check.
  - Avoid creating string boards or allocating dynamic vectors during counting to maximize pruning performance.

---

## Example Input / Output

For $N = 4$:
- `solve_n_queens(4, solutions)` produces 2 valid board configurations:

  **Solution 1:**
  ```text
  .Q..
  ...Q
  Q...
  ..Q.
  ```

  **Solution 2:**
  ```text
  ..Q.
  Q...
  ...Q
  .Q..
  ```

- `count_n_queens_solutions(4)` returns `2`.
- `count_n_queens_solutions(8)` returns `92`.

---

## Local Development & Testing

Use the provided `Makefile` or helper script to test your code:

- **Run Public Tests**:
  ```bash
  make test-public
  # or
  ./run
  ```
- **Clean Build Artifacts**:
  ```bash
  make clean
  # or
  ./run clean
  ```

---

## Grading Breakdown

Grading is executed automatically by the evaluator via the targets defined in `manifest.json`:

1. `test-public` (0 points): Evaluates public test suite locally during development.
2. `test-submission-nqueens-solver` (5 points): Private test suite verifying `is_safe_placement` logic, edge cases ($N=1,2,3$), board string formatting, and exact backtracking solution sets for $N=5,6,7$.
3. `test-submission-branch-bound-pruning` (5 points): Private test suite validating `count_n_queens_solutions` accuracy and execution speed across $N=1 \dots 12$.

Total Score: **10 Points**.
