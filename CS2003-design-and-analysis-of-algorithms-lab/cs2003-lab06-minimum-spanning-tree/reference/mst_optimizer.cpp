#include "mst_optimizer.hpp"
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

// ---------------------------------------------------------------------------
// Disjoint Set Union (DSU) Implementation
// ---------------------------------------------------------------------------

DisjointSet::DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int DisjointSet::find(int i) {
    if (i < 0 || i >= static_cast<int>(parent.size())) return -1;
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent[i]);
}

bool DisjointSet::unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);

    if (root_i == -1 || root_j == -1 || root_i == root_j) {
        return false;
    }

    if (rank[root_i] < rank[root_j]) {
        parent[root_i] = root_j;
    } else if (rank[root_i] > rank[root_j]) {
        parent[root_j] = root_i;
    } else {
        parent[root_j] = root_i;
        rank[root_i]++;
    }

    return true;
}

// ---------------------------------------------------------------------------
// Kruskal's Algorithm Implementation
// ---------------------------------------------------------------------------

MSTResult kruskal_mst(int num_vertices, const std::vector<Edge>& edges) {
    if (num_vertices <= 0) {
        return {0, {}, true};
    }
    if (num_vertices == 1) {
        return {0, {}, true};
    }

    std::vector<Edge> sorted_edges = edges;
    std::sort(sorted_edges.begin(), sorted_edges.end(), [](const Edge& a, const Edge& b) {
        if (a.weight != b.weight) return a.weight < b.weight;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });

    DisjointSet dsu(num_vertices);
    MSTResult result;
    result.total_weight = 0;
    result.is_connected = false;

    for (const auto& edge : sorted_edges) {
        if (edge.u < 0 || edge.u >= num_vertices || edge.v < 0 || edge.v >= num_vertices) {
            continue;
        }
        if (dsu.unite(edge.u, edge.v)) {
            result.edges.push_back(edge);
            result.total_weight += edge.weight;
            if (result.edges.size() == static_cast<size_t>(num_vertices - 1)) {
                break;
            }
        }
    }

    if (result.edges.size() == static_cast<size_t>(num_vertices - 1)) {
        result.is_connected = true;
    } else {
        result.is_connected = false;
    }

    return result;
}

// ---------------------------------------------------------------------------
// Prim's Algorithm Implementation
// ---------------------------------------------------------------------------

MSTResult prim_mst(int num_vertices, const std::vector<Edge>& edges) {
    if (num_vertices <= 0) {
        return {0, {}, true};
    }
    if (num_vertices == 1) {
        return {0, {}, true};
    }

    std::vector<std::vector<std::pair<int, int>>> adj(num_vertices);
    for (const auto& edge : edges) {
        if (edge.u >= 0 && edge.u < num_vertices && edge.v >= 0 && edge.v < num_vertices) {
            adj[edge.u].push_back({edge.v, edge.weight});
            adj[edge.v].push_back({edge.u, edge.weight});
        }
    }

    // Min-heap priority queue storing tuple: (weight, to_vertex, from_vertex)
    using PQItem = std::tuple<int, int, int>;
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;

    std::vector<bool> in_mst(num_vertices, false);
    MSTResult result;
    result.total_weight = 0;
    result.is_connected = false;

    in_mst[0] = true;
    int visited_count = 1;

    for (const auto& nbr : adj[0]) {
        pq.push({nbr.second, nbr.first, 0});
    }

    while (!pq.empty() && visited_count < num_vertices) {
        auto [weight, to_node, from_node] = pq.top();
        pq.pop();

        if (in_mst[to_node]) {
            continue;
        }

        in_mst[to_node] = true;
        visited_count++;
        result.total_weight += weight;
        result.edges.push_back({from_node, to_node, weight});

        for (const auto& nbr : adj[to_node]) {
            if (!in_mst[nbr.first]) {
                pq.push({nbr.second, nbr.first, to_node});
            }
        }
    }

    if (visited_count == num_vertices) {
        result.is_connected = true;
    } else {
        result.is_connected = false;
    }

    return result;
}
