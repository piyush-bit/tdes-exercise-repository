#include "dynamic_programming.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

void test_lcs_public() {
    std::cout << "[Public Test] Running LCS test..." << std::endl;
    std::string X = "AGGTAB";
    std::string Y = "GXTXAYB";
    LCSResult res = longest_common_subsequence(X, Y);

    std::cout << "  LCS Length: " << res.length << " (Expected: 4)" << std::endl;
    std::cout << "  LCS String: " << res.lcs << " (Expected: GTAB)" << std::endl;

    assert(res.length == 4);
    assert(res.lcs == "GTAB");
    assert(!res.diff.empty());
    std::cout << "  LCS public test PASSED." << std::endl;
}

void test_knapsack_public() {
    std::cout << "[Public Test] Running 0/1 Knapsack test..." << std::endl;
    int capacity = 5;
    std::vector<int> weights = {2, 3, 4, 5};
    std::vector<int> values = {3, 4, 5, 6};

    KnapsackResult res = knapsack_01_dp(capacity, weights, values);

    std::cout << "  Max Value: " << res.max_value << " (Expected: 7)" << std::endl;
    assert(res.max_value == 7);
    assert(res.selected_indices == std::vector<int>({0, 1}));
    std::cout << "  0/1 Knapsack public test PASSED." << std::endl;
}

void test_mcm_public() {
    std::cout << "[Public Test] Running Matrix Chain Order test..." << std::endl;
    std::vector<int> dims = {10, 30, 5, 60};
    MCMResult res = matrix_chain_order(dims);

    std::cout << "  Min Multiplications: " << res.min_scalar_multiplications << " (Expected: 4500)" << std::endl;
    std::cout << "  Parenthesization: " << res.optimal_parenthesization << " (Expected: ((A1A2)A3))" << std::endl;

    assert(res.min_scalar_multiplications == 4500);
    assert(res.optimal_parenthesization == "((A1A2)A3)");
    std::cout << "  Matrix Chain Order public test PASSED." << std::endl;
}

int main() {
    std::cout << "=== Running CS2003 Lab 04 Public Tests ===" << std::endl;
    try {
        test_lcs_public();
        test_knapsack_public();
        test_mcm_public();
        std::cout << "=== All Public Tests Passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Public test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
