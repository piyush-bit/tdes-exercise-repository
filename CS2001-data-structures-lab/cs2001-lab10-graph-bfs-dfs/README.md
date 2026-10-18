# CS2001 Lab 10: Graph Implementation, BFS & DFS Traversal in C

## Objectives
In this lab, you will implement an adjacency list representation of a Graph data structure in C and implement two fundamental graph traversal algorithms:
1. **Breadth-First Search (BFS)**
2. **Depth-First Search (DFS)**

---

## Data Structure Overview

A Graph $G = (V, E)$ consists of a set of vertices $V$ and edges $E$. In this lab, graphs are represented using an **Adjacency List**.

### Data Structures (`graph.h`)

```c
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int num_vertices;
    Node** adj_lists;
    int is_directed; // 0 for undirected, 1 for directed
} Graph;
```

- `num_vertices`: Total number of vertices in the graph, labeled `0` to `num_vertices - 1`.
- `adj_lists`: Array of linked list heads of size `num_vertices`. Each entry `adj_lists[i]` points to the head of a linked list containing adjacent target vertices for vertex `i`.
- `is_directed`: Flag indicating directed (`1`) or undirected (`0`) edges.

---

## Function Specifications & API Contracts

You are required to implement the functions declared in `graph.h` inside `graph.c`.

### 1. `Graph* create_graph(int num_vertices, int is_directed)`
- Allocates and initializes a `Graph` structure.
- Allocates an array of `num_vertices` `Node*` pointers for `adj_lists`, initialized to `NULL`.
- Sets `is_directed` to `1` if `is_directed != 0`, otherwise `0`.
- **Error Conditions**: Returns `NULL` if `num_vertices <= 0` or if any memory allocation fails.

### 2. `int add_edge(Graph* graph, int src, int dest)`
- Appends an edge from `src` to `dest` at the **end (tail)** of vertex `src`'s adjacency list.
- If `is_directed == 0` (undirected) and `src != dest`, also appends an edge from `dest` to `src` at the tail of vertex `dest`'s adjacency list.
- **Error Conditions**: Returns `-1` if `graph` is `NULL`, `graph->adj_lists` is `NULL`, vertex index `src < 0` or `src >= num_vertices`, vertex index `dest < 0` or `dest >= num_vertices`, or if node allocation fails.
- **Return Value**: Returns `0` on success, `-1` on error.

### 3. `int bfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity)`
- Performs Breadth-First Search starting from `start_vertex`.
- Uses a Queue (FIFO order) and tracks visited vertices to prevent infinite loops.
- Adjacent vertices must be processed in the exact order they appear in the adjacency list.
- Stores the traversal order into `result`.
- **Error Conditions**: Returns `-1` if `graph` is `NULL`, `result` is `NULL`, `start_vertex < 0` or `start_vertex >= num_vertices`, `capacity <= 0`, or if `capacity` is less than the total number of reachable vertices visited.
- **Return Value**: Returns the total number of vertices visited in the traversal component on success, `-1` on error.

### 4. `int dfs_traversal(const Graph* graph, int start_vertex, int* result, int capacity)`
- Performs Depth-First Search starting from `start_vertex`.
- Recursively (or using an explicit stack) visits adjacent unvisited vertices in the exact order they appear in the adjacency list.
- Stores the traversal order into `result`.
- **Error Conditions**: Returns `-1` if `graph` is `NULL`, `result` is `NULL`, `start_vertex < 0` or `start_vertex >= num_vertices`, `capacity <= 0`, or if `capacity` is less than the total number of reachable vertices visited.
- **Return Value**: Returns the total number of vertices visited in the traversal component on success, `-1` on error.

### 5. `void free_graph(Graph* graph)`
- Deallocates all dynamically allocated memory, including every linked list node across all `adj_lists`, the `adj_lists` array itself, and the `Graph` struct.
- Safe to call with `NULL` (no-op).

---

## Traversal Order Guidelines

To ensure deterministic test results:
- Always append newly added edges to the **tail** of the adjacency list.
- When visiting neighbors of vertex `u` during BFS or DFS, process them in order from the head node to the tail node of `adj_lists[u]`.

---

## How to Test Locally

Run public tests:
```bash
make test-public
# or
./run public
```

Clean build artifacts:
```bash
make clean
# or
./run clean
```
