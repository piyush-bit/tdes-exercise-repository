#ifndef DYNAMIC_PROGRAMMING_HPP
#define DYNAMIC_PROGRAMMING_HPP

#include <string>
#include <vector>

// 1. Longest Common Subsequence & Diff Result
struct LCSResult {
    int length;
    std::string lcs;
    std::vector<std::string> diff; // Diff lines e.g. " A", "-B", "+C"
};

LCSResult longest_common_subsequence(const std::string& X, const std::string& Y);

// 2. 0/1 Knapsack Result
struct KnapsackResult {
    int max_value;
    std::vector<int> selected_indices; // 0-based item indices sorted in ascending order
};

KnapsackResult knapsack_01_dp(int capacity, const std::vector<int>& weights, const std::vector<int>& values);

// 3. Matrix Chain Order Result
struct MCMResult {
    int min_scalar_multiplications;
    std::string optimal_parenthesization; // e.g. "((A1A2)A3)"
};

MCMResult matrix_chain_order(const std::vector<int>& dims);

// 4. Traveling Salesperson Problem (Bitmask DP) Result
struct TSPResult {
    int min_cost;
    std::vector<int> path; // e.g. {0, 1, 3, 2, 0}
};

TSPResult tsp_dp(const std::vector<std::vector<int>>& dist);

#endif // DYNAMIC_PROGRAMMING_HPP
