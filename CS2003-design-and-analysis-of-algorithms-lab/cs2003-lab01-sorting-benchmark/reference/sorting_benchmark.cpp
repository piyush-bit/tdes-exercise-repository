#include "sorting_benchmark.hpp"
#include <algorithm>

SortStats bubble_sort_stats(std::vector<LogEntry>& logs) {
    SortStats stats;
    size_t n = logs.size();
    if (n <= 1) return stats;

    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            stats.comparisons++;
            if (logs[j + 1] < logs[j]) {
                std::swap(logs[j], logs[j + 1]);
                stats.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return stats;
}

SortStats selection_sort_stats(std::vector<LogEntry>& logs) {
    SortStats stats;
    size_t n = logs.size();
    if (n <= 1) return stats;

    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            stats.comparisons++;
            if (logs[j] < logs[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(logs[i], logs[min_idx]);
            stats.swaps++;
        }
    }
    return stats;
}

SortStats insertion_sort_stats(std::vector<LogEntry>& logs) {
    SortStats stats;
    size_t n = logs.size();
    if (n <= 1) return stats;

    for (size_t i = 1; i < n; ++i) {
        size_t j = i;
        while (j > 0) {
            stats.comparisons++;
            if (logs[j] < logs[j - 1]) {
                std::swap(logs[j], logs[j - 1]);
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }
    }
    return stats;
}

static void heapify(std::vector<LogEntry>& logs, size_t n, size_t i, SortStats& stats) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n) {
        stats.comparisons++;
        if (logs[largest] < logs[left]) {
            largest = left;
        }
    }

    if (right < n) {
        stats.comparisons++;
        if (logs[largest] < logs[right]) {
            largest = right;
        }
    }

    if (largest != i) {
        std::swap(logs[i], logs[largest]);
        stats.swaps++;
        heapify(logs, n, largest, stats);
    }
}

SortStats heap_sort_stats(std::vector<LogEntry>& logs) {
    SortStats stats;
    size_t n = logs.size();
    if (n <= 1) return stats;

    for (int i = (int)n / 2 - 1; i >= 0; --i) {
        heapify(logs, n, static_cast<size_t>(i), stats);
    }

    for (size_t i = n - 1; i > 0; --i) {
        std::swap(logs[0], logs[i]);
        stats.swaps++;
        heapify(logs, i, 0, stats);
    }

    return stats;
}
