#include "greedy_huffman.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

static int tests_passed = 0;
static int tests_failed = 0;

static void assert_double_eq(double val1, double val2, const std::string& test_name) {
    if (std::abs(val1 - val2) < 1e-4) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << " (Expected " << val2 << ", got " << val1 << ")\n";
        tests_failed++;
    }
}

static void assert_bool(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << "\n";
        tests_passed++;
    } else {
        std::cout << "[FAIL] " << test_name << "\n";
        tests_failed++;
    }
}

void test_standard_knapsack() {
    std::vector<Item> items = {
        {101, 10.0, 60.0},
        {102, 20.0, 100.0},
        {103, 30.0, 120.0}
    };
    std::vector<double> fractions;
    double val = fractional_knapsack_greedy(50.0, items, fractions);
    assert_double_eq(val, 240.0, "Private Knapsack: Standard Maximum Value");
    assert_bool(fractions.size() == 3, "Private Knapsack: Fraction Vector Size");
    if (fractions.size() == 3) {
        assert_double_eq(fractions[0], 1.0, "Private Knapsack: Item 101 Fraction");
        assert_double_eq(fractions[1], 1.0, "Private Knapsack: Item 102 Fraction");
        assert_double_eq(fractions[2], 2.0 / 3.0, "Private Knapsack: Item 103 Fraction");
    }
}

void test_tie_breaking() {
    // Both items have ratio = 5.0 (50/10 = 5.0, 100/20 = 5.0)
    // Item 10 has id=10, Item 20 has id=20
    // Capacity = 15. Item 10 (wt 10) taken fully (1.0), Item 20 (wt 20) taken 5/20 = 0.25
    std::vector<Item> items = {
        {20, 20.0, 100.0},
        {10, 10.0, 50.0}
    };
    std::vector<double> fractions;
    double val = fractional_knapsack_greedy(15.0, items, fractions);
    assert_double_eq(val, 75.0, "Private Knapsack: Tie Breaking Value");
    if (fractions.size() == 2) {
        assert_double_eq(fractions[0], 0.25, "Private Knapsack: Item id=20 Fraction (2nd priority)");
        assert_double_eq(fractions[1], 1.0, "Private Knapsack: Item id=10 Fraction (1st priority)");
    }
}

void test_edge_zero_capacity() {
    std::vector<Item> items = {
        {1, 10.0, 60.0},
        {2, 20.0, 100.0}
    };
    std::vector<double> fractions;
    double val = fractional_knapsack_greedy(0.0, items, fractions);
    assert_double_eq(val, 0.0, "Private Knapsack: Zero Capacity Value");
    if (fractions.size() == 2) {
        assert_double_eq(fractions[0], 0.0, "Private Knapsack: Zero Capacity Fraction 0");
        assert_double_eq(fractions[1], 0.0, "Private Knapsack: Zero Capacity Fraction 1");
    }
}

void test_excess_capacity() {
    std::vector<Item> items = {
        {1, 10.0, 50.0},
        {2, 15.0, 75.0}
    };
    std::vector<double> fractions;
    double val = fractional_knapsack_greedy(100.0, items, fractions);
    assert_double_eq(val, 125.0, "Private Knapsack: Excess Capacity Value");
    if (fractions.size() == 2) {
        assert_double_eq(fractions[0], 1.0, "Private Knapsack: Excess Capacity Item 1");
        assert_double_eq(fractions[1], 1.0, "Private Knapsack: Excess Capacity Item 2");
    }
}

void test_invalid_weight_and_empty() {
    std::vector<Item> items_empty;
    std::vector<double> fractions;
    double val_empty = fractional_knapsack_greedy(50.0, items_empty, fractions);
    assert_double_eq(val_empty, 0.0, "Private Knapsack: Empty Items List");

    std::vector<Item> items_invalid = {
        {1, -5.0, 100.0},
        {2, 0.0, 50.0},
        {3, 10.0, 40.0}
    };
    double val_inv = fractional_knapsack_greedy(10.0, items_invalid, fractions);
    assert_double_eq(val_inv, 40.0, "Private Knapsack: Invalid Weights Skipped Value");
    if (fractions.size() == 3) {
        assert_double_eq(fractions[0], 0.0, "Private Knapsack: Negative Weight Fraction 0");
        assert_double_eq(fractions[1], 0.0, "Private Knapsack: Zero Weight Fraction 1");
        assert_double_eq(fractions[2], 1.0, "Private Knapsack: Valid Item Fraction 1.0");
    }
}

int main() {
    std::cout << "--- Private Test Suite: Fractional Knapsack ---\n";
    test_standard_knapsack();
    test_tie_breaking();
    test_edge_zero_capacity();
    test_excess_capacity();
    test_invalid_weight_and_empty();

    std::cout << "\nPrivate Knapsack Test Summary: " << tests_passed << " PASSED, " << tests_failed << " FAILED.\n";
    return (tests_failed == 0) ? 0 : 1;
}
