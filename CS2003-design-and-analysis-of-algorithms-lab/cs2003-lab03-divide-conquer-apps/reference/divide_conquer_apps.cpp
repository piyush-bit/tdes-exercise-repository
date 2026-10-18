#include "divide_conquer_apps.hpp"
#include <algorithm>
#include <utility>

/**
 * Helper comparison function for ordering trades.
 * Primary key: timestamp (ascending)
 * Secondary key: trade_id (ascending)
 */
static bool is_less_chronological(const Trade& a, const Trade& b) {
    if (a.timestamp != b.timestamp) {
        return a.timestamp < b.timestamp;
    }
    return a.trade_id < b.trade_id;
}

/**
 * Partition helper for Quick Sort.
 */
static int partition_trades(std::vector<Trade>& trades, int low, int high) {
    Trade pivot = trades[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (is_less_chronological(trades[j], pivot)) {
            i++;
            std::swap(trades[i], trades[j]);
        }
    }
    std::swap(trades[i + 1], trades[high]);
    return i + 1;
}

/**
 * Recursive Quick Sort routine.
 */
static void quick_sort_recursive(std::vector<Trade>& trades, int low, int high) {
    if (low < high) {
        int pi = partition_trades(trades, low, high);
        quick_sort_recursive(trades, low, pi - 1);
        quick_sort_recursive(trades, pi + 1, high);
    }
}

void rank_sort_trades(std::vector<Trade>& trades) {
    if (trades.empty()) {
        return;
    }
    quick_sort_recursive(trades, 0, static_cast<int>(trades.size()) - 1);
}

std::vector<Trade> merge_trade_streams(const std::vector<Trade>& streamA, const std::vector<Trade>& streamB) {
    std::vector<Trade> result;
    result.reserve(streamA.size() + streamB.size());

    size_t i = 0;
    size_t j = 0;

    while (i < streamA.size() && j < streamB.size()) {
        if (is_less_chronological(streamA[i], streamB[j])) {
            result.push_back(streamA[i]);
            i++;
        } else {
            result.push_back(streamB[j]);
            j++;
        }
    }

    while (i < streamA.size()) {
        result.push_back(streamA[i]);
        i++;
    }

    while (j < streamB.size()) {
        result.push_back(streamB[j]);
        j++;
    }

    return result;
}

int find_price_threshold(const std::vector<Trade>& sorted_trades, double target_price) {
    if (sorted_trades.empty()) {
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(sorted_trades.size()) - 1;
    int result_index = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sorted_trades[mid].price >= target_price) {
            result_index = mid;
            high = mid - 1; // Try finding an earlier matching index in the left half
        } else {
            low = mid + 1;  // Search in the right half
        }
    }

    return result_index;
}
