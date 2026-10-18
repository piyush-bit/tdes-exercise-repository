#ifndef MST_OPTIMIZER_HPP
#define MST_OPTIMIZER_HPP

#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <tuple>
#include <iostream>

// Represents an undirected weighted edge connecting vertices u and v
struct Edge {
    int u;
    int v;
    int weight;

    bool operator==(const Edge& other) const {
        return ((u == other.u && v == other.v) || (u == other.v && v == other.u)) && weight == other.weight;
    }
};

// Represents the output result of a Minimum Spanning Tree computation
struct MSTResult {
    int total_weight;
    std::vector<Edge> edges;
    bool is_connected;
};

// Disjoint Set Union (DSU) / Union-Find data structure used in Kruskal's algorithm
class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DisjointSet(int n);
    int find(int i);
    bool unite(int i, int j);
};

// Computes the Minimum Spanning Tree using Kruskal's algorithm (DSU)
MSTResult kruskal_mst(int num_vertices, const std::vector<Edge>& edges);

// Computes the Minimum Spanning Tree using Prim's algorithm (Min-Heap Priority Queue)
MSTResult prim_mst(int num_vertices, const std::vector<Edge>& edges);

#endif // MST_OPTIMIZER_HPP
