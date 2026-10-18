#include "sorting_benchmark.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

static LogEntry make_entry(int id, int priority, uint64_t timestamp, const std::string& msg) {
    return LogEntry{id, priority, timestamp, msg};
}

static void test_bubble_sort() {
    std::cout << "[TEST] Running public test for Bubble Sort..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(1, 30, 1000, "Warn"),
        make_entry(2, 10, 1001, "Debug"),
        make_entry(3, 50, 999,  "Fatal"),
        make_entry(4, 20, 1002, "Info"),
        make_entry(5, 10, 950,  "Trace")
    };

    SortStats stats = bubble_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(logs[0].id == 5); // priority 10, timestamp 950
    assert(logs[1].id == 2); // priority 10, timestamp 1001
    assert(logs[2].id == 4); // priority 20
    assert(logs[3].id == 1); // priority 30
    assert(logs[4].id == 3); // priority 50

    assert(stats.comparisons > 0);
    assert(stats.swaps > 0);

    // Test on already sorted vector (Optimized Bubble Sort early stop)
    SortStats sorted_stats = bubble_sort_stats(logs);
    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(sorted_stats.swaps == 0);
    assert(sorted_stats.comparisons == logs.size() - 1);

    std::cout << "  -> Bubble Sort Passed! (Comps: " << stats.comparisons << ", Swaps: " << stats.swaps << ")" << std::endl;
}

static void test_selection_sort() {
    std::cout << "[TEST] Running public test for Selection Sort..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(1, 40, 500, "Error"),
        make_entry(2, 10, 200, "Debug"),
        make_entry(3, 30, 100, "Info"),
        make_entry(4, 20, 400, "Notice")
    };

    SortStats stats = selection_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(stats.comparisons == 6); // n*(n-1)/2 = 4*3/2 = 6
    assert(stats.swaps > 0);

    std::cout << "  -> Selection Sort Passed! (Comps: " << stats.comparisons << ", Swaps: " << stats.swaps << ")" << std::endl;
}

static void test_insertion_sort() {
    std::cout << "[TEST] Running public test for Insertion Sort..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(10, 5,  100, "Low"),
        make_entry(20, 1,  200, "Lowest"),
        make_entry(30, 20, 300, "High"),
        make_entry(40, 15, 400, "Medium")
    };

    SortStats stats = insertion_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(stats.comparisons > 0);
    assert(stats.swaps > 0);

    std::cout << "  -> Insertion Sort Passed! (Comps: " << stats.comparisons << ", Swaps: " << stats.swaps << ")" << std::endl;
}

static void test_heap_sort() {
    std::cout << "[TEST] Running public test for Heap Sort..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(1, 100, 50, "Critical"),
        make_entry(2, 20,  10, "Info"),
        make_entry(3, 80,  20, "Warn"),
        make_entry(4, 10,  30, "Trace"),
        make_entry(5, 50,  40, "Notice")
    };

    SortStats stats = heap_sort_stats(logs);

    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(stats.comparisons > 0);
    assert(stats.swaps > 0);

    std::cout << "  -> Heap Sort Passed! (Comps: " << stats.comparisons << ", Swaps: " << stats.swaps << ")" << std::endl;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  CS2003 Lab 01: Public Test Suite" << std::endl;
    std::cout << "==========================================" << std::endl;

    test_bubble_sort();
    test_selection_sort();
    test_insertion_sort();
    test_heap_sort();

    std::cout << "All public tests passed successfully!" << std::endl;
    return 0;
}
