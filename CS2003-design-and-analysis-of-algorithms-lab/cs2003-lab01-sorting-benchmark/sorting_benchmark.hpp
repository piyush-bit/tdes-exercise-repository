#ifndef SORTING_BENCHMARK_HPP
#define SORTING_BENCHMARK_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>

/**
 * @brief Represents a high-frequency telemetry log entry in a distributed logging infrastructure.
 */
struct LogEntry {
    int id;
    int priority;
    uint64_t timestamp;
    std::string message;

    /**
     * @brief Compare two LogEntry objects for ascending order sorting.
     * Orders primarily by priority (ascending), secondarily by timestamp (ascending),
     * and tertiarily by id (ascending) to guarantee deterministic total ordering.
     */
    bool operator<(const LogEntry& other) const {
        if (priority != other.priority) {
            return priority < other.priority;
        }
        if (timestamp != other.timestamp) {
            return timestamp < other.timestamp;
        }
        return id < other.id;
    }

    bool operator>(const LogEntry& other) const {
        return other < *this;
    }

    bool operator<=(const LogEntry& other) const {
        return !(*this > other);
    }

    bool operator>=(const LogEntry& other) const {
        return !(*this < other);
    }

    bool operator==(const LogEntry& other) const {
        return id == other.id && priority == other.priority &&
               timestamp == other.timestamp && message == other.message;
    }
};

/**
 * @brief Performance statistics gathered during a sorting algorithm run.
 */
struct SortStats {
    size_t comparisons = 0;
    size_t swaps = 0;
};

/**
 * @brief Sorts a vector of LogEntry objects using Bubble Sort and records performance statistics.
 * @param logs The vector of telemetry logs to sort in-place.
 * @return SortStats metrics containing total comparisons and swaps executed.
 */
SortStats bubble_sort_stats(std::vector<LogEntry>& logs);

/**
 * @brief Sorts a vector of LogEntry objects using Selection Sort and records performance statistics.
 * @param logs The vector of telemetry logs to sort in-place.
 * @return SortStats metrics containing total comparisons and swaps executed.
 */
SortStats selection_sort_stats(std::vector<LogEntry>& logs);

/**
 * @brief Sorts a vector of LogEntry objects using Insertion Sort and records performance statistics.
 * @param logs The vector of telemetry logs to sort in-place.
 * @return SortStats metrics containing total comparisons and swaps executed.
 */
SortStats insertion_sort_stats(std::vector<LogEntry>& logs);

/**
 * @brief Sorts a vector of LogEntry objects using Heap Sort and records performance statistics.
 * @param logs The vector of telemetry logs to sort in-place.
 * @return SortStats metrics containing total comparisons and swaps executed.
 */
SortStats heap_sort_stats(std::vector<LogEntry>& logs);

#endif // SORTING_BENCHMARK_HPP
