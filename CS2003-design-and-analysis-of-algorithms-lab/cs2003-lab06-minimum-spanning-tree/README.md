# CS2003 Lab 06: Minimum Spanning Tree Infrastructure Optimizer

Welcome to **Lab 06: Minimum Spanning Tree Infrastructure Optimizer**. In this lab, you will build graph optimization algorithms in C++ to design minimal-cost network backbones connecting servers, power grids, and telecommunication infrastructure.

---

## 🎯 Learning Objectives

By completing this exercise, you will:
1. Understand and implement **Disjoint Set Union (DSU)** / Union-Find with **Path Compression** and **Union by Rank**.
2. Implement **Kruskal's Algorithm** for Minimum Spanning Trees using DSU and edge sorting.
3. Implement **Prim's Algorithm** for Minimum Spanning Trees using adjacency lists and a **Min-Heap Priority Queue** (`std::priority_queue`).
4. Compare performance and structural outputs of edge-centric (Kruskal) vs node-centric (Prim) MST techniques.

---

## 🛠️ Data Structures & API Specification

All data structures and function prototypes are declared in `mst_optimizer.hpp`. You will implement the functions inside `mst_optimizer.cpp`.

### Data Structures

```cpp
// Represents an undirected weighted edge connecting vertices u and v
struct Edge {
    int u;
    int v;
    int weight;
};

// Represents the output result of an MST algorithm
struct MSTResult {
    int total_weight;          // Sum of edge weights in the MST
    std::vector<Edge> edges;   // List of edges selected in the MST
    bool is_connected;         // true if a valid MST covering all vertices exists; false otherwise
};
```

### DisjointSet Class (DSU)

```cpp
class DisjointSet {
public:
    explicit DisjointSet(int n);  // Initializes parent and rank vectors
    int find(int i);              // Finds set representative with path compression
    bool unite(int i, int j);     // Merges sets containing i and j by rank; returns false if already in same set
};
```

### Core Algorithms

```cpp
// Computes MST using Kruskal's algorithm
MSTResult kruskal_mst(int num_vertices, const std::vector<Edge>& edges);

// Computes MST using Prim's algorithm
MSTResult prim_mst(int num_vertices, const std::vector<Edge>& edges);
```

---

## 📝 Tasks & Implementation Guidelines

1. **DisjointSet (Union-Find)**
   - `DisjointSet(n)`: Initialize `parent[i] = i` and `rank[i] = 0` for all $0 \le i < n$.
   - `find(i)`: Return representative parent of $i$. Implement path compression (`parent[i] = find(parent[i])`).
   - `unite(i, j)`: Find roots of $i$ and $j$. If identical, return `false`. Otherwise, merge smaller rank tree under larger rank tree and return `true`.

2. **Kruskal's Algorithm (`kruskal_mst`)**
   - Sort edges in non-decreasing order of `weight`.
   - Initialize DSU with `num_vertices`.
   - Iterate through sorted edges, calling `unite(u, v)`. Add accepted edges to `result.edges` and add `weight` to `result.total_weight`.
   - For a graph of $V$ vertices, a valid MST must contain exactly $V - 1$ edges. Set `is_connected = true` if $|edges| == V - 1$ (or $V \le 1$), otherwise `false`.

3. **Prim's Algorithm (`prim_mst`)**
   - Build an adjacency list representation from `edges`.
   - Maintain a boolean array `in_mst` tracking visited vertices.
   - Start from vertex `0`, mark `in_mst[0] = true`, and push adjacent edges into a min-heap (`std::priority_queue`).
   - Extract minimum weight edges from the queue connecting unvisited nodes. Update total weight and add selected edges.
   - Verify all $V$ vertices were visited. Set `is_connected = true` if all vertices were included, otherwise `false`.

---

## 🚀 Local Build & Testing

Run tests locally using `make` or the convenience script `./run`:

```bash
# Run public test suite locally
./run public
# or
make test-public

# Clean build artifacts
./run clean
```

---

## 📊 Evaluation & Grading Targets

| Target | Description | Points |
| :--- | :--- | :--- |
| `make test-public` | Public test suite (basic connected graphs) | 0 (Diagnostic) |
| `make test-submission-kruskal-mst` | Evaluates Kruskal's algorithm & DSU implementation | 5 Points |
| `make test-submission-prim-mst` | Evaluates Prim's algorithm & Min-Heap implementation | 5 Points |
| **Total Max Score** | | **10 Points** |
