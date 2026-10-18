# CS2001 Lab 09: Advanced Sorts (Quick, Merge) & Searches (Sequential, Binary)

Welcome to Lab 09! In this lab, you will implement advanced sorting algorithms (**Quick Sort** and **Merge Sort**) and essential searching algorithms (**Sequential Search** and **Binary Search**) in C.

---

## Objectives

- Understand and implement divide-and-conquer sorting algorithms: **Quick Sort** and **Merge Sort**.
- Implement linear search (**Sequential Search**) for unsorted or sorted arrays.
- Implement **Binary Search** for efficiently finding elements in sorted arrays.
- Handle edge cases gracefully (empty arrays, single-element arrays, `NULL` pointers, negative values, and duplicate elements).

---

## File Structure

```
cs2001-lab09-advanced-sort-search/
├── Dockerfile              # Docker environment specification
├── manifest.json           # Machine-readable metadata and grading targets
├── Makefile                # Build automation and test targets
├── README.md               # Exercise specification and documentation
├── run                     # Helper script for running tests
├── sort_search.h           # Function prototypes and API documentation
├── sort_search.c           # Student implementation file (EDIT THIS FILE)
├── public_test.c           # Public unit test suite
├── reference/
│   └── sort_search.c       # Reference solution (for evaluation & packaging)
└── tests_private/          # Private test suites used during grading
    ├── test_adv_sorts.c    # Private tests for Quick Sort and Merge Sort
    └── test_searches.c     # Private tests for Sequential and Binary Search
```

---

## API Contract

You must implement the four functions declared in `sort_search.h`:

### 1. `void quick_sort(int arr[], int size)`
- Sorts `arr` of size `size` in non-decreasing (ascending) order in-place using the Quick Sort algorithm.
- **Edge Cases:** If `arr == NULL` or `size <= 1`, do nothing and return safely.

### 2. `void merge_sort(int arr[], int size)`
- Sorts `arr` of size `size` in non-decreasing (ascending) order in-place using the Merge Sort algorithm.
- **Edge Cases:** If `arr == NULL` or `size <= 1`, do nothing and return safely. Memory allocated dynamically during merge must be freed properly.

### 3. `int sequential_search(const int arr[], int size, int target)`
- Performs a sequential (linear) search for `target` in `arr`.
- Returns the 0-based index of the first occurrence of `target` if found.
- Returns `-1` if `target` is not in `arr` or if `arr == NULL` or `size <= 0`.

### 4. `int binary_search(const int arr[], int size, int target)`
- Performs binary search for `target` in a sorted array `arr`.
- Returns the 0-based index of `target` if found.
- Returns `-1` if `target` is not in `arr` or if `arr == NULL` or `size <= 0`.

---

## Building and Testing Locally

### Using Make

Run the public test suite:
```bash
make test-public
```

Clean build artifacts:
```bash
make clean
```

### Using the Helper Script

Run public tests:
```bash
./run
# or
./run public
```

Clean build artifacts:
```bash
./run clean
```

---

## Grading Criteria

| Target | Description | Points |
| :--- | :--- | :--- |
| `make test-public` | Public test suite verification | 0 (Diagnostic) |
| `make test-submission-advanced-sorts` | Private tests for Quick Sort and Merge Sort | 5 |
| `make test-submission-searches` | Private tests for Sequential Search and Binary Search | 5 |
| **Total** | | **10** |
