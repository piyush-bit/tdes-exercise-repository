# CS2002 Lab 02: Cloud Microservice Connection Pool & Telemetry Counter

## Overview
In modern cloud-native architectures, managing network connections efficiently and measuring real-time telemetry metrics are critical for application responsiveness and scalability. Creating network connections is an expensive operation; microservices rely on **connection pooling** to reuse established sockets up to a maximum allowed limit.

In this lab, you will implement a C++ backend component: `ServiceConnection` in `microservice_pool.cpp` (with declarations in `microservice_pool.hpp`). You will apply core Object-Oriented Programming (OOP) concepts in C++17, focusing on **static class members**, **static factory methods**, resource management, and **inline performance calculation functions**.

---

## Objectives
1. **Static Data Members**: Use static variables (`active_connections_`, `total_connections_created_`, `max_allowed_connections_`) shared across all instances of the class to track global pool metrics.
2. **Static Factory Pattern**: Implement `ServiceConnection::createConnection()` to control connection allocation and enforce max connection constraints.
3. **Resource Lifecycle**: Correctly update connection counts upon connection instantiation, explicit disconnection, and object destruction.
4. **Inline Telemetry Utilities**: Implement zero-overhead telemetry calculations using `inline` functions (`calculateLatencyMs`, `bytesToMegabytes`).

---

## Software Specifications & API Contract

### Class `ServiceConnection` (`microservice_pool.hpp` / `microservice_pool.cpp`)

#### Static Data Members (Private)
- `static int active_connections_`: Tracks the number of currently active connections. Initialized to `0`.
- `static int total_connections_created_`: Tracks the cumulative number of connections created since pool initialization or reset. Initialized to `0`.
- `static int max_allowed_connections_`: Maximum connections allowed in the pool at any given time. Default is `10`.

#### Constructor & Destructor
- `ServiceConnection(int id, const std::string& endpoint)`
  - Initializes `id_`, `endpoint_`, sets `is_connected_ = true`, and sets `bytes_transferred_ = 0`.
  - Increments `active_connections_` and `total_connections_created_`.
- `~ServiceConnection()`
  - Destructor. Calls `disconnect()` so that destroyed objects release active pool capacity.

#### Member Functions
- `void disconnect()`: Sets `is_connected_ = false` and decrements `active_connections_` if the connection was active. Calling `disconnect()` multiple times on the same object must not decrement `active_connections_` more than once.
- `bool isConnected() const`: Returns `true` if the connection is active, `false` otherwise.
- `int getId() const`: Returns the connection ID.
- `const std::string& getEndpoint() const`: Returns the endpoint string.
- `void sendData(size_t bytes)`: If `is_connected_` is `true`, adds `bytes` to `bytes_transferred_`. If disconnected, data is ignored.
- `size_t getBytesTransferred() const`: Returns total bytes transferred over this connection.

#### Static Pool Management & Getter Methods
- `static ServiceConnection* createConnection(int id, const std::string& endpoint)`: Factory method. If `active_connections_ < max_allowed_connections_`, allocates a new `ServiceConnection` on the heap and returns its pointer. If the maximum pool limit is reached, returns `nullptr` without creating an object or incrementing counters.
- `static void setMaxConnections(int max_conn)`: Updates `max_allowed_connections_`.
- `static int getActiveConnections()`: Returns current `active_connections_`.
- `static int getTotalConnectionsCreated()`: Returns `total_connections_created_`.
- `static void resetCounters()`: Resets `active_connections_` to `0`, `total_connections_created_` to `0`, and restores `max_allowed_connections_` to default `10`.

---

### Inline Performance & Telemetry Functions (`microservice_pool.hpp`)

- `inline double calculateLatencyMs(double requestTimeSec, double responseTimeSec)`
  - Calculates round-trip latency in milliseconds: `(responseTimeSec - requestTimeSec) * 1000.0`.
  - If `responseTimeSec < requestTimeSec`, returns `0.0`.
- `inline double bytesToMegabytes(size_t bytes)`
  - Converts byte count to megabytes (MB): `static_cast<double>(bytes) / (1024.0 * 1024.0)`.

---

## File Structure
```
cs2002-lab02-microservice-pool/
├── manifest.json              # Lab metadata & evaluation spec
├── README.md                  # Problem description and documentation
├── Dockerfile                 # Runner container environment (gcc:13-bookworm)
├── Makefile                   # Build script supporting public and submission targets
├── run                        # Executable CLI helper script
├── microservice_pool.hpp      # Header file defining ServiceConnection and inline functions
├── microservice_pool.cpp      # Student boilerplate implementation file (EDIT THIS FILE)
├── public_test.cpp            # Public test suite for student local testing
├── reference/
│   └── microservice_pool.cpp  # Reference implementation for grading validation
└── tests_private/
    ├── test_static_pool.cpp   # Private test suite for static pool & connection limit
    └── test_inline_metrics.cpp# Private test suite for inline telemetry & data counting
```

---

## Running and Testing

To compile and run the public test suite:
```bash
./run
# OR
make test-public
```

To clean build artifacts:
```bash
./run clean
# OR
make clean
```
