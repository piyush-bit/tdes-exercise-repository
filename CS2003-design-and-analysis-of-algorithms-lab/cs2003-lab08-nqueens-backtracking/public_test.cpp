#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "nqueens_solver.hpp"

static bool validate_board(const std::vector<std::string>& board, int n) {
    if ((int)board.size() != n) return false;
    std::vector<int> queens(n, -1);
    for (int r = 0; r < n; ++r) {
        if ((int)board[r].size() != n) return false;
        int q_count = 0;
        for (int c = 0; c < n; ++c) {
            if (board[r][c] == 'Q') {
                q_count++;
                queens[r] = c;
            } else if (board[r][c] != '.') {
                return false;
            }
        }
        if (q_count != 1) return false;
    }

    for (int r = 0; r < n; ++r) {
        for (int prev = 0; prev < r; ++prev) {
            if (queens[r] == queens[prev] || std::abs(queens[r] - queens[prev]) == std::abs(r - prev)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::cout << "--- Running Public Tests: N-Queens Solver ---" << std::endl;
    int passed = 0;
    int total = 0;

    // Test 1: N = 4 Backtracking Solutions
    total++;
    std::vector<std::vector<std::string>> sol4;
    solve_n_queens(4, sol4);
    if (sol4.size() == 2) {
        bool valid = true;
        for (const auto& board : sol4) {
            if (!validate_board(board, 4)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << "[PASS] Test 1: solve_n_queens(4) returned 2 valid boards." << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] Test 1: solve_n_queens(4) returned boards with invalid placements." << std::endl;
        }
    } else {
        std::cout << "[FAIL] Test 1: solve_n_queens(4) expected 2 solutions, got " << sol4.size() << std::endl;
    }

    // Test 2: N = 4 Count via Branch & Bound
    total++;
    long long count4 = count_n_queens_solutions(4);
    if (count4 == 2) {
        std::cout << "[PASS] Test 2: count_n_queens_solutions(4) returned 2." << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Test 2: count_n_queens_solutions(4) expected 2, got " << count4 << std::endl;
    }

    // Test 3: N = 8 Backtracking Solutions
    total++;
    std::vector<std::vector<std::string>> sol8;
    solve_n_queens(8, sol8);
    if (sol8.size() == 92) {
        bool valid = true;
        for (const auto& board : sol8) {
            if (!validate_board(board, 8)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << "[PASS] Test 3: solve_n_queens(8) returned 92 valid boards." << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] Test 3: solve_n_queens(8) returned invalid boards." << std::endl;
        }
    } else {
        std::cout << "[FAIL] Test 3: solve_n_queens(8) expected 92 solutions, got " << sol8.size() << std::endl;
    }

    // Test 4: N = 8 Count via Branch & Bound
    total++;
    long long count8 = count_n_queens_solutions(8);
    if (count8 == 92) {
        std::cout << "[PASS] Test 4: count_n_queens_solutions(8) returned 92." << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Test 4: count_n_queens_solutions(8) expected 92, got " << count8 << std::endl;
    }

    std::cout << "Summary: Passed " << passed << " / " << total << " public tests." << std::endl;
    return (passed == total) ? 0 : 1;
}
