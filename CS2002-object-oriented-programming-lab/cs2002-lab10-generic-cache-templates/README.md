# CS2002 Lab 10: Generic Cache & Data Pipeline Templates

## Overview
In high-performance data processing pipelines and backend systems, template-based generic abstractions enable code reuse across diverse data types without sacrificing type safety or runtime efficiency.

This lab covers:
1. **Function Templates**: Implementing generic algorithms operating on Standard Library containers (`std::vector<T>`).
2. **Class Templates**: Designing generic data structures (`GenericCache<K, V>`) supporting key-value operations with bounded capacity and First-In-First-Out (FIFO) eviction.

---

## Objectives
1. Implement the function template `findMaxMetric<T>` to locate peak metric values across numeric, string, or custom comparable types.
2. Implement the class template `GenericCache<K, V>` to manage key-value pairs with configurable capacity and FIFO eviction.

---

## Specifications

### 1. Function Template: `findMaxMetric<T>`
```cpp
template <typename T>
T findMaxMetric(const std::vector<T>& metrics);
```
- **Inputs**: A constant reference to `std::vector<T>`.
- **Outputs**: Returns the maximum element in `metrics` (determined by `operator<`).
- **Exceptions**: Throws `std::invalid_argument("metrics vector cannot be empty")` if `metrics` is empty.

---

### 2. Class Template: `GenericCache<K, V>`
```cpp
template <typename K, typename V>
class GenericCache;
```

#### Member Functions:
- **`explicit GenericCache(size_t capacity = 100)`**
  - Initializes a cache with maximum `capacity`.
  - Throws `std::invalid_argument` if `capacity == 0`.
- **`void put(const K& key, const V& value)`**
  - Inserts or updates a key-value mapping.
  - If `key` exists, updates the associated value.
  - If `key` is new and current size equals `capacity`, evicts the oldest inserted key before inserting the new entry.
- **`std::optional<V> get(const K& key) const`**
  - Returns `std::optional<V>` containing the value if `key` exists; otherwise returns `std::nullopt`.
- **`bool contains(const K& key) const`**
  - Returns `true` if `key` exists in cache, `false` otherwise.
- **`size_t size() const`**
  - Returns the current number of cached entries.
- **`size_t capacity() const`**
  - Returns the maximum allowed capacity.
- **`void clear()`**
  - Clears all cached key-value entries.

---

## Files in this Lab
- `generic_cache.hpp`: Header file containing template declarations.
- `generic_cache.cpp`: Student implementation file containing `// TODO:` stubs. **(File to edit & submit)**.
- `public_test.cpp`: Public test suite runnable via `make test-public`.
- `Makefile`: Build configuration for local testing and evaluator grading targets.
- `run`: Executable helper script.

---

## Building and Testing Locally

Run the public test suite using the `run` helper script:
```bash
./run
```
Or directly using `make`:
```bash
make test-public
```

Clean build artifacts:
```bash
make clean
```
