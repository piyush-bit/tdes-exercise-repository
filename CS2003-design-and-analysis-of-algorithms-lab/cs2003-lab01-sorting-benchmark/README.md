# CS2003 Lab 01: Telemetry Log Benchmark & Priority Sorting Engine

## Problem Statement

High-throughput distributed systems generate vast streams of telemetry logs (e.g., performance metrics, security alerts, microservice error events). Before sending log entries to downstream anomaly detectors or prioritized dispatch queues, systems must sort log entries by priority, timestamp, and unique identifier.

In resource-constrained environments (edge nodes, embedded devices, high-frequency logging agents), CPU cycle allocation and memory operations must be carefully budgeted. Measuring wall-clock execution time alone is insufficient due to system noise and CPU frequency scaling. Software engineers rely on **algorithmic benchmarking**—tracking exact **comparisons** and **element swaps**—to evaluate sorting efficiency under different workload distributions (e.g., nearly sorted logs, reverse sorted logs, or random arrivals).

In this lab, you will engineer a **Telemetry Log Sorting & Benchmarking Engine** in C++ implementing four classic sorting algorithms:
1. **Bubble Sort** (`bubble_sort_stats`)
2. **Selection Sort** (`selection_sort_stats`)
3. **Insertion Sort** (`insertion_sort_stats`)
4. **Heap Sort** (`heap_sort_stats`)

Each function must sort a `std::vector<LogEntry>` **in-place in ascending order** and return a `SortStats` struct recording the exact number of key comparisons and element swaps performed during execution.

---

## Data Structures & Contract

Defined in [`sorting_benchmark.hpp`](sorting_benchmark.hpp):

```cpp
struct LogEntry {
    int id;
    int priority;
    uint64_t timestamp;
    std::string message;

    bool operator<(const LogEntry& other) const;
    bool operator>(const LogEntry& other) const;
    bool operator<=(const LogEntry& other) const;
    bool operator>=(const LogEntry& other) const;
    bool operator==(const LogEntry& other) const;
};

struct SortStats {
    size_t comparisons = 0;
    size_t swaps = 0;
};
```

### Ordering Contract
Logs are ordered in ascending order:
1. **Primary Key**: `priority` (lower values come first).
2. **Secondary Key**: `timestamp` (earlier timestamps come first).
3. **Tertiary Key**: `id` (lower IDs come first).

Using the overloaded relational operators (`<`, `>`, etc.) on `LogEntry` automatically enforces this ordering rule.

---

## Algorithm Specifications & Operation Counting Rules

### 1. Optimized Bubble Sort (`bubble_sort_stats`)
- **Logic**: Repeatedly pass through the array, comparing adjacent elements. Swap adjacent elements if `logs[j + 1] < logs[j]`. If no swaps occur during an entire pass, terminate early.
- **Comparisons**: Increment `stats.comparisons` for every adjacent pair comparison (`logs[j + 1] < logs[j]`).
- **Swaps**: Increment `stats.swaps` for every `std::swap(logs[j], logs[j + 1])`.
- **Complexity**:
  - Time: Best $\mathcal{O}(n)$, Average $\mathcal{O}(n^2)$, Worst $\mathcal{O}(n^2)$
  - Space: $\mathcal{O}(1)$ auxiliary

### 2. Selection Sort (`selection_sort_stats`)
- **Logic**: For each position `i` from `0` to `n - 2`, find the minimum element in subarray `[i ... n - 1]`. If the minimum element index `min_idx != i`, swap `logs[i]` with `logs[min_idx]`.
- **Comparisons**: Increment `stats.comparisons` for every comparison `logs[j] < logs[min_idx]` in the inner loop.
- **Swaps**: Increment `stats.swaps` when `min_idx != i` and `std::swap(logs[i], logs[min_idx])` is called.
- **Complexity**:
  - Time: Best $\mathcal{O}(n^2)$, Average $\mathcal{O}(n^2)$, Worst $\mathcal{O}(n^2)$
  - Space: $\mathcal{O}(1)$ auxiliary

### 3. Insertion Sort (`insertion_sort_stats`)
- **Logic**: For each index `i` from `1` to `n - 1`, insert element `logs[i]` into its proper position in the sorted prefix `[0 ... i - 1]` by swapping adjacent elements leftward while `logs[j] < logs[j - 1]`.
- **Comparisons**: Increment `stats.comparisons` for every element comparison `logs[j] < logs[j - 1]` (including the comparison that fails and terminates the inner loop).
- **Swaps**: Increment `stats.swaps` for every adjacent `std::swap(logs[j], logs[j - 1])`.
- **Complexity**:
  - Time: Best $\mathcal{O}(n)$, Average $\mathcal{O}(n^2)$, Worst $\mathcal{O}(n^2)$
  - Space: $\mathcal{O}(1)$ auxiliary

### 4. Heap Sort (`heap_sort_stats`)
- **Logic**:
  1. Build a max-heap in-place from the bottom up starting at index $\lfloor n / 2 \rfloor - 1$ down to `0` using a max-heapify helper function.
  2. Repeatedly extract the maximum element (root at index `0`) by swapping it with index `i` (for `i` from `n - 1` down to `1`), then call heapify on the reduced heap of size `i`.
- **Comparisons**: In `heapify(logs, n, i, stats)`:
  - If left child exists (`left < n`), increment `stats.comparisons` and check if `logs[left] > logs[largest]`.
  - If right child exists (`right < n`), increment `stats.comparisons` and check if `logs[right] > logs[largest]`.
- **Swaps**: Increment `stats.swaps` whenever root is swapped with a child in `heapify`, and when max root is swapped to index `i` during extraction.
- **Complexity**:
  - Time: Best $\mathcal{O}(n \log n)$, Average $\mathcal{O}(n \log n)$, Worst $\mathcal{O}(n \log n)$
  - Space: $\mathcal{O}(1)$ auxiliary

---

## Instructions & Tasks

1. Implement all four sorting functions in `sorting_benchmark.cpp`.
2. Do not modify `sorting_benchmark.hpp`.
3. Test your implementation locally:
   ```bash
   make test-public
   # or
   ./run public
   ```
4. Verify edge cases: empty vectors (`n = 0`), single-element vectors (`n = 1`), pre-sorted vectors, and reverse-sorted vectors.

---

## Makefile Targets

- `make test-public`: Compiles and runs public unit tests against `sorting_benchmark.cpp`.
- `make clean`: Removes binary build artifacts.
