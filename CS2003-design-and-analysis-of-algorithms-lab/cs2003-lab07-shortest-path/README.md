# CS2003 Lab 07: GPS Route Navigation & Shortest Path Engine

## Overview

In modern navigation systems, computing the shortest path between locations (nodes) across a transportation network (graph) is a fundamental problem. This lab requires you to design and implement a single-source shortest path engine in C++ featuring two classic graph algorithms:

1. **Dijkstra's Algorithm**: Greedy single-source shortest path algorithm using a min-priority queue (`std::priority_queue`), optimal for graphs with non-negative edge weights.
2. **Bellman-Ford Algorithm**: Dynamic programming single-source shortest path algorithm capable of handling negative edge weights and detecting reachable **negative weight cycles**.
3. **Path Reconstruction**: Utility function `reconstruct_path` to reconstruct the exact node sequence of the shortest path from the source node to any destination using parent pointers.

---

## Technical Specifications

All data structures and function prototypes are defined in `shortest_path.hpp`.

### Data Structures

```cpp
struct Edge {
    int src;
    int dest;
    double weight;
};

struct ShortestPathResult {
    bool success;              // True if execution and parameters were valid
    bool has_negative_cycle;   // True if Bellman-Ford detected a reachable negative cycle
    std::vector<double> distances; // Distance from source node to vertex i
    std::vector<int> parent;       // Immediate predecessor of vertex i in shortest path tree
};
```

---

## API & Function Contracts

### 1. `dijkstra_shortest_path`

```cpp
ShortestPathResult dijkstra_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node);
```

- **Description**: Computes single-source shortest path distances and parent pointers from `start_node` to all vertices in `[0, num_nodes - 1]`.
- **Validation**:
  - `num_nodes` must be `> 0`.
  - `start_node` must be within `[0, num_nodes - 1]`.
  - Every edge must satisfy `0 <= src < num_nodes`, `0 <= dest < num_nodes`, and `weight >= 0.0`.
  - If any validation fails, return `ShortestPathResult` with `success = false`.
- **Behavior**:
  - Initialize `distances` vector of size `num_nodes` with `std::numeric_limits<double>::infinity()`, except `distances[start_node] = 0.0`.
  - Initialize `parent` vector of size `num_nodes` with `-1`.
  - Use a min-priority queue to greedily extract the unvisited vertex with the minimum distance and relax outbound edges.
  - Return `ShortestPathResult` with `success = true` and `has_negative_cycle = false`.

### 2. `bellman_ford_shortest_path`

```cpp
ShortestPathResult bellman_ford_shortest_path(int num_nodes, const std::vector<Edge>& edges, int start_node);
```

- **Description**: Computes single-source shortest path distances and parent pointers from `start_node` to all vertices in `[0, num_nodes - 1]`, supporting negative edge weights.
- **Validation**:
  - `num_nodes` must be `> 0`.
  - `start_node` must be within `[0, num_nodes - 1]`.
  - Every edge must satisfy `0 <= src < num_nodes` and `0 <= dest < num_nodes`.
  - If any validation fails, return `ShortestPathResult` with `success = false`.
- **Behavior**:
  - Initialize `distances` to infinity and `parent` to `-1`, with `distances[start_node] = 0.0`.
  - Relax all edges `num_nodes - 1` times.
  - Perform an additional ($N$-th) relaxation pass over all edges. If any edge `(u, v, w)` reachable from source (`distances[u] != infinity`) can be further relaxed (`distances[u] + w < distances[v]`), set `has_negative_cycle = true`.
  - Return `ShortestPathResult` with `success = true`.

### 3. `reconstruct_path`

```cpp
std::vector<int> reconstruct_path(int start_node, int target_node, const std::vector<int>& parent);
```

- **Description**: Reconstructs the node sequence from `start_node` to `target_node`.
- **Behavior**:
  - Returns `{start_node}` if `start_node == target_node` (provided indices are valid).
  - Traces back from `target_node` to `start_node` using `parent`.
  - Returns `std::vector<int>` containing the sequence `[start_node, ..., target_node]`.
  - If `target_node` is unreachable or indices are invalid, return an empty vector `{}`.

---

## Local Development & Testing

Run public tests against your live solution:

```bash
make test-public
# or using the run wrapper:
./run
```

Clean build artifacts:

```bash
make clean
# or:
./run clean
```
