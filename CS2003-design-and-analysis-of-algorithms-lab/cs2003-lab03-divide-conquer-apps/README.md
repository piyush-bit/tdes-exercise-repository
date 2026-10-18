# CS2003 Lab 03: Distributed Trade Matching & Price Threshold Finder

## Overview

High-frequency trading platforms and financial exchanges process millions of order executions and trade records per second. Efficient data structures and divide-and-conquer algorithms are essential for sorting streams of executed trades, merging multi-exchange feeds into chronological order, and performing fast price range queries.

In this lab, you will implement three fundamental Divide & Conquer algorithms tailored for financial trade streams:

1. **`rank_sort_trades`**: An in-place **Quick Sort** algorithm to order trade records chronologically.
2. **`merge_trade_streams`**: A 2-way **Merge Sort** merge step to unify two pre-sorted streams of trades from different trading venues.
3. **`find_price_threshold`**: A **Binary Search** algorithm to find the first trade index in a price-sorted dataset meeting or exceeding a target execution price.

---

## Data Structure

The `Trade` structure is declared in `divide_conquer_apps.hpp`:

```cpp
struct Trade {
    uint64_t trade_id;   // Unique trade identifier
    uint64_t timestamp;  // Execution timestamp (milliseconds since epoch)
    double price;        // Execution price per unit
    uint32_t quantity;   // Volume / number of shares traded
    std::string symbol;  // Ticker symbol (e.g., "AAPL", "MSFT")

    bool operator==(const Trade& other) const;
};
```

---

## Tasks & Specifications

### 1. In-Place Quick Sort (`rank_sort_trades`)

```cpp
void rank_sort_trades(std::vector<Trade>& trades);
```

- Sorts the input vector of `Trade` objects **in-place** using the **Quick Sort** algorithm (Divide & Conquer).
- **Sorting Criteria**:
  - Primary key: `timestamp` in ascending order (earlier trades come first).
  - Secondary key (tie-breaker): `trade_id` in ascending order if timestamps are identical.
- **Constraints**:
  - Must handle empty vectors, single-element vectors, and already-sorted vectors gracefully without crashing or out-of-bounds errors.

---

### 2. Stream Merging (`merge_trade_streams`)

```cpp
std::vector<Trade> merge_trade_streams(const std::vector<Trade>& streamA, const std::vector<Trade>& streamB);
```

- Merges two pre-sorted trade streams (`streamA` and `streamB`) into a single chronological stream using **Merge Sort** merge logic.
- Both input streams are guaranteed to be pre-sorted by `timestamp` ascending (and `trade_id` ascending).
- **Return Value**:
  - A `std::vector<Trade>` containing all elements from `streamA` and `streamB` in sorted order.
  - Expected time complexity: $O(N + M)$ where $N$ and $M$ are the sizes of `streamA` and `streamB`.

---

### 3. Binary Search Price Threshold (`find_price_threshold`)

```cpp
int find_price_threshold(const std::vector<Trade>& sorted_trades, double target_price);
```

- Given a vector `sorted_trades` pre-sorted in ascending order of `price`, uses **Binary Search** to find the 0-based index of the **first trade** with `price >= target_price`.
- **Return Value**:
  - Returns the 0-based index of the first trade matching the condition.
  - Returns `-1` if no trade in the list has `price >= target_price`, or if `sorted_trades` is empty.
  - If multiple trades have the exact target price, it must return the **first (lowest index)** occurrence (lower bound).
- Expected time complexity: $O(\log N)$.

---

## Building and Running

You can test your implementation locally using `make` or the provided `./run` script:

```bash
# Run the public test suite locally
make test-public
# or
./run public

# Clean build artifacts
make clean
# or
./run clean
```

---

## Evaluation & Grading

Your submission is graded against private test targets specified in `manifest.json`:

- `test-public`: Public sanity checks (0 points)
- `test-submission-trade-merging`: Tests for Quick Sort and Stream Merging (5 points)
- `test-submission-price-threshold`: Tests for Binary Search Price Threshold (5 points)

Total: **10 points**.
