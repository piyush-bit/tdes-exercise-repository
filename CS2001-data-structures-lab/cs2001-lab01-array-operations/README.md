# CS2001 Lab 01: Array Operations — Traversal, Insertion, and Deletion in C

## Problem Overview

In computer science, an **array** is a contiguous block of memory holding elements of the same data type. Operating on an array requires managing its **size** (the number of currently stored valid elements) relative to its **capacity** (the total allocated memory capacity).

In this lab, you will implement foundational operations on integer arrays in C:
1. **Traversal** (`traverse_array`): Copying array elements to a destination array while analyzing/iterating through elements.
2. **Insertion** (`insert_at_index`): Inserting a new element at a specific index, shifting subsequent elements to the right.
3. **Deletion** (`delete_at_index`): Removing an element at a specific index, shifting subsequent elements to the left.
4. **Search** (`find_element`): Searching for the first occurrence of a target value.

---

## File Structure

- `array_operations.h` — Function declarations and contract documentation (Do not modify).
- `array_operations.c` — **Your working file.** Complete all `// TODO:` stubs here.
- `public_test.c` — Public unit test suite.
- `Makefile` — Build and test commands.
- `run` — Convenience wrapper script (`./run`).

---

## API Function Specifications

### 1. `int traverse_array(const int src[], int size, int dest[], int dest_capacity)`
Copies all `size` elements from `src` into `dest`.
- **Returns**: Number of elements copied (`size`) on success.
- **Returns `-1` on error**:
  - `src == NULL` or `dest == NULL`
  - `size < 0`
  - `dest_capacity < size`

### 2. `int insert_at_index(int arr[], int size, int capacity, int index, int element)`
Inserts `element` at position `index` (0-based) into `arr`. Shifts existing elements from `index` up to `size - 1` one slot to the right.
- **Returns**: New array size (`size + 1`) on success.
- **Returns `-1` on error**:
  - `arr == NULL`
  - `capacity <= 0` or `size < 0`
  - `size >= capacity` (array is full)
  - `index < 0` or `index > size` (invalid index)

### 3. `int delete_at_index(int arr[], int size, int index)`
Deletes the element at position `index` (0-based) from `arr`. Shifts existing elements from `index + 1` up to `size - 1` one slot to the left.
- **Returns**: New array size (`size - 1`) on success.
- **Returns `-1` on error**:
  - `arr == NULL`
  - `size <= 0` (array is empty)
  - `index < 0` or `index >= size` (invalid index)

### 4. `int find_element(const int arr[], int size, int target)`
Searches `arr` for `target`.
- **Returns**: 0-based index of the first occurrence of `target` if found.
- **Returns `-1` if not found** or if parameters are invalid (`arr == NULL` or `size <= 0`).

---

## How to Test Locally

Run the public test suite using either the Makefile or the convenience script:

```bash
make test-public
# OR
./run
```

To clean build artifacts:
```bash
make clean
# OR
./run clean
```

---

## Grading Criteria

| Target | Points | Public / Private | Description |
| :--- | :---: | :---: | :--- |
| `make test-public` | 0 | Public | Local verification of student boilerplate & basic cases |
| `make test-submission-traversal` | 3 | Private | Boundary conditions, empty size, NULL pointers & capacity limits |
| `make test-submission-insertion` | 3 | Private | Insertion at front, middle, end; full array overflow & invalid indices |
| `make test-submission-deletion` | 4 | Private | Deletion from front, middle, end; empty array underflow & searching |
| **Total** | **10** | | |
