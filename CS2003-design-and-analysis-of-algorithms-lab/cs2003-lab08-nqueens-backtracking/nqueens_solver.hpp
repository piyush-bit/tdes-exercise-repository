#ifndef NQUEENS_SOLVER_HPP
#define NQUEENS_SOLVER_HPP

#include <vector>
#include <string>

/**
 * Checks whether placing a queen at grid position (row, col) is safe from attack
 * by previously placed queens in rows 0 to row - 1.
 *
 * @param queens Vector where queens[r] indicates the column index of the queen in row r.
 * @param row The current row where placement is being evaluated.
 * @param col The column index where a queen is proposed to be placed.
 * @return true if the position (row, col) does not conflict with any queen in rows 0..row-1, false otherwise.
 */
bool is_safe_placement(const std::vector<int>& queens, int row, int col);

/**
 * Finds all distinct N-Queens board solutions for an N x N chessboard.
 * Each solution is represented as a vector of N strings, where '.' denotes an empty space
 * and 'Q' denotes a queen.
 *
 * @param n Size of the board (N x N) and number of queens to place.
 * @param solutions Vector to be populated with all distinct valid board configurations.
 */
void solve_n_queens(int n, std::vector<std::vector<std::string>>& solutions);

/**
 * Counts the total number of distinct N-Queens solutions for an N x N board
 * using bitmasking / branch-and-bound pruning for optimal execution performance.
 *
 * @param n Size of the board (N x N).
 * @return Total number of distinct valid placement configurations.
 */
long long count_n_queens_solutions(int n);

#endif // NQUEENS_SOLVER_HPP
