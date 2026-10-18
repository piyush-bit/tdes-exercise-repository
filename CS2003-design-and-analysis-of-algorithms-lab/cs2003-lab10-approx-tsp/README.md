# CS2003 Lab 10: Autonomous Logistics TSP 2-Approximation Engine

## 1. Executive Summary & Problem Context

In modern autonomous logistics networks, a fleet of delivery drones or autonomous ground vehicles must visit a set of $N$ depot/waypoint locations scattered across a 2D Euclidean grid and return to the starting depot. Finding the absolute shortest route that visits every location exactly once is the classical **Travelling Salesperson Problem (TSP)**.

Because TSP is **NP-hard**, computing the exact optimal tour for large delivery networks ($N > 30$) becomes computationally intractable. However, since geographical distances satisfy the **triangle inequality** ($d(u, w) \le d(u, v) + d(v, w)$), the problem falls under **Metric TSP**.

In this lab, you will design and implement a **2-Approximation Algorithm** for Metric TSP using **Prim's Minimum Spanning Tree (MST)** followed by a **Pre-order Depth-First Search (DFS)** shortcutting traversal.

---

## 2. Mathematical Foundation & Algorithm Overview

### 2.1 Metric TSP Properties
Given a set of 2D points $P = \{p_0, p_1, \dots, p_{N-1}\}$, the distance between any two points $p_i = (x_i, y_i)$ and $p_j = (x_j, y_j)$ is the standard Euclidean metric:
$$d(p_i, p_j) = \sqrt{(x_i - x_j)^2 + (y_i - y_j)^2}$$

Metric properties guaranteed:
1. **Symmetry**: $d(p_i, p_j) = d(p_j, p_i)$
2. **Triangle Inequality**: $d(p_i, p_k) \le d(p_i, p_j) + d(p_j, p_k)$ for all $i, j, k$.

### 2.2 The 2-Approximation Bound
Let $OPT$ denote the cost of the optimal TSP tour, and let $W_{\text{MST}}$ denote the total weight of the Minimum Spanning Tree (MST) spanning all points.

1. **Lower Bound**: Removing any edge from an optimal TSP cycle yields a spanning tree. Therefore:
   $$W_{\text{MST}} \le OPT$$
2. **Eulerian Tour**: Traversing every edge of the MST twice (once forward, once backward) creates an Eulerian graph of total weight $2 \cdot W_{\text{MST}}$.
3. **Pre-order DFS Shortcutting**: Visiting the vertices in **Pre-order DFS** order and skipping already visited vertices constructs a valid Hamiltonian cycle (TSP tour). By the triangle inequality, bypassing intermediate vertices never increases total path cost:
   $$\text{Cost}(\text{Approx Tour}) \le 2 \cdot W_{\text{MST}} \le 2 \cdot OPT$$

Hence, this algorithm guarantees a tour cost no greater than **twice the optimal tour cost**!

---

## 3. Detailed Algorithm Workflow

### Step 1: Minimum Spanning Tree (Prim's Algorithm)
Given $N$ points forming a complete graph:
1. Initialize `min_weight[i] = ∞`, `parent[i] = -1`, `in_mst[i] = false` for all $i \in [0, N-1]$.
2. Set `min_weight[start_node] = 0.0`.
3. For $N$ iterations:
   - Pick the unvisited node $u$ with the smallest `min_weight[u]`.
   - Mark $u$ as visited (`in_mst[u] = true`).
   - If `parent[u] != -1`, record edge $(parent[u], u)$ with weight $d(p_{parent[u]}, p_u)$ in `mst_edges`.
   - Update `min_weight[v]` and `parent[v]` for all unvisited $v$ where $d(p_u, p_v) < \text{min\_weight}[v]$.

### Step 2: Deterministic Pre-order DFS Traversal
1. Build an adjacency tree from `mst_edges`.
2. Sort each node's neighbor list in ascending order of vertex ID. This ensures **deterministic DFS traversal**.
3. Perform a Depth-First Search starting at `start_node`. Append node $u$ to the tour sequence upon its first visit (pre-order).

### Step 3: Tour Cost Calculation
Given a tour sequence $[t_0, t_1, \dots, t_{N-1}]$, calculate:
$$\text{Cost} = \left(\sum_{i=0}^{N-2} d(p_{t_i}, p_{t_{i+1}})\right) + d(p_{t_{N-1}}, p_{t_0})$$

---

## 4. Code Base & Interface Specification

### `Point` Structure
```cpp
struct Point {
    int id;
    double x;
    double y;

    double distance_to(const Point& other) const;
};
```

### `Edge` Structure
```cpp
struct Edge {
    int u;
    int v;
    double weight;
};
```

### Function Specifications (`approx_tsp.hpp`)

#### 1. `double calculate_tour_cost(const std::vector<Point>& points, const std::vector<int>& tour)`
- Calculates the total round-trip distance of visiting points in the order specified by `tour`.
- Returns `0.0` if `tour` has 0 or 1 element.

#### 2. `std::vector<int> approx_tsp_2approx(const std::vector<Point>& points, std::vector<Edge>& mst_edges, int start_node = 0)`
- Inputs:
  - `points`: vector of 2D locations.
  - `mst_edges`: output reference vector to store the $N-1$ edges of the MST.
  - `start_node`: root node index for MST construction and DFS traversal (defaults to `0`).
- Returns:
  - Vector of vertex indices representing the 2-approximation TSP tour.
- Edge cases:
  - If `points.empty()`, returns `{}` and empty `mst_edges`.
  - If `points.size() == 1`, returns `{0}` and empty `mst_edges`.

---

## 5. Development & Testing Instructions

### Local Testing
To test your live implementation against the public suite:
```bash
make test-public
# or
./run public
```

### Cleaning Build Artifacts
```bash
make clean
# or
./run clean
```
