# CS2002 Lab 04: RAII Database Session & Transaction Manager

## Overview

**Resource Acquisition Is Initialization (RAII)** is a core C++ design pattern that binds the lifecycle of resources (such as dynamic memory, sockets, file descriptors, and database locks) to the lifetime of objects. In database applications, failing to close socket handles or flush pending data buffers can result in database corruption, resource exhaustion, and memory leaks.

In this lab, you will implement `DatabaseConnection`, a class managing a simulated database connection socket and an internal dynamically allocated write buffer using RAII principles.

---

## Objectives

1. **Object Lifecycles & RAII**: Ensure resources (socket handles and dynamic buffers) are acquired upon object instantiation and automatically cleaned up (flushed and released) during object destruction.
2. **Deep Copy Semantics**: Implement custom copy constructors and copy assignment operators to perform deep copying of dynamically allocated array buffers, preventing double-free errors and dangling pointer issues.
3. **Buffer Management**: Manage dynamic character buffers for staging database write operations before flushing.

---

## API & Class Specification

The class `DatabaseConnection` is declared in `db_connection.hpp`. You must implement its methods in `db_connection.cpp`.

### Constructors & Destructor

- `DatabaseConnection()`
  - **Default Constructor**:
    - Initializes `db_name_` to `"default_db"`.
    - Initializes `socket_fd_` to `-1` (disconnected).
    - Sets `is_connected_` to `false`.
    - Allocates dynamic memory buffer `buffer_` with capacity `1024` bytes.
    - Sets `buffer_size_` to `0` and initializes `buffer_[0] = '\0'`.

- `DatabaseConnection(const std::string& db_name, int socket_fd)`
  - **Parameterized Constructor**:
    - Initializes `db_name_` to the provided database name.
    - Initializes `socket_fd_` to the provided file descriptor.
    - Sets `is_connected_` to `true` if `socket_fd >= 0`, otherwise `false`.
    - Allocates dynamic memory buffer `buffer_` with capacity `1024` bytes.
    - Sets `buffer_size_` to `0` and initializes `buffer_[0] = '\0'`.
    - Increments active connections count if `is_connected_` is `true`.

- `DatabaseConnection(const DatabaseConnection& other)`
  - **Copy Constructor (Deep Copy)**:
    - Copies scalar and string attributes (`db_name_`, `socket_fd_`, `is_connected_`, `buffer_capacity_`, `buffer_size_`).
    - Allocates a new dynamic array buffer `new char[buffer_capacity_]`.
    - Copies buffer content from `other.buffer_` into the newly allocated buffer.
    - Increments active connections count if `is_connected_` is `true`.

- `~DatabaseConnection()`
  - **RAII Destructor**:
    - If `is_connected_` is `true`:
      - Flushes the buffer by invoking `flush_buffer()`.
      - Closes the connection by invoking `close_connection()`.
    - Deallocates the dynamically allocated buffer: `delete[] buffer_; buffer_ = nullptr;`.

### Assignment Operator

- `DatabaseConnection& operator=(const DatabaseConnection& other)`
  - Handles self-assignment (`this == &other`).
  - Flushes and closes existing resources if `is_connected_` is `true`, and releases old `buffer_`.
  - Performs deep copy of `other`'s attributes and allocates a fresh buffer copy.
  - Returns `*this`.

### Core Operations & Methods

- `void write_to_buffer(const std::string& data)`
  - Appends `data` to `buffer_` if `is_connected_` is `true`.
  - Dynamically expands `buffer_` capacity (e.g., doubling capacity) if the incoming data exceeds current `buffer_capacity_`.
  - Null-terminates the buffer string after copying.

- `void flush_buffer()`
  - Clears buffered write data (`buffer_size_ = 0`, `buffer_[0] = '\0'`).
  - Increments the total flush counter (`total_flushes_`).

- `void close_connection()`
  - If `is_connected_` is `true`:
    - Sets `is_connected_ = false` and `socket_fd_ = -1`.
    - Increments total closed connection count (`total_closes_`) and decrements active connection count (`active_connections_`).

### Getters & Metrics

- `std::string get_db_name() const`
- `int get_socket_fd() const`
- `const char* get_buffer() const`
- `std::size_t get_buffer_size() const`
- `std::size_t get_buffer_capacity() const`
- `bool is_connected() const`
- `static int get_total_flushes()`
- `static int get_total_closes()`
- `static int get_active_connections()`
- `static void reset_counters()`

---

## Local Verification & Usage

Run the public test suite locally to verify your implementation:

```bash
make test-public
# or using the run wrapper:
./run
```

To clean generated binaries and temporary files:

```bash
make clean
```
