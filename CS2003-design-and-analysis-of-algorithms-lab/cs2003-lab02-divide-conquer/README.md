# CS2003 Lab 02: High-Throughput Financial Order Book Divide & Conquer

## Problem Overview

In modern high-frequency trading (HFT) platforms and electronic exchanges, maintaining an organized **Limit Order Book (LOB)** is essential for low-latency order matching, price discovery, and execution. Incoming trade orders must be rapidly indexed, sorted according to execution priorities (e.g., price-time priority or order ID indexing), and queried in sub-millisecond time frames.

In this lab, you will implement core **Divide & Conquer** algorithms in C++ to handle high-throughput financial order books:
1. **Quick Sort (`quick_sort_dc`)**: An in-place divide-and-conquer sorting algorithm used for general-purpose order indexing.
2. **Merge Sort (`merge_sort_dc`)**: A stable divide-and-conquer sorting algorithm guaranteed to run in $O(N \log N)$ time, ideal for order books requiring deterministic execution bounds.
3. **Binary Search (`binary_search_dc`)**: A divide-and-conquer search algorithm operating on sorted order books to locate order records by `order_id` in $O(\log N)$ time.

---

## Data Structures

The header file `divide_conquer.hpp` defines the `Order` struct and function prototypes:

```cpp
struct Order {
    uint64_t order_id;
    std::string symbol;
    double price;
    uint32_t quantity;
    bool is_buy; // true for BUY, false for SELL
};
```

You are also provided with a custom order comparator alias:
```cpp
using OrderComparator = std::function<bool(const Order&, const Order&)>;
```

---

## Required Functions to Implement

All functions must be implemented in `divide_conquer.cpp`:

### 1. `quick_sort_dc`
```cpp
void quick_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp = default_order_comparator);
```
- **Description**: Sorts `orders` in-place within index range `[left, right]` using Quick Sort (Divide & Conquer).
- **Behavior**:
  - **Base Case**: If `left >= right`, `left < 0`, or `right >= orders.size()`, return immediately.
  - **Divide**: Choose a pivot element (e.g. middle element `left + (right - left) / 2`) and partition the elements in range `[left, right]` such that elements satisfying `comp(orders[j], pivot)` are placed to the left of the pivot.
  - **Conquer**: Recursively call `quick_sort_dc` on sub-ranges `[left, pivot_idx - 1]` and `[pivot_idx + 1, right]`.
- **Complexity**: Average Time $O(N \log N)$, Space $O(\log N)$ recursion depth.

### 2. `merge_sort_dc`
```cpp
void merge_sort_dc(std::vector<Order>& orders, int left, int right, OrderComparator comp = default_order_comparator);
```
- **Description**: Sorts `orders` in-place within index range `[left, right]` using Merge Sort (Divide & Conquer).
- **Behavior**:
  - **Base Case**: If `left >= right`, `left < 0`, or `right >= orders.size()`, return immediately.
  - **Divide**: Calculate middle index `mid = left + (right - left) / 2`.
  - **Conquer**: Recursively call `merge_sort_dc` on `[left, mid]` and `[mid + 1, right]`.
  - **Combine**: Merge the two sorted halves into a temporary buffer preserving relative order (stable), then copy back into `orders[left..right]`.
- **Complexity**: Time $O(N \log N)$ worst-case, Space $O(N)$ auxiliary space.

### 3. `binary_search_dc`
```cpp
int binary_search_dc(const std::vector<Order>& orders, uint64_t target_id, int left, int right);
```
- **Description**: Searches a sorted `orders` vector for a record with matching `target_id` within `[left, right]` using Divide & Conquer.
- **Behavior**:
  - Assumes `orders` is sorted by `order_id` ascending.
  - **Base Case**: If `left > right`, `left < 0`, `right >= orders.size()`, or vector is empty, return `-1`.
  - **Divide & Inspect**: Calculate `mid = left + (right - left) / 2`.
  - If `orders[mid].order_id == target_id`, return `mid`.
  - If `orders[mid].order_id > target_id`, recurse on `[left, mid - 1]`.
  - Otherwise, recurse on `[mid + 1, right]`.
- **Complexity**: Time $O(\log N)$, Space $O(\log N)$ stack frames.

---

## Local Development & Testing

Run local public unit tests:
```bash
make test-public
# or
./run
```

To clean build binaries:
```bash
make clean
```
