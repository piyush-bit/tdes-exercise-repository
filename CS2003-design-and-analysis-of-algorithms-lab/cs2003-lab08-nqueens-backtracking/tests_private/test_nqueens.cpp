#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "nqueens_solver.hpp"

static bool validate_board_structure(const std::vector<std::string>& board, int n) {
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
    std::cout << "=== Running Private Test Suite: N-Queens Backtracking Solver ===" << std::endl;
    int passed = 0;
    int total = 0;

    // Subtest 1: is_safe_placement unit checks
    total++;
    {
        std::vector<int> q = {1, 3, 0}; // 3 queens placed in rows 0, 1, 2
        // placing at row 3, col 2 -> safe?
        // r0(1): abs(1-2)=1 != 3-0=3 (ok)
        // r1(3): abs(3-2)=1 != 3-1=2 (ok)
        // r2(0): abs(0-2)=2 == 3-2=1? no, abs(0-2)=2 != 1 (ok)
        // cols: 1!=2, 3!=2, 0!=2 (ok) -> safe
        bool safe1 = is_safe_placement(q, 3, 2);
        // placing at row 3, col 1 -> same col as r0 (conflict)
        bool safe2 = is_safe_placement(q, 3, 1);
        // placing at row 3, col 3 -> diagonal with r2(0)? row diff 3-2=1, col diff 3-0=3 (ok). diagonal with r1(3)? col diff 3-3=0 (conflict)
        bool safe3 = is_safe_placement(q, 3, 3);

        if (safe1 && !safe2 && !safe3) {
            std::cout << "[PASS] is_safe_placement correctly identifies safe and conflicting coordinates." << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] is_safe_placement failed basic safety checks (safe1=" << safe1 << ", safe2=" << safe2 << ", safe3=" << safe3 << ")." << std::endl;
        }
    }

    // Subtest 2: Edge cases N=1, N=2, N=3
    total++;
    {
        std::vector<std::vector<std::string>> sol1, sol2, sol3;
        solve_n_queens(1, sol1);
        solve_n_queens(2, sol2);
        solve_n_queens(3, sol3);

        bool pass1 = (sol1.size() == 1 && sol1[0].size() == 1 && sol1[0][0] == "Q");
        bool pass2 = (sol2.size() == 0);
        bool pass3 = (sol3.size() == 0);

        if (pass1 && pass2 && pass3) {
            std::cout << "[PASS] Edge cases N=1, N=2, N=3 handled correctly." << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] Edge cases N=1, 2, 3 failed (sol1: " << sol1.size() << ", sol2: " << sol2.size() << ", sol3: " << sol3.size() << ")." << std::endl;
        }
    }

    // Subtest 3: Solution count & structure for N=5, 6, 7
    total++;
    {
        struct TestPair { int n; size_t expected_count; };
        std::vector<TestPair> cases = {{5, 10}, {6, 4}, {7, 40}};
        bool all_valid = true;

        for (const auto& tc : cases) {
            std::vector<std::vector<std::string>> sol;
            solve_n_queens(tc.n, sol);
            if (sol.size() != tc.expected_count) {
                std::cout << "[FAIL] N=" << tc.n << " expected " << tc.expected_count << " solutions, got " << sol.size() << std::endl;
                all_valid = false;
                break;
            }
            for (const auto& board : sol) {
                if (!validate_board_structure(board, tc.n)) {
                    std::cout << "[FAIL] Invalid board configuration detected for N=" << tc.n << std::endl;
                    all_valid = false;
                    break;
                }
            }
            if (!all_valid) break;
        }

        if (all_valid) {
            std::cout << "[PASS] solve_n_queens for N=5, 6, 7 produced exact expected counts and valid boards." << std::endl;
            passed++;
        }
    }

    // Subtest 4: Buffer reuse / vector clearing check
    total++;
    {
        std::vector<std::vector<std::string>> sol;
        sol.push_back({"DUMMY"});
        solve_n_queens(4, sol);
        if (sol.size() == 2 && sol[0][0] != "DUMMY") {
            std::cout << "[PASS] solve_n_queens properly clears output container before populating." << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] solve_n_queens did not properly clear pre-existing content in output vector." << std::endl;
        }
    }

    std::cout << "Private N-Queens Solver Tests: Passed " << passed << " / " << total << std::endl;
    return (passed == total) ? 0 : 1;
}
