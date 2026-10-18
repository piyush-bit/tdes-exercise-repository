#include "dynamic_programming.hpp"
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

void test_knapsack_private() {
    // Edge case 1: Zero capacity
    KnapsackResult r1 = knapsack_01_dp(0, {2, 3}, {10, 20});
    assert(r1.max_value == 0);
    assert(r1.selected_indices.empty());

    // Edge case 2: Items exceed capacity
    KnapsackResult r2 = knapsack_01_dp(5, {10, 20}, {100, 200});
    assert(r2.max_value == 0);
    assert(r2.selected_indices.empty());

    // Standard case
    int cap = 50;
    std::vector<int> weights = {10, 20, 30};
    std::vector<int> values = {60, 100, 120};
    KnapsackResult r3 = knapsack_01_dp(cap, weights, values);
    assert(r3.max_value == 220); // Items 1 and 2 (weights 20 + 30 = 50, values 100 + 120 = 220)
    assert(r3.selected_indices == std::vector<int>({1, 2}));

    // Verify weight sum and value sum
    int total_w = 0, total_v = 0;
    for (int idx : r3.selected_indices) {
        total_w += weights[idx];
        total_v += values[idx];
    }
    assert(total_w <= cap);
    assert(total_v == r3.max_value);
}

void test_mcm_private() {
    // Single matrix
    MCMResult r1 = matrix_chain_order({10, 20});
    assert(r1.min_scalar_multiplications == 0);
    assert(r1.optimal_parenthesization == "A1");

    // Two matrices
    MCMResult r2 = matrix_chain_order({10, 20, 30});
    assert(r2.min_scalar_multiplications == 6000);
    assert(r2.optimal_parenthesization == "(A1A2)");

    // Four matrices
    std::vector<int> dims = {40, 20, 30, 10, 30};
    MCMResult r3 = matrix_chain_order(dims);
    assert(r3.min_scalar_multiplications == 26000);
    assert(r3.optimal_parenthesization == "((A1(A2A3))A4)");
}

void test_tsp_private() {
    std::vector<std::vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSPResult res = tsp_dp(dist);
    assert(res.min_cost == 80);
    assert(res.path.size() == 5);
    assert(res.path.front() == 0 && res.path.back() == 0);

    // Verify path cost matches total dist
    int calculated_cost = 0;
    std::vector<bool> visited(4, false);
    for (size_t i = 0; i + 1 < res.path.size(); ++i) {
        int u = res.path[i];
        int v = res.path[i+1];
        calculated_cost += dist[u][v];
        visited[u] = true;
    }
    assert(calculated_cost == res.min_cost);
    for (bool v : visited) {
        assert(v == true);
    }
}

int main() {
    std::cout << "[Private Test] Running test_knapsack_mcm..." << std::endl;
    try {
        test_knapsack_private();
        test_mcm_private();
        test_tsp_private();
        std::cout << "[Private Test] test_knapsack_mcm PASSED!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[Private Test] test_knapsack_mcm FAILED: " << e.what() << std::endl;
        return 1;
    }
}
