#include "nqueens_solver.hpp"
#include <cmath>
#include <cstdlib>

bool is_safe_placement(const std::vector<int>& queens, int row, int col) {
    for (int r = 0; r < row; ++r) {
        int qcol = queens[r];
        if (qcol == col || std::abs(qcol - col) == std::abs(r - row)) {
            return false;
        }
    }
    return true;
}

static void backtrack_n_queens(int row, int n, std::vector<int>& queens, std::vector<std::vector<std::string>>& solutions) {
    if (row == n) {
        std::vector<std::string> board(n, std::string(n, '.'));
        for (int i = 0; i < n; ++i) {
            board[i][queens[i]] = 'Q';
        }
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (is_safe_placement(queens, row, col)) {
            queens[row] = col;
            backtrack_n_queens(row + 1, n, queens, solutions);
        }
    }
}

void solve_n_queens(int n, std::vector<std::vector<std::string>>& solutions) {
    solutions.clear();
    if (n <= 0) {
        return;
    }
    std::vector<int> queens(n, -1);
    backtrack_n_queens(0, n, queens, solutions);
}

static long long count_bitmask_helper(int cols, int diag1, int diag2, int mask) {
    if (cols == mask) {
        return 1;
    }

    long long count = 0;
    int available = mask & ~(cols | diag1 | diag2);

    while (available > 0) {
        int p = available & -available;
        available -= p;
        count += count_bitmask_helper(cols | p, (diag1 | p) << 1, (diag2 | p) >> 1, mask);
    }

    return count;
}

long long count_n_queens_solutions(int n) {
    if (n <= 0 || n > 30) {
        return 0;
    }
    int mask = (1 << n) - 1;
    return count_bitmask_helper(0, 0, 0, mask);
}
