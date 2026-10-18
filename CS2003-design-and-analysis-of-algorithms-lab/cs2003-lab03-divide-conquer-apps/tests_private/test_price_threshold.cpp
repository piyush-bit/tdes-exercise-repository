#include "divide_conquer_apps.hpp"
#include <iostream>
#include <vector>
#include <cassert>

static int failed_tests = 0;

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "  [FAIL] " << msg << " (line " << __LINE__ << ")" << std::endl; \
            failed_tests++; \
        } \
    } while(0)

void test_price_threshold_empty_and_single() {
    std::vector<Trade> empty;
    TEST_ASSERT(find_price_threshold(empty, 10.0) == -1, "Empty vector returns -1");

    std::vector<Trade> single = {{1, 100, 50.0, 10, "AAPL"}};
    TEST_ASSERT(find_price_threshold(single, 40.0) == 0, "Single element target below price returns 0");
    TEST_ASSERT(find_price_threshold(single, 50.0) == 0, "Single element target equal to price returns 0");
    TEST_ASSERT(find_price_threshold(single, 60.0) == -1, "Single element target above price returns -1");
}

void test_price_threshold_duplicates() {
    // Array with duplicate prices
    std::vector<Trade> sorted_trades = {
        {1, 100, 10.0, 10, "AAPL"},
        {2, 101, 20.0, 10, "AAPL"},
        {3, 102, 20.0, 10, "AAPL"},
        {4, 103, 20.0, 10, "AAPL"},
        {5, 104, 30.0, 10, "AAPL"}
    };

    // Target 20.0 must return index 1 (the first trade with price >= 20.0)
    int idx = find_price_threshold(sorted_trades, 20.0);
    TEST_ASSERT(idx == 1, "Duplicate target price returns the FIRST index meeting threshold (index 1)");

    int idx_between = find_price_threshold(sorted_trades, 15.0);
    TEST_ASSERT(idx_between == 1, "Target 15.0 returns index 1 (first trade with price >= 15.0)");
}

void test_price_threshold_boundaries() {
    std::vector<Trade> sorted_trades = {
        {1, 100, 100.10, 10, "SPY"},
        {2, 101, 100.25, 10, "SPY"},
        {3, 102, 100.50, 10, "SPY"},
        {4, 103, 100.75, 10, "SPY"},
        {5, 104, 101.00, 10, "SPY"}
    };

    TEST_ASSERT(find_price_threshold(sorted_trades, 50.0) == 0, "Target below min returns 0");
    TEST_ASSERT(find_price_threshold(sorted_trades, 200.0) == -1, "Target above max returns -1");
    TEST_ASSERT(find_price_threshold(sorted_trades, 100.50) == 2, "Exact match for middle element returns correct index");
    TEST_ASSERT(find_price_threshold(sorted_trades, 100.60) == 3, "In-between target returns next index meeting threshold");
}

void test_price_threshold_large() {
    std::vector<Trade> large;
    for (int i = 0; i < 1000; ++i) {
        large.push_back({static_cast<uint64_t>(i + 1), 1000, static_cast<double>(i * 2), 10, "QQQ"});
    }

    TEST_ASSERT(find_price_threshold(large, 0.0) == 0, "Large dataset first element threshold");
    TEST_ASSERT(find_price_threshold(large, 500.0) == 250, "Large dataset midpoint threshold");
    TEST_ASSERT(find_price_threshold(large, 1998.0) == 999, "Large dataset last element threshold");
    TEST_ASSERT(find_price_threshold(large, 2000.0) == -1, "Large dataset above max threshold");
}

int main() {
    std::cout << "Running Private Test Suite: Price Threshold..." << std::endl;
    test_price_threshold_empty_and_single();
    test_price_threshold_duplicates();
    test_price_threshold_boundaries();
    test_price_threshold_large();

    if (failed_tests == 0) {
        std::cout << "TEST SUBMISSION PRICE THRESHOLD PASSED!" << std::endl;
        return 0;
    } else {
        std::cerr << failed_tests << " TEST(S) FAILED IN PRICE THRESHOLD!" << std::endl;
        return 1;
    }
}
