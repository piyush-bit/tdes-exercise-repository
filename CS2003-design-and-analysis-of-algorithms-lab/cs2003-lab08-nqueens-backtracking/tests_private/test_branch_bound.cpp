#include <iostream>
#include <vector>
#include <chrono>
#include "nqueens_solver.hpp"

struct TestCase {
    int n;
    long long expected;
};

int main() {
    std::cout << "=== Running Private Test Suite: Branch and Bound Bitmask Pruning ===" << std::endl;
    int passed = 0;
    int total = 0;

    std::vector<TestCase> test_cases = {
        {1, 1},
        {2, 0},
        {3, 0},
        {4, 2},
        {5, 10},
        {6, 4},
        {7, 40},
        {8, 92},
        {9, 352},
        {10, 724},
        {11, 2680},
        {12, 14200}
    };

    // Subtest 1: Exact solution counts N=1..12
    total++;
    bool all_counts_correct = true;
    for (const auto& tc : test_cases) {
        long long result = count_n_queens_solutions(tc.n);
        if (result != tc.expected) {
            std::cout << "[FAIL] count_n_queens_solutions(" << tc.n << ") expected " << tc.expected << ", got " << result << std::endl;
            all_counts_correct = false;
        }
    }
    if (all_counts_correct) {
        std::cout << "[PASS] count_n_queens_solutions returned exact counts for N=1..12." << std::endl;
        passed++;
    }

    // Subtest 2: Edge & Invalid inputs (N <= 0)
    total++;
    long long c_zero = count_n_queens_solutions(0);
    long long c_neg = count_n_queens_solutions(-5);
    if (c_zero == 0 && c_neg == 0) {
        std::cout << "[PASS] count_n_queens_solutions returned 0 for non-positive inputs." << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] count_n_queens_solutions failed boundary checks (c_zero=" << c_zero << ", c_neg=" << c_neg << ")." << std::endl;
    }

    // Subtest 3: Performance check for N=12
    total++;
    auto start = std::chrono::high_resolution_clock::now();
    long long c12 = count_n_queens_solutions(12);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    if (c12 == 14200 && duration.count() < 1000.0) { // Should execute in under 1 second
        std::cout << "[PASS] count_n_queens_solutions(12) completed in " << duration.count() << " ms." << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Performance or correctness failure for N=12 (count=" << c12 << ", time=" << duration.count() << " ms)." << std::endl;
    }

    std::cout << "Private Branch & Bound Tests: Passed " << passed << " / " << total << std::endl;
    return (passed == total) ? 0 : 1;
}
