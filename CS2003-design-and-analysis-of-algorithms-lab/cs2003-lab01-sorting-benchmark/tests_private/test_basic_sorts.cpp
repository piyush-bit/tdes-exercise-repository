#include "sorting_benchmark.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

static LogEntry make_entry(int id, int priority, uint64_t timestamp, const std::string& msg = "log") {
    return LogEntry{id, priority, timestamp, msg};
}

static void test_empty_and_single() {
    std::cout << "[PRIVATE] Testing empty & single element vectors..." << std::endl;
    std::vector<LogEntry> empty_vec;
    
    SortStats bs = bubble_sort_stats(empty_vec);
    assert(bs.comparisons == 0 && bs.swaps == 0);

    SortStats ss = selection_sort_stats(empty_vec);
    assert(ss.comparisons == 0 && ss.swaps == 0);

    SortStats is = insertion_sort_stats(empty_vec);
    assert(is.comparisons == 0 && is.swaps == 0);

    std::vector<LogEntry> single_vec = { make_entry(1, 10, 1000) };
    bs = bubble_sort_stats(single_vec);
    assert(bs.comparisons == 0 && bs.swaps == 0);

    ss = selection_sort_stats(single_vec);
    assert(ss.comparisons == 0 && ss.swaps == 0);

    is = insertion_sort_stats(single_vec);
    assert(is.comparisons == 0 && is.swaps == 0);

    std::cout << "  -> Empty and single element tests passed!" << std::endl;
}

static void test_bubble_sort_deep() {
    std::cout << "[PRIVATE] Testing Bubble Sort deep analysis..." << std::endl;
    // Reverse sorted vector
    std::vector<LogEntry> logs = {
        make_entry(4, 40, 400),
        make_entry(3, 30, 300),
        make_entry(2, 20, 200),
        make_entry(1, 10, 100)
    };

    SortStats stats = bubble_sort_stats(logs);
    assert(std::is_sorted(logs.begin(), logs.end()));
    // For n=4 reverse sorted: comparisons = 3 + 2 + 1 = 6, swaps = 6
    assert(stats.comparisons == 6);
    assert(stats.swaps == 6);

    // Sorted vector
    SortStats sorted_stats = bubble_sort_stats(logs);
    assert(sorted_stats.comparisons == 3);
    assert(sorted_stats.swaps == 0);

    std::cout << "  -> Bubble Sort deep test passed!" << std::endl;
}

static void test_selection_sort_deep() {
    std::cout << "[PRIVATE] Testing Selection Sort deep analysis..." << std::endl;
    std::vector<LogEntry> logs = {
        make_entry(4, 40, 400),
        make_entry(1, 10, 100),
        make_entry(3, 30, 300),
        make_entry(2, 20, 200)
    };

    SortStats stats = selection_sort_stats(logs);
    assert(std::is_sorted(logs.begin(), logs.end()));
    // For n=4: comparisons = 3 + 2 + 1 = 6
    assert(stats.comparisons == 6);
    assert(stats.swaps > 0);

    std::cout << "  -> Selection Sort deep test passed!" << std::endl;
}

static void test_insertion_sort_deep() {
    std::cout << "[PRIVATE] Testing Insertion Sort deep analysis..." << std::endl;
    // Reverse sorted: n=4 -> comparisons = 1 + 2 + 3 = 6, swaps = 6
    std::vector<LogEntry> logs = {
        make_entry(4, 40, 400),
        make_entry(3, 30, 300),
        make_entry(2, 20, 200),
        make_entry(1, 10, 100)
    };

    SortStats stats = insertion_sort_stats(logs);
    assert(std::is_sorted(logs.begin(), logs.end()));
    assert(stats.comparisons == 6);
    assert(stats.swaps == 6);

    // Sorted vector: n=4 -> comparisons = 3, swaps = 0
    SortStats sorted_stats = insertion_sort_stats(logs);
    assert(sorted_stats.comparisons == 3);
    assert(sorted_stats.swaps == 0);

    std::cout << "  -> Insertion Sort deep test passed!" << std::endl;
}

static void test_duplicate_keys_and_large() {
    std::cout << "[PRIVATE] Testing duplicate keys and random dataset..." << std::endl;
    std::vector<LogEntry> logs;
    for (int i = 0; i < 50; ++i) {
        logs.push_back(make_entry(i, 10 + (i % 5), 1000 + (i % 3)));
    }

    std::vector<LogEntry> logs1 = logs;
    std::vector<LogEntry> logs2 = logs;
    std::vector<LogEntry> logs3 = logs;

    bubble_sort_stats(logs1);
    selection_sort_stats(logs2);
    insertion_sort_stats(logs3);

    assert(std::is_sorted(logs1.begin(), logs1.end()));
    assert(std::is_sorted(logs2.begin(), logs2.end()));
    assert(std::is_sorted(logs3.begin(), logs3.end()));

    // Verify all end up identical
    for (size_t i = 0; i < logs.size(); ++i) {
        assert(logs1[i] == logs2[i]);
        assert(logs2[i] == logs3[i]);
    }

    std::cout << "  -> Duplicate keys and dataset consistency test passed!" << std::endl;
}

int main() {
    std::cout << "==========================================" << std::endl;
    std::cout << "  Private Grading Suite: Basic Sorts" << std::endl;
    std::cout << "==========================================" << std::endl;

    test_empty_and_single();
    test_bubble_sort_deep();
    test_selection_sort_deep();
    test_insertion_sort_deep();
    test_duplicate_keys_and_large();

    std::cout << "All Basic Sorts private tests passed! (5/5 pts)" << std::endl;
    return 0;
}
