# CS2001 Lab 08: Sorting Algorithms (Bubble, Selection, Insertion, Heap Sort) in C

## Problem Overview

**Sorting** is the algorithmic process of arranging elements of a collection into a specific order (typically ascending or descending). In this lab, you will implement four classic comparison-based sorting algorithms in C:

1. **Bubble Sort**: A simple comparison sort that repeatedly steps through the list, compares adjacent elements, and swaps them if they are out of order.
   - *Time Complexity*: \(O(N^2)\) worst/average case, \(O(N)\) best case with swap checking.
   - *Space Complexity*: \(O(1)\) auxiliary.

2. **Selection Sort**: An in-place comparison sort that divides the array into a sorted and an unsorted region. It repeatedly selects the minimum element from the unsorted region and swaps it into the sorted region.
   - *Time Complexity*: \(O(N^2)\) all cases.
   - *Space Complexity*: \(O(1)\) auxiliary.

3. **Insertion Sort**: An in-place comparison sort that builds the sorted array one element at a time by picking the next element and inserting it into its correct position among previously sorted elements.
   - *Time Complexity*: \(O(N^2)\) worst/average case, \(O(N)\) best case.
   - *Space Complexity*: \(O(1)\) auxiliary.

4. **Heap Sort**: A comparison-based sorting algorithm based on a Binary Heap data structure. It first constructs a Max-Heap from the array, then repeatedly swaps the root (maximum element) with the last element of the heap and restores the heap property.
   - *Time Complexity*: \(O(N \log N)\) best/average/worst case.
   - *Space Complexity*: \(O(1)\) auxiliary (iterative or log-N call stack).

---

## File Structure

- `sorting.h` — Header file with function declarations and API specifications (Do not modify).
- `sorting.c` — **Your primary working file.** Complete all `// TODO:` stubs here.
- `public_test.c` — Public unit test suite for local testing.
- `Makefile` — Build automation script containing test and grading targets.
- `run` — Convenience wrapper script (`./run`).

---

## API Specifications

All functions operate on an array of integers `arr[]` of size `n` and sort the array in **ascending order** in-place.

### 1. `void bubble_sort(int arr[], int n)`
Sorts `arr` in ascending order using the Bubble Sort algorithm.
- **Preconditions / Edge Cases**:
  - If `arr == NULL` or `n <= 1`, do nothing and return immediately.
- **Behavior**:
  - Compare adjacent elements `arr[j]` and `arr[j+1]`.
  - Swap if `arr[j] > arr[j+1]`.
  - Early termination if no swaps occur during a full pass.

---

### 2. `void selection_sort(int arr[], int n)`
Sorts `arr` in ascending order using the Selection Sort algorithm.
- **Preconditions / Edge Cases**:
  - If `arr == NULL` or `n <= 1`, do nothing and return immediately.
- **Behavior**:
  - Find the index of the minimum element in `arr[i...n-1]`.
  - Swap `arr[i]` with `arr[min_idx]` if `min_idx != i`.

---

### 3. `void insertion_sort(int arr[], int n)`
Sorts `arr` in ascending order using the Insertion Sort algorithm.
- **Preconditions / Edge Cases**:
  - If `arr == NULL` or `n <= 1`, do nothing and return immediately.
- **Behavior**:
  - Iterate from index `1` to `n-1`.
  - Insert element `arr[i]` into its appropriate position in sorted subarray `arr[0...i-1]` by shifting larger elements to the right.

---

### 4. `void heap_sort(int arr[], int n)`
Sorts `arr` in ascending order using the Heap Sort algorithm.
- **Preconditions / Edge Cases**:
  - If `arr == NULL` or `n <= 1`, do nothing and return immediately.
- **Behavior**:
  - Build a Max-Heap from `arr` (starting heapification from index `n/2 - 1` down to `0`).
  - Extract the max element from heap by swapping `arr[0]` with `arr[i]` (where `i` goes from `n-1` down to `1`), then call heapify on reduced heap of size `i`.

---

## How to Test Locally

Run the public test suite using Make or the `run` script:

```bash
make test-public
# OR
./run
```

To clean up compiled binaries:
```bash
make clean
# OR
./run clean
```

---

## Grading Criteria

| Target | Points | Type | Description |
| :--- | :---: | :---: | :--- |
| `make test-public` | 0 | Public | Local verification of student solution against basic test cases |
| `make test-submission-basic-sorts` | 5 | Private | Comprehensive validation of `bubble_sort`, `selection_sort`, and `insertion_sort` |
| `make test-submission-heap-sort` | 5 | Private | Comprehensive validation of `heap_sort` (edge cases, duplicates, large arrays) |
| **Total** | **10** | | |
