#include "divide_conquer_apps.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

static int failed_tests = 0;

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "  [FAIL] " << msg << " (line " << __LINE__ << ")" << std::endl; \
            failed_tests++; \
        } \
    } while(0)

static bool is_sorted_chronological(const std::vector<Trade>& trades) {
    for (size_t i = 1; i < trades.size(); ++i) {
        if (trades[i - 1].timestamp > trades[i].timestamp) {
            return false;
        }
        if (trades[i - 1].timestamp == trades[i].timestamp && trades[i - 1].trade_id > trades[i].trade_id) {
            return false;
        }
    }
    return true;
}

void test_rank_sort_edge_cases() {
    // Empty vector
    std::vector<Trade> empty_trades;
    rank_sort_trades(empty_trades);
    TEST_ASSERT(empty_trades.empty(), "Quick Sort handles empty vector");

    // Single element
    std::vector<Trade> single = {{1, 100, 50.0, 10, "NVDA"}};
    rank_sort_trades(single);
    TEST_ASSERT(single.size() == 1 && single[0].trade_id == 1, "Quick Sort handles single element vector");

    // Already sorted
    std::vector<Trade> sorted = {
        {1, 100, 10.0, 5, "NVDA"},
        {2, 200, 20.0, 5, "NVDA"},
        {3, 300, 30.0, 5, "NVDA"}
    };
    rank_sort_trades(sorted);
    TEST_ASSERT(is_sorted_chronological(sorted), "Quick Sort handles already sorted vector");

    // Reverse sorted
    std::vector<Trade> rev_sorted = {
        {3, 300, 30.0, 5, "NVDA"},
        {2, 200, 20.0, 5, "NVDA"},
        {1, 100, 10.0, 5, "NVDA"}
    };
    rank_sort_trades(rev_sorted);
    TEST_ASSERT(is_sorted_chronological(rev_sorted) && rev_sorted[0].trade_id == 1, "Quick Sort handles reverse sorted vector");
}

void test_rank_sort_tie_breaker() {
    std::vector<Trade> trades = {
        {50, 1000, 10.0, 100, "AMZN"},
        {10, 1000, 10.0, 100, "AMZN"},
        {30, 1000, 10.0, 100, "AMZN"},
        {20, 1000, 10.0, 100, "AMZN"}
    };

    rank_sort_trades(trades);
    TEST_ASSERT(is_sorted_chronological(trades), "Quick Sort correctly uses trade_id for tie breaking");
    TEST_ASSERT(trades[0].trade_id == 10 && trades[1].trade_id == 20 && trades[2].trade_id == 30 && trades[3].trade_id == 50, "Tie breaker order strictly ascending");
}

void test_merge_streams_edge_cases() {
    std::vector<Trade> empty;
    std::vector<Trade> stream = {{1, 100, 10.0, 5, "TSLA"}};

    std::vector<Trade> m1 = merge_trade_streams(empty, empty);
    TEST_ASSERT(m1.empty(), "Merge handles two empty streams");

    std::vector<Trade> m2 = merge_trade_streams(empty, stream);
    TEST_ASSERT(m2.size() == 1 && m2[0].trade_id == 1, "Merge handles empty streamA");

    std::vector<Trade> m3 = merge_trade_streams(stream, empty);
    TEST_ASSERT(m3.size() == 1 && m3[0].trade_id == 1, "Merge handles empty streamB");
}

void test_merge_streams_interleaved() {
    std::vector<Trade> streamA = {
        {1, 10, 100.0, 10, "META"},
        {3, 30, 102.0, 10, "META"},
        {5, 50, 104.0, 10, "META"}
    };

    std::vector<Trade> streamB = {
        {2, 20, 101.0, 10, "META"},
        {4, 40, 103.0, 10, "META"},
        {6, 60, 105.0, 10, "META"}
    };

    std::vector<Trade> merged = merge_trade_streams(streamA, streamB);
    TEST_ASSERT(merged.size() == 6, "Merged size equals streamA.size() + streamB.size()");
    TEST_ASSERT(is_sorted_chronological(merged), "Merged stream is strictly chronological");
    for (size_t i = 0; i < 6; ++i) {
        TEST_ASSERT(merged[i].trade_id == i + 1, "Interleaved merge order verified");
    }
}

int main() {
    std::cout << "Running Private Test Suite: Trade Merging..." << std::endl;
    test_rank_sort_edge_cases();
    test_rank_sort_tie_breaker();
    test_merge_streams_edge_cases();
    test_merge_streams_interleaved();

    if (failed_tests == 0) {
        std::cout << "TEST SUBMISSION TRADE MERGING PASSED!" << std::endl;
        return 0;
    } else {
        std::cerr << failed_tests << " TEST(S) FAILED IN TRADE MERGING!" << std::endl;
        return 1;
    }
}
