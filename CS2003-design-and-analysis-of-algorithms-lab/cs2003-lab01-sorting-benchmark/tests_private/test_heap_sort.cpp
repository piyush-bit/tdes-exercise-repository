#include "sorting_benchmark.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>
#include <cmath>

static LogEntry make_entry(int id, int priority, uint64_t timestamp, const std::string& msg = "log") {
    return LogEntry{id, priority, timestamp, msg};
}

static void test_heap_sort_edge_cases() {
    std::cout << "[PRIVATE] Testing Heap Sort edge cases..." << std::endl;
    std::vector<LogEntry> empty_vec;
    SortStats stats = heap_sort_stats(empty_vec);
    assert(stats.comparisons == 0 && stats.swaps == 0);

    std::vector<LogEntry> single_vec = { make_entry(1, 10, 100) };
    stats = heap_sort_stats(single_vec);
    assert(stats.comparisons == 0 && stats.swaps == 0);

    std::cout << "  -> Heap Sort edge cases passed!" << std::endl;
}

static void test_heap_sort_correctness() {
    std::cout << "[PRIVATE] Testing Heap Sort correctness & tie-breaking..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(1, 50, 200, "Fatal"),
        make_entry(2, 20, 100, "Debug"),
        make_entry(3, 20, 100, "Info"),
        make_entry(4, 10, 500, "Trace"),
        make_entry(5, 50, 100, "Critical")
    };

    std::vector<LogEntry> expected = logs;
    std::sort(expected.begin(), expected.end());

    SortStats stats = heap_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(logs == expected);
    assert(stats.comparisons > 0);
    assert(stats.swaps > 0);

    std::cout << "  -> Heap Sort correctness & tie-breaking passed!" << std::endl;
}

static void test_heap_sort_nlogn_complexity() {
    std::cout << "[PRIVATE] Testing Heap Sort O(N log N) comparison upper bound..." << std::endl;
    const size_t N = 500;
    std::vector<LogEntry> logs;
    logs.reserve(N);

    std::mt19937 rng(42); // fixed seed for reproducibility
    std::uniform_int_distribution<int> prio_dist(1, 1000);
    std::uniform_int_distribution<uint64_t> ts_dist(100000, 999999);

    for (size_t i = 0; i < N; ++i) {
        logs.push_back(make_entry(static_cast<int>(i), prio_dist(rng), ts_dist(rng), "telemetry"));
    }

    std::vector<LogEntry> std_sorted = logs;
    std::sort(std_sorted.begin(), std_sorted.end());

    SortStats stats = heap_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(logs == std_sorted);

    size_t upper_bound = static_cast<size_t>(4.0 * N * std::log2(N));
    assert(stats.comparisons <= upper_bound);
    assert(stats.comparisons > N);

    std::cout << "  -> Heap Sort O(N log N) bound passed! (Comps: " << stats.comparisons << " <= " << upper_bound << ")" << std::endl;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  Private Grading Suite: Heap Sort" << std::endl;
    std::cout << "==========================================" << std::endl;

    test_heap_sort_edge_cases();
    test_heap_sort_correctness();
    test_heap_sort_nlogn_complexity();

    std::cout << "All Heap Sort private tests passed! (5/5 pts)" << std::endl;
    return 0;
}
