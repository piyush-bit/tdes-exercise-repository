#include "divide_conquer_apps.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

static int failed_tests = 0;

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "  [FAIL] " << msg << " (line " << __LINE__ << ")" << std::endl; \
            failed_tests++; \
        } else { \
            std::cout << "  [PASS] " << msg << std::endl; \
        } \
    } while(0)

void test_public_rank_sort() {
    std::cout << "Running Public Test: rank_sort_trades..." << std::endl;

    std::vector<Trade> trades = {
        {103, 1600000002, 150.50, 100, "AAPL"},
        {101, 1600000000, 149.00, 50,  "AAPL"},
        {102, 1600000000, 149.50, 75,  "AAPL"},
        {104, 1600000005, 151.00, 200, "AAPL"}
    };

    rank_sort_trades(trades);

    TEST_ASSERT(trades.size() == 4, "Vector size preserved after sorting");
    TEST_ASSERT(trades[0].trade_id == 101 && trades[0].timestamp == 1600000000, "Trade 101 sorted first");
    TEST_ASSERT(trades[1].trade_id == 102 && trades[1].timestamp == 1600000000, "Trade 102 sorted second (tie-breaker)");
    TEST_ASSERT(trades[2].trade_id == 103 && trades[2].timestamp == 1600000002, "Trade 103 sorted third");
    TEST_ASSERT(trades[3].trade_id == 104 && trades[3].timestamp == 1600000005, "Trade 104 sorted fourth");
}

void test_public_merge_streams() {
    std::cout << "Running Public Test: merge_trade_streams..." << std::endl;

    std::vector<Trade> streamA = {
        {201, 1000, 50.0, 10, "MSFT"},
        {203, 3000, 52.0, 30, "MSFT"}
    };

    std::vector<Trade> streamB = {
        {202, 2000, 51.0, 20, "MSFT"},
        {204, 4000, 53.0, 40, "MSFT"}
    };

    std::vector<Trade> merged = merge_trade_streams(streamA, streamB);

    TEST_ASSERT(merged.size() == 4, "Merged vector has correct total size");
    TEST_ASSERT(merged[0].trade_id == 201 && merged[0].timestamp == 1000, "Merged index 0 correct");
    TEST_ASSERT(merged[1].trade_id == 202 && merged[1].timestamp == 2000, "Merged index 1 correct");
    TEST_ASSERT(merged[2].trade_id == 203 && merged[2].timestamp == 3000, "Merged index 2 correct");
    TEST_ASSERT(merged[3].trade_id == 204 && merged[3].timestamp == 4000, "Merged index 3 correct");
}

void test_public_price_threshold() {
    std::cout << "Running Public Test: find_price_threshold..." << std::endl;

    std::vector<Trade> sorted_trades = {
        {1, 100, 10.0, 100, "GOOGL"},
        {2, 101, 20.0, 100, "GOOGL"},
        {3, 102, 30.0, 100, "GOOGL"},
        {4, 103, 40.0, 100, "GOOGL"},
        {5, 104, 50.0, 100, "GOOGL"}
    };

    int idx1 = find_price_threshold(sorted_trades, 25.0);
    TEST_ASSERT(idx1 == 2, "Threshold search for 25.0 returns index 2 (price 30.0)");

    int idx2 = find_price_threshold(sorted_trades, 10.0);
    TEST_ASSERT(idx2 == 0, "Threshold search for exact min price 10.0 returns index 0");

    int idx3 = find_price_threshold(sorted_trades, 60.0);
    TEST_ASSERT(idx3 == -1, "Threshold search above max price returns -1");
}

int main() {
    std::cout << "=== CS2003 Lab 03 Public Tests ===" << std::endl;
    test_public_rank_sort();
    test_public_merge_streams();
    test_public_price_threshold();

    if (failed_tests == 0) {
        std::cout << "ALL PUBLIC TESTS PASSED!" << std::endl;
        return 0;
    } else {
        std::cerr << failed_tests << " PUBLIC TEST(S) FAILED!" << std::endl;
        return 1;
    }
}
